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
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Page
    {
        private NetworkStream _stream;
        public Signup(NetworkStream stream)
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

        private void signup_Click(object sender, RoutedEventArgs e)
        {
            if (password.Text != confirmPassword.Text)
            {
                MessageBox.Show($"passwords do not match!");
                return;

            }
            // Send a message to the server
            JObject message = new JObject();
            message["username"] = username.Text;
            message["password"] = password.Text;
            message["mail"] = email.Text;
            string jsonString = message.ToString();
            byte code = 102;

            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);


            if (!jsonObject.ContainsKey("message"))
            {
                NavigationService?.Navigate(new Menu(this._stream, username.Text));
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
        }
    }
}
