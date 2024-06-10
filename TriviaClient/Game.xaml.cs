using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    /// 

    public partial class Game : Page
    {
        private NetworkStream _stream;
        
        private Button[] buttonArr;
        private TextBlock[] textArr;
        private Random random;

        private int _amountOfQuestions;
        private int _answerTime;
        private int _currQuestion;
        private int _correctAnswerCount;
        private int _timeLeft;
        private bool _tickCancallationFlag;
        private int _totalAnswerTime;
        


        public Game(NetworkStream stream, int amountOfQuestions, int answerTime, int currQuestion, int correctAnswerCount, int totalTime)
        {


            InitializeComponent();

            this._totalAnswerTime = totalTime;

            this._tickCancallationFlag = true;
            Thread timeThread = new Thread(new ThreadStart(timeTick));
            timeThread.Start();


            this._stream = stream;
            this._currQuestion = currQuestion;
            this._amountOfQuestions = amountOfQuestions;
            this.questionsNum.Text = "Question " + currQuestion.ToString() + " out of " + amountOfQuestions.ToString();

            this._correctAnswerCount = correctAnswerCount;
            this.correct.Text = "Correct Answers: " + correctAnswerCount.ToString();

            this._answerTime = answerTime;

            
            JObject message = new JObject();
            string jsonString = message.ToString();
            byte code = 142;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                this.question.Text = jsonObject.Value<string>("question");
                //now assign each button an answer and an answer id randomly 
                this.buttonArr = new Button[4];
                this.buttonArr[0] = this.answer1;
                this.buttonArr[1] = this.answer2;
                this.buttonArr[2] = this.answer3;
                this.buttonArr[3] = this.answer4;

                this.textArr = new TextBlock[4];
                this.textArr[0] = this.answer1Text;
                this.textArr[1] = this.answer2Text;
                this.textArr[2] = this.answer3Text;
                this.textArr[3] = this.answer4Text;

                this.random = new Random();
                //shuffle the answers
                int[] answerPlaces = { 0, 1, 2, 3 };
                Shuffle(answerPlaces);

                // extract the answers
                Regex regex = new Regex(@"\d+:[^,]+");

                string answers = jsonObject.Value<string>("answers");

                int i = 0;
                foreach (Match match in regex.Matches(answers))
                {
                    string[] parsedMatch = match.Value.Split(':');
                    int id = int.Parse(parsedMatch[0]);
                    string answer = parsedMatch[1];

                    this.textArr[answerPlaces[i]].Text = answer;
                    this.buttonArr[answerPlaces[i]].Tag = id;
                    i++;
                }
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
            
        }
        private void timeTick()
        {
            this._timeLeft = this._answerTime;
            while (this._tickCancallationFlag)
            {
                this.Dispatcher.Invoke(() => {
                    this.time.Text = "Time Left: " + time.ToString();
                });
                this._timeLeft--;

                //because dispatcher takes a while (probably) if time will reset at 0
                //it will go over to the next question at 2 (in the ui) so we use -2
                if (this._timeLeft == -2)
                {
                    
                    this.Dispatcher.Invoke(() => {
                        // answer id 5 does not exist, whcih means the answer will always be wrong
                        this.sendButtonAnswer(5);
                    });
                }
                Thread.Sleep(1000);
            }

        }
        private void sendButtonAnswer(int answerId)
        {
            JObject message = new JObject();
            string jsonString = message.ToString();
            byte code = 143;
            message["answerID"] = answerId;

            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {

                if (jsonObject.Value<int>("isCorrect") == 1)
                {
                    //correct answer
                    this._correctAnswerCount++;
                   

                }
                else
                {
                    //wrong answer
                    

                }
                this._tickCancallationFlag = false;
                if (this._amountOfQuestions == this._currQuestion)
                {
                    NavigationService?.Navigate(new WaitingResults(this._stream, this._correctAnswerCount, this._to));
                }
                else
                {
                    NavigationService?.Navigate(new Game(this._stream, this._amountOfQuestions, this._answerTime, this._currQuestion + 1, this._correctAnswerCount, this._totalAnswerTime + this._timeLeft));

                }
                
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }

        }

        private void answer_Click(object sender, RoutedEventArgs e)
        {
            Button clickedButton = sender as Button;
            sendButtonAnswer(int.Parse(clickedButton.Tag.ToString()));
        }

        //private funv to make 4 randomn numbers for the answers
        private void Shuffle(int[] array)
        {
            for (int i = array.Length - 1; i > 0; i--)
            {
                int j = random.Next(0, i + 1);
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }


    }
}
