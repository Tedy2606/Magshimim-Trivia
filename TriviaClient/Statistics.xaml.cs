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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
        private NetworkStream _stream;
        public Statistics(NetworkStream stream)
        {
            InitializeComponent();
            this._stream = stream;  
        }

        private void back_Click(object sender, RoutedEventArgs e)
        {
            if (NavigationService.CanGoBack)
            {
                NavigationService?.GoBack();
            }
        }

        private void playerStatistics_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new PlayerStatistics(this._stream));
        }

        private void highScores_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new HighScores(this._stream));
        }
    }
}
