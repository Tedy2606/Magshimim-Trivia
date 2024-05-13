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
    /// Interaction logic for HighScores.xaml
    /// </summary>
    public partial class HighScores : Page
    {
        private NetworkStream _stream;
        public HighScores(NetworkStream stream)
        {
            InitializeComponent();
            this._stream = stream;
            // Send a message to the server
            JObject message = new JObject();

            string jsonString = message.ToString();
            byte code = 115;



            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                this.user1.Text = "user1 : " + jsonObject["statistics"][0];
                this.user2.Text = "user2 : " + jsonObject["statistics"][1];
                this.user3.Text = "user3 : " + jsonObject["statistics"][2];
                this.user4.Text = "user4 : " + jsonObject["statistics"][3];
                this.user5.Text = "user5 : " + jsonObject["statistics"][4];
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
