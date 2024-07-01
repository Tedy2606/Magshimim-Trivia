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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            frame.Navigate(new ServerIP());
        }

        public void SwitchThemes_Keyboard(object sender, KeyEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.LeftCtrl))
            {
                if (Keyboard.IsKeyDown(Key.LeftShift) && Keyboard.IsKeyDown(Key.N))
                {
                    // Theme for adults (Ctrl + Shift + N)
                    AppTheme.ChangeTheme(new Uri("Themes/Adult.xaml", UriKind.Relative));
                }
                else if (Keyboard.IsKeyDown(Key.R))
                {
                    // Theme for minors (Ctrl + R)
                    AppTheme.ChangeTheme(new Uri("Themes/Minor.xaml", UriKind.Relative));
                }
            }
        }
    }
}
