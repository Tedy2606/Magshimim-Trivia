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

            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

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

        private void statistics_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new PlayerStatistics(this._stream));
        }
    }
}
