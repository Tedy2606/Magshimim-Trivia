﻿using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
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
            message["roomID"] = clickedButton.Tag.ToString();
            string jsonString = message.ToString();
            byte code = 112;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                //temp
                NavigationService?.Navigate(new MemberRoom(this._stream));
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
                //get the button name - id string 
                string rooms = jsonObject.Value<string>("rooms");
                int count = rooms.Count(c => c == ':'); // find out how many rooms are there
                Button[] buttons = new Button[count];
                count = 0;
                for (int i = 0; i < rooms.Length; i++)
                {

                    if (i == 0 || rooms[i].Equals(","))
                    {
                        int stopIndex = rooms.IndexOf(':', i);
                        string name = rooms.Substring(i, stopIndex - i - 1); // Extract the substring
                        stopIndex = rooms.IndexOf(',', i);
                        string id;
                        if (stopIndex == -1) // if there is no , (ie last id)
                        {
                            id = rooms.Substring(i + 1);
                        }
                        else
                        {
                            id = rooms.Substring(i + 1, stopIndex - i); // Extract the substring
                        }



                        buttons[count] = new Button
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

                        buttons[count].Click += button_click;

                        // Create a border with rounded corners
                        Border border = new Border();
                        border.CornerRadius = new CornerRadius(10);
                        //border.Child = buttons[count];

                        //// add it to the button
                        //buttons[count].Content = border;


                        // *** end design here ***
                        stackPanel.Children.Add(buttons[count]);
                        count++;
                    }

                }
            }
        }
    }
}
