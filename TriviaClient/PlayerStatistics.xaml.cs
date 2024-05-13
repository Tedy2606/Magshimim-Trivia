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
    /// Interaction logic for PlayerStatistics.xaml
    /// </summary>
    public partial class PlayerStatistics : Page
    {
        private NetworkStream _stream;
        public PlayerStatistics(NetworkStream stream)
        {
            InitializeComponent();
            this._stream = stream;

            // Send a message to the server
            JObject message = new JObject();

            string jsonString = message.ToString();
            byte code = 114;



            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                this.score.Text = "score : " + jsonObject["statistics"][0];
                this.games.Text = "games : " + jsonObject["statistics"][1];
                this.answers.Text = "answers : " + jsonObject["statistics"][2];
                this.correctAnswers.Text = "correctAnswers : " + jsonObject["statistics"][3];
                this.averageAnswerTime.Text = "score : " + jsonObject["statistics"][4];

            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }


        }

        private void back_Click(object sender, RoutedEventArgs e)
        {
            if (NavigationService.CanGoBack)
            {
                NavigationService?.GoBack();
            }
        }
    }
}
