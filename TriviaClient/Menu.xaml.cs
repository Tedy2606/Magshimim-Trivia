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
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Page
    {
        private NetworkStream _stream;
        public Menu(NetworkStream stream, string name)
        {
            InitializeComponent();
            this._stream = stream;
            this.username.Text = name;
        }

        private void logout_Click(object sender, RoutedEventArgs e)
        {
            // Send a message to the server
            JObject message = new JObject();
            string jsonString = message.ToString();
            byte code = 111;




            byte[] data_len_bytes = BitConverter.GetBytes(jsonString.Length);
            //reverse to reverse the endian orientation 
            data_len_bytes = data_len_bytes.Reverse().ToArray();




            var messageBytes = Encoding.UTF8.GetBytes(jsonString);

            byte[] message_and_len = data_len_bytes.Concat(messageBytes).ToArray();

            var full_msg_byte = Enumerable.Prepend(message_and_len, code).ToArray();

            this._stream.Write(full_msg_byte, 0, full_msg_byte.Length);


            // Receive response from the server
            byte[] len_buffer = new byte[5];
            int len_bytesRead = this._stream.Read(len_buffer, 0, len_buffer.Length);
            //guess whos fucking back
            int data_len = (len_buffer[1] << 24) | (len_buffer[2] << 16) | (len_buffer[3] << 8) | len_buffer[4];

            byte[] buffer = new byte[data_len];



            //read from stream 
            int bytesRead = this._stream.Read(buffer, 0, buffer.Length);
            //get the string 
            string utf8String = Encoding.UTF8.GetString(buffer, 0, bytesRead);
            //turn string into json 
            JObject jsonObject = JObject.Parse(utf8String);
            if (!jsonObject.ContainsKey("message"))
            {
                NavigationService?.GoBack();
                NavigationService?.GoBack();
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
        }

        private void exit_Click(object sender, RoutedEventArgs e)
        {
            logout_Click(sender, e);
            // Get the main window of the application
            Window mainWindow = Application.Current.MainWindow;

            // Close the main window (which effectively closes the application)
            mainWindow.Close();
        }

        private void createRoom_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new CreateRoom(this._stream));
        }

        private void joinRoom_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new JoinRoom(this._stream));
        }
    }
}
