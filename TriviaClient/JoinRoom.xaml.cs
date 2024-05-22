using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private NetworkStream _stream;
        public JoinRoom(NetworkStream stream)
        {
            this._stream = stream;
            InitializeComponent();

            refresh();
        }
        private void button_click(object sender, RoutedEventArgs e)
        {
            // Send a message to the server
            Button clickedButton = sender as Button;
            JObject message = new JObject();
            message["roomID"] = int.Parse(clickedButton.Tag.ToString());
            string jsonString = message.ToString();
            byte code = 112;
            

            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                NavigationService?.Navigate(new MemberRoom(this._stream, clickedButton.Content.ToString()));
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

        private void refresh_Click(object sender, RoutedEventArgs e)
        {
            refresh();
        }

        private void refresh()
        {
            // clear the buttons when refreshing
            stackPanel.Children.Clear();

            // Send a message to the server
            JObject message = new JObject();

            string jsonString = message.ToString();
            byte code = 117;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (jsonObject.ContainsKey("message"))
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
            else
            {
                Regex regex = new Regex(@"\b\w+:\d+\b");
                
                //get the button name - id string 
                string rooms = jsonObject.Value<string>("rooms");
                

                foreach (Match match in regex.Matches(rooms))
                {
                    // get the name and id of the room
                    string[] parsedMatch = match.Value.Split(':');
                    string name = parsedMatch[0];
                    string id = parsedMatch[1];

                    // Create the button of the room
                    Button button = new Button
                    {
                        Name = name,
                        Tag = id,

                        // Design
                        Content = name,
                        Width = 360,
                        Height = 60,
                        Background = Brushes.Orange,
                        FontSize = 36,
                        FontFamily = new FontFamily("Arial"),
                        FontWeight = FontWeights.Bold
                    };

                    button.Click += button_click;

                    // Create a border with rounded corners
                    Border border = new Border();
                    border.CornerRadius = new CornerRadius(10);
                    //border.Child = buttons[count];

                    //// add it to the button
                    //buttons[count].Content = border;


                    // *** end design here ***
                    stackPanel.Children.Add(button);
                }
            }
        }
    }
}
