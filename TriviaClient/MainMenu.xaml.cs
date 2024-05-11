using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Text.Json.Nodes;
using System.Collections;



namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Page
    {

        private void rndfunc() 
        {
            //no defines 
            const int port = 56812;

            using (TcpClient cliente = new TcpClient())
            {
                IPAddress ipAddress = IPAddress.Parse("127.0.0.1");
                try
                {
                    cliente.Connect(ipAddress, port); // connect to the server
                    Console.WriteLine("Connection has been made with the server");

                    // Get a stream object for reading and writing
                    NetworkStream stream = cliente.GetStream();

                    // Send a message to the server
                    JObject message = new JObject();
                    message["username"] = "ra";
                    message["password"] = "ma";
                    string jsonString = message.ToString();
                    byte byteValue = 101;




                    byte[] data_len_bytes = BitConverter.GetBytes(jsonString.Length);
                    //reverse to reverse the endian orientation 
                    data_len_bytes = data_len_bytes.Reverse().ToArray();




                    var messageBytes = Encoding.UTF8.GetBytes(jsonString);

                    byte[] message_and_len = data_len_bytes.Concat(messageBytes).ToArray();

                    var full_msg_byte = Enumerable.Prepend(message_and_len, byteValue).ToArray();

                    stream.Write(full_msg_byte, 0, full_msg_byte.Length);


                    // Receive response from the server
                    byte[] len_buffer = new byte[5];
                    int len_bytesRead = stream.Read(len_buffer, 0, len_buffer.Length);
                    //guess whos fucking back
                    int data_len = (len_buffer[1] << 24) | (len_buffer[2] << 16) | (len_buffer[3] << 8) | len_buffer[4];

                    byte[] buffer = new byte[data_len];



                    //read from stream 
                    int bytesRead = stream.Read(buffer, 0, buffer.Length);
                    //get the string 
                    string utf8String = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                    //turn string into json 
                    JObject jsonObject = JObject.Parse(utf8String);
                    
                    MessageBox.Show($"Response from server: {jsonObject}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                }
            }


        }

        public MainMenu()
        {
            InitializeComponent();
            rndfunc();
        }

        private void login_Click(object sender, RoutedEventArgs e)
        {
            
            NavigationService?.Navigate(new Login());
        }

        private void signup_Click(object sender, RoutedEventArgs e)
        {

            NavigationService?.Navigate(new Signup());
            
        }
        private void exit_Click(object sender, RoutedEventArgs e)
        {
            // Get the main window of the application
            Window mainWindow = Application.Current.MainWindow;

            // Close the main window (which effectively closes the application)
            mainWindow.Close();
        }
    }
}
