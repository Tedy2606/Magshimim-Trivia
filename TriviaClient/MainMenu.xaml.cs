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
        private NetworkStream _stream;

        public MainMenu()
        {
            //no defines 
            const int port = 56812;

            TcpClient client = new TcpClient();
            
            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");
            try
            {
                 client.Connect(ipAddress, port); // connect to the server
                 Console.WriteLine("Connection has been made with the server");

                 // Get a stream object for reading and writing
                 this._stream = client.GetStream();

            }
            catch (Exception ex)
            {
                 Console.WriteLine($"Error: {ex.Message}");
            }
            

            InitializeComponent();
            
        }

        private void login_Click(object sender, RoutedEventArgs e)
        {
            
            NavigationService?.Navigate(new Login(this._stream));
        }

        private void signup_Click(object sender, RoutedEventArgs e)
        {

            NavigationService?.Navigate(new Signup(this._stream));
            
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
