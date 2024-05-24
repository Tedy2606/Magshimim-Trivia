using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Numerics;
using System.Text;
using System.Text.RegularExpressions;
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
using System.Windows.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MemberRoom.xaml
    /// </summary>
    public partial class MemberRoom : Page
    {
        private NetworkStream _stream;
        private DispatcherTimer _dispatcherTimer;

        public MemberRoom(NetworkStream stream, string roomName)
        {
            this._stream = stream;
            InitializeComponent();

            this.roomName.Text = roomName;

            // initialize the dispatcher timer
            this._dispatcherTimer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(3)
            };
            this._dispatcherTimer.Tick += this.DispatcherTimer_Tick;

            // start refreshing the rooms
            this._dispatcherTimer.Start();
            this.refresh();
        }

        private void DispatcherTimer_Tick(object sender, EventArgs e)
        {
            this.refresh();
        }

        private void leaveRoom_Click(object sender, RoutedEventArgs e)
        {
            leaveRoom();
        }

        private void leaveRoom()
        {
            // Send a message to the server
            JObject message = new JObject();
            string jsonString = message.ToString();
            byte code = 121;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                this._dispatcherTimer.Stop();
                NavigationService?.GoBack();
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
        }

        private void refresh()
        {
            // clear the buttons when refreshing
            stackPanel.Children.Clear();

            // Send a message to the server
            JObject message = new JObject();

            string jsonString = message.ToString();
            byte code = 120;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (jsonObject.ContainsKey("message"))
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
            else
            {
                // get the room activity status
                int hasGameBegun = jsonObject.Value<int>("hasGameBegun");

                if (hasGameBegun == 0) // leave if room is closed
                {
                    leaveRoom();
                }
                else if (hasGameBegun == 2) // game has started
                {
                    // TODO: move to questions page
                }

                // get the room players
                Regex regex = new Regex(@"\w+");

                string players = jsonObject.Value<string>("players");

                Boolean isAdmin = true;
                foreach (Match match in regex.Matches(players))
                {
                    string name = match.Value;

                    // Create the button of the room
                    TextBlock player = new TextBlock
                    {
                        Text = name,
                        Width = 360,
                        Height = 60,
                        Foreground = isAdmin ? Brushes.Orange : Brushes.White,
                        FontSize = 42,
                        FontFamily = new FontFamily("Arial"),
                        FontWeight = FontWeights.Bold,
                        TextAlignment = TextAlignment.Center
                    };

                    stackPanel.Children.Add(player);
                    isAdmin = false;
                }
            }
        }
    }
}
