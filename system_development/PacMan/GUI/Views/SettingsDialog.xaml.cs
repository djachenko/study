using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using GUI.ViewModels;
using PacMan.Model;
using PacMan.Model.Exceptions;

namespace GUI.Views
{
    public sealed partial class SettingsDialog
    {
        private Dictionary<TextBox, Direction> BoxMapping { get; set; }

        public SettingsDialog()
        {
            InitializeComponent();

            BoxMapping = new Dictionary<TextBox, Direction>();

            DataContext = new SettingsDialogViewModel();
        }

        private void ReadSettings(object sender, KeyEventArgs e)
        {
            var box = sender as TextBox;
            var viewModel = DataContext as SettingsDialogViewModel;

            if (box != null && viewModel != null)
            {
                try
                {
                    viewModel.ChangeSettings(BoxMapping[box], e.Key);
                }
                catch (KeyBindedException)
                {
                    const string header = "Key already binded";
                    const string text = "This key is already binded to other direction. Please, choose some other key";
                    const MessageBoxButton button = MessageBoxButton.OK;
                    const MessageBoxImage icon = MessageBoxImage.Error;

                    MessageBox.Show(text, header, button, icon);
                }


                box.Focus();
            }
        }

        private void RememberMapping(object sender, RoutedEventArgs e)
        {
            var box = sender as TextBox;
            var viewModel = DataContext as SettingsDialogViewModel;

            if (box != null && viewModel != null)
            {
                foreach (var settingEntry in viewModel.Entries.Where(settingEntry => settingEntry.Key.Equals(box.Text)))
                {
                    BoxMapping[box] = settingEntry.Direction;

                    break;
                }
            }
        }

        private void OnOkClick(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void OnResetClick(object sender, RoutedEventArgs e)
        {
            var viewModel = DataContext as SettingsDialogViewModel;

            if (viewModel != null)
            {
                viewModel.Reset();
            }
        }
    }
}
