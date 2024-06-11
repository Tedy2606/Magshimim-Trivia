using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.CompilerServices;
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
    public partial class Results : Page
    {
        private NetworkStream _stream;

        public Results(NetworkStream stream, int correctCount, int totalAnswerTime)
        {
            InitializeComponent();

            this._stream = stream;
            this.correctAnswers.Text += correctCount.ToString();

            //replace thiw with acg once we start actually looking at what is in the results
            this.averageAnswerTime.Text += totalAnswerTime.ToString() + "s";

            //open results and calculate points ( finish the db function to submit data)
            JObject message = new JObject();
            byte code = 144;

            Networker networker = new Networker();
            JObject jsonObject = networker.sendAndRecive(message, this._stream, code);

            if (!jsonObject.ContainsKey("message"))
            {
                
            }
            else
            {
                MessageBox.Show($"Response from server: {jsonObject}");
            }

        }
    }
}
