using System.Windows;
using GUI.ViewModels;
using PacMan.Model.Exceptions;

namespace GUI
{
    public sealed partial class MainWindow
    {
        public MainWindow()
        {
            InitializeComponent();

            try
            {
                var gameViewModel = new GameViewModel();

                GameView.DataContext = gameViewModel;
            }
            catch (GhostsNotValidException)
            {
                const string header = "AI error";
                const string text = "An error was encountered while trying to load AIs for Ghost entities. Maybe you've changed them or they were corruppted somewhere outside. Anyway, game cannot be started :(";
                const MessageBoxButton button = MessageBoxButton.OK;
                const MessageBoxImage icon = MessageBoxImage.Error;

                MessageBox.Show(text, header, button, icon);

                Close();
            }
        }
    }
}
