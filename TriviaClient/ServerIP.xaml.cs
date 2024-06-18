using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Nodes;
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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for ServerIP.xaml
    /// </summary>
    public partial class ServerIP : Page
    {
        public ServerIP()
        {
            InitializeComponent();
        }

        private void localHost_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new MainMenu("127.0.0.1"));
        }

        private void ip_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                Regex regex = new Regex(@"\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b");

                if (regex.IsMatch(this.ip.Text))
                {
                    NavigationService?.Navigate(new MainMenu(ip.Text));
                }
                else
                {
                    MessageBox.Show($"Invalid IPv4 format");
                }
            }
        }
    }
}
