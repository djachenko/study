using System.Windows;
using GUI.ViewModels;

namespace GUI.Views
{
    public sealed partial class AddNewRecordDialog
    {
        public AddNewRecordDialog()
        {
            InitializeComponent();

            DataContextChanged += (sender, args) =>
            {
                var viewModel = DataContext as AddNewRecordDialogViewModel;

                if (viewModel != null)
                {
                    OkButton.Click += (o, eventArgs) =>
                    {
                        if (!viewModel.OnOkButtonClick())
                        {
                            const string header = "Invalid name";
                            var text = "Your name shouldn't be empty and should have no more than " + 
                                AddNewRecordDialogViewModel.NameMaxLength + 
                                " letters.";
                            const MessageBoxButton button = MessageBoxButton.OK;
                            const MessageBoxImage icon = MessageBoxImage.Error;

                            MessageBox.Show(text, header, button, icon);
                        }
                        else
                        {
                            Close();
                        }
                    };
                }
            };
        }

        private void OnLoaded(object sender, RoutedEventArgs e)
        {
            Name.Text = string.Empty;
        }
    }
}
