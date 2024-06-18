using System;
using System.Collections.Generic;
using System.IO;
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
    /// Interaction logic for AddQuestion.xaml
    /// </summary>
    public partial class AddQuestion : Page
    {
        private NetworkStream _stream;

        public AddQuestion(NetworkStream stream)
        {
            InitializeComponent();
            this._stream = stream;
        }
    }
}
