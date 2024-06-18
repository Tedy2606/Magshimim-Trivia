using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
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
    /// Interaction logic for AddQuestion.xaml
    /// </summary>
    public partial class AddQuestion : Page
    {
        private NetworkStream _stream;

        public AddQuestion(NetworkStream stream)
        {
            InitializeComponent();
            this._stream = stream;
        }

        private void submit_Click(object sender, RoutedEventArgs e)
        {
            // Send a message to the server
            JObject message = new JObject();
            message["question"] = question.Text;
            message["correctAnswer"] = correctAnswer.Text;
            message["answer1"] = answer1.Text;
            message["answer2"] = answer2.Text;
            message["answer3"] = answer3.Text;

            string jsonString = message.ToString();
            byte code = 118;

            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                MessageBox.Show($"Question has been added");
                NavigationService?.GoBack();
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
