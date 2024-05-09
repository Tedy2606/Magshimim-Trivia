using System;
using System.Collections.Generic;
using System.Linq;
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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Page
    {
        public MainMenu()
        {
            InitializeComponent();
            
        }

        private void login_Click(object sender, RoutedEventArgs e)
        {
            
            NavigationService?.Navigate(new Login());
        }

        private void signup_Click(object sender, RoutedEventArgs e)
        {

            NavigationService?.Navigate(new Signup());
            
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
