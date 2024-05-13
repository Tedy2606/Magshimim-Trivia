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
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Page
    {
        private NetworkStream _stream;
        public Login( NetworkStream stream)
        {
            this._stream = stream;
            InitializeComponent();
        }

        private void back_Click(object sender, RoutedEventArgs e)
        {
            if (NavigationService.CanGoBack)
            {
                NavigationService?.GoBack();
            }
        }

        private void login_Click(object sender, RoutedEventArgs e)
        {

            // Send a message to the server
            JObject message = new JObject();
            message["username"] = username.Text;
            message["password"] = password.Text;
            string jsonString = message.ToString();
            byte code = 101;

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
