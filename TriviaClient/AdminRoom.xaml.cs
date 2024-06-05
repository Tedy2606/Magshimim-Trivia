using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
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
    /// Interaction logic for AdminRoom.xaml
    /// </summary>
    public partial class AdminRoom : Page
    {
        private NetworkStream _stream;
        private DispatcherTimer _dispatcherTimer;
        //the following two are purly to be passed down to game
        private int _amountOfQuestions;
        private int _answerTime;

        public AdminRoom(NetworkStream stream, string roomName, int amountOfQuestions, int answerTime)
        {
            this._stream = stream;
            InitializeComponent();
            //just for the game itself
            this._amountOfQuestions = amountOfQuestions;
            this._answerTime = answerTime;


            this.roomName.Text = roomName;

            // initialize the dispatcher timer
            this._dispatcherTimer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(3)
            };
            this._dispatcherTimer.Tick += this.DispatcherTimer_Tick;

            // start refreshing the rooms
            this._dispatcherTimer.Start();
            this.refresh();

            
        }

        private void DispatcherTimer_Tick(object sender, EventArgs e)
        {
            this.refresh();
        }

        private void closeRoom_Click(object sender, RoutedEventArgs e)
        {
            // Send a message to the server
            Button clickedButton = sender as Button;
            JObject message = new JObject();
            string jsonString = message.ToString();
            byte code = 131;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                this._dispatcherTimer.Stop();
                NavigationService?.GoBack();
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
        }

        private void startGame_Click(object sender, RoutedEventArgs e)
        {
            // Send a message to the server
            Button clickedButton = sender as Button;
            JObject message = new JObject();
            string jsonString = message.ToString();
            byte code = 132;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                this._dispatcherTimer.Stop();
                NavigationService?.Navigate(new Game(this._stream, this._amountOfQuestions, this._answerTime, 1));
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
        }

        private void refresh()
        {
            // clear the buttons when refreshing
            stackPanel.Children.Clear();

            // Send a message to the server
            JObject message = new JObject();

            string jsonString = message.ToString();
            byte code = 120;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (jsonObject.ContainsKey("message"))
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
            else
            {
                Regex regex = new Regex(@"\w+");

                //get the button name - id string 
                string players = jsonObject.Value<string>("players");

                Boolean isAdmin = true;
                foreach (Match match in regex.Matches(players))
                {
                    string name = match.Value;

                    // Create the button of the room
                    TextBlock player = new TextBlock
                    {
                        Text = name,
                        Width = 360,
                        Height = 60,
                        Foreground = isAdmin ?
                            App.Current.Resources["Highlight"] as SolidColorBrush :
                            App.Current.Resources["Text"] as SolidColorBrush,
                        FontSize = 42,
                        FontFamily = new FontFamily("Arial"),
                        FontWeight = FontWeights.Bold,
                        TextAlignment = TextAlignment.Center
                    };

                    stackPanel.Children.Add(player);
                    isAdmin = false;
                }
            }
        }
    }
}
