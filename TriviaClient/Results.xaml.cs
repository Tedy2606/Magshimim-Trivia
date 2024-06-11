using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.CompilerServices;
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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for Results.xaml
    /// </summary>
    public partial class Results : Page
    {
        private NetworkStream _stream;
        private int _amoutOfQuestions;

        public Results(NetworkStream stream, int amountOfQuestions, int correctCount, int totalAnswerTime)
        {
            InitializeComponent();

            this._stream = stream;
            this._amoutOfQuestions = amountOfQuestions;

            // add results text
            this.correctAnswers.Text += correctCount.ToString();

            this.averageAnswerTime.Text += amountOfQuestions != 0 ? (totalAnswerTime / amountOfQuestions).ToString() + "s" : "0";

            //open results and calculate points ( finish the db function to submit data)
            JObject message = new JObject();
            byte code = 144;

            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                stackPanel.Children.Clear(); // clear the waiting for players string

                // get the results regex
                Regex regex = new Regex(@"\w+:\d+\.\d+");

                string results = jsonObject.Value<string>("results");

                Boolean isWinner = true;
                foreach (Match match in regex.Matches(results))
                {
                    string[] parsedMatch = match.Value.Split(':');
                    string score = parsedMatch[0] + " - " + parsedMatch[1].Remove(parsedMatch[1].Length - 4) + "pts";

                    // Create the button of the room
                    TextBlock player = new TextBlock
                    {
                        Text = score,
                        Width = 360,
                        Height = 60,
                        Foreground = isWinner ?
                            App.Current.Resources["Highlight"] as SolidColorBrush :
                            App.Current.Resources["Text"] as SolidColorBrush,
                        FontSize = 42,
                        FontFamily = new FontFamily("Arial"),
                        FontWeight = FontWeights.Bold,
                        TextAlignment = TextAlignment.Center
                    };

                    stackPanel.Children.Add(player);
                    isWinner = false;
                }
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
        }

        private void backToMenu_Click(object sender, RoutedEventArgs e)
        {
            if (NavigationService.CanGoBack)
            {
                NavigationService?.GoBack(); // to game screen

                for (int i = 0; i < this._amoutOfQuestions;  i++) // go to room screen
                {
                    NavigationService?.GoBack();
                }
                
                NavigationService?.GoBack(); // go to room create/join screen

                NavigationService?.GoBack(); // go to menu
            }
        }
    }
}
