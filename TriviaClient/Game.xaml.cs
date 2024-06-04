using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
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
        private Random random;
        public Game(NetworkStream stream)
        {
            InitializeComponent();
            this._stream = stream;

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
                this.random = new Random();
                int[] answers = { 0, 1, 2, 3 };
                Shuffle(answers);
                //this.buttonArr[answers[0]] = answer1



            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
        }

        private void answer2_Click(object sender, RoutedEventArgs e)
        {
            JObject message = new JObject();
            string jsonString = message.ToString();
            byte code = 131;
            //add the answer id from the tag maybe
            // message["id"] = this.button.tag or smth like that



            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                NavigationService?.Navigate(new Game(this._stream));
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
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
