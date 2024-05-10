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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Page
    {

        async public void rndfunc() 
        {
            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");

            IPEndPoint ipEndPoint = new(ipAddress, 56812);
            using Socket client = new(
                ipEndPoint.AddressFamily,
                SocketType.Stream,
                ProtocolType.Tcp);

            await client.ConnectAsync(ipEndPoint);
            while (true)
            {
                // Send message.
                JObject message = new JObject();
                message["username"] = "t";
                message["password"] = "b";
                string jsonString = message.ToString();
                byte byteValue = 101;
                jsonString = ((char)byteValue) + jsonString.Length.ToString() + jsonString;
                var messageBytes = Encoding.UTF8.GetBytes(jsonString);
                _ = await client.SendAsync(messageBytes, SocketFlags.None);
                MessageBox.Show($"Socket client sent message: \"{jsonString}\"");

                // Receive ack.
                var buffer = new byte[1_024];
                var received = await client.ReceiveAsync(buffer, SocketFlags.None);
                var response = Encoding.UTF8.GetString(buffer, 0, received);
                MessageBox.Show($"Socket client sent message: \"{response}\"");
                string t = JsonConvert.SerializeObject(response);
                if (response == "")
                {
                   MessageBox.Show(
                        $"Socket client received acknowledgment: \"{response}\"");
                    break;
                }
                // Sample output:
                //     Socket client sent message: "Hi friends 👋!"
                //     Socket client received acknowledgment: ""

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
