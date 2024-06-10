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
    /// Interaction logic for Results.xaml
    /// </summary>
    public partial class WaitingResults : Page
    {
        private NetworkStream _stream;

        public WaitingResults(NetworkStream stream, int correctCount, int totalTime)
        {
            InitializeComponent();
            this._stream = stream;
            JObject message = new JObject();
            string jsonString = message.ToString();
            byte code = 144;


            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                NavigationService?.Navigate(new Results(this._stream, jsonObject, correctCount,  totalTime));
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }

        }
    }
}
