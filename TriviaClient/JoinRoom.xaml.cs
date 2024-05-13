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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private NetworkStream _stream;
        public JoinRoom(NetworkStream stream)
        {
            this._stream = stream;
            InitializeComponent();

            // Send a message to the server
            JObject message = new JObject();
            
            string jsonString = message.ToString();
            byte code = 117;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                NavigationService?.Navigate(new Login(this._stream));
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }
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
                   


                    buttons[count] = new Button();
                    buttons[count].Name = name;
                    buttons[count].Tag = id;
                    buttons[count].Click += button_click;
                    // *** design here ***
                    
                   



                    // *** end design here ***
                    // Add the button to the window's content (assuming you have a grid named 'grid' as your window's root element)
                    grid.Children.Add(buttons[count]);


                    count++;
                }

            }


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
                NavigationService?.Navigate(new Login(this._stream));
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
    }
}
