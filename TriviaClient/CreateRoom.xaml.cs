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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Page
    {
        private NetworkStream _stream;
        public CreateRoom(NetworkStream stream)
        {
            InitializeComponent();
            this._stream = stream;
        }

        private void back_Click(object sender, RoutedEventArgs e)
        {
            if (NavigationService.CanGoBack)
            {
                NavigationService?.GoBack();
            }
        }

        private void createRoom_Click(object sender, RoutedEventArgs e)
        {
            // Send a message to the server
            JObject message = new JObject();
            message["maxUsers"] = (int)playerNum.Value;
            message["answerTimeout"] = (int)answerTime.Value;
            message["questionCount"] = 10;
            message["roomName"] = roomName.Text;
            string jsonString = message.ToString();
            byte code = 113;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                NavigationService?.Navigate(new AdminRoom(this._stream, roomName.Text, (int)this.questionCount.Value, (int)this.answerTime.Value));
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
        }
    }
}
