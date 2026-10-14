using System;
using System.Windows;
using GUI.ViewModels;
using PacMan.Helpers;
using PacMan.Model.Exceptions;

namespace GUI.Views
{
    public sealed partial class GameView
    {
        private GameViewModel _viewModel;

        private GameViewModel ViewModel
        {
            get { return _viewModel; }
            set
            {
                _viewModel = value; 
                
                _viewModel.SaveRecord += ShowSaveRecordWindow;
            }
        }

        public GameView()
        {
            InitializeComponent();
            
            DataContextChanged += (sender, args) =>
            {
                var game = DataContext as GameViewModel;

                if (game != null)
                {
                    ViewModel = game;
                }
            };
        }

        private void StartStop(object sender, RoutedEventArgs e)
        {
            if (ViewModel != null)
            {
                ViewModel.StartStop();
            }
        }

        private void RestartLevel(object sender, RoutedEventArgs e)
        {
            if (ViewModel != null)
            {
                ViewModel.RestartLevel();
            }
        }

        private void RestartCampaign(object sender, RoutedEventArgs e)
        {
            if (ViewModel != null)
            {
                ViewModel.RestartCampaign();
            }
        }

        private void OnLoaded(object sender, RoutedEventArgs e)
        {
            var window = Window.GetWindow(this);

            if (window != null && ViewModel != null)
            {
                window.KeyDown += ViewModel.HandleKeyDown;
                window.KeyUp += ViewModel.HandleKeyUp;
            }
        }

        private void OnRecordTableButtonOnClick(object sender, RoutedEventArgs e)
        {
            try
            {
                var recordsWindow = new RecordTableDialog { Owner = Window.GetWindow(this) };

                recordsWindow.ShowDialog();
            }
            catch (ResourceFileNotValidException)
            {
                const string header = "Record table not accessible";
                const string text = "An error was encountered while trying to load record table. Maybe you've changed it or it was corruppted somewhere outside. Anyway, we cannot show it. Sorry";
                const MessageBoxButton button = MessageBoxButton.OK;
                const MessageBoxImage icon = MessageBoxImage.Error;

                MessageBox.Show(text, header, button, icon);
            }
        }

        private void ShowSaveRecordWindow(object sender, EventArgs eventArgs)
        {
            var saveRecordEventArgs = eventArgs as SaveRecordEventArgs;

            if (saveRecordEventArgs != null)
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    try
                    {
                        var saveRecordWindow = new AddNewRecordDialog
                        {
                            Owner = Window.GetWindow(this),
                            DataContext = new AddNewRecordDialogViewModel(saveRecordEventArgs.Score)
                        };

                        saveRecordWindow.ShowDialog();
                    }
                    catch (ResourceFileNotValidException)
                    {
                        const string header = "Record table not accessible";
                        const string text = "An error was encountered while trying to load record tavle. Maybe you've changed it or it was corruppted somewhere outside. Anyway, we cannot save your result, though you've earned it. Sorry.";
                        const MessageBoxButton button = MessageBoxButton.OK;
                        const MessageBoxImage icon = MessageBoxImage.Error;

                        MessageBox.Show(text, header, button, icon);
                    }
                });
            }
        }

        private void OnSettingsButtonClick(object sender, RoutedEventArgs e)
        {
            var window = new SettingsDialog { Owner = Window.GetWindow(this) };

            window.ShowDialog();
        }

        private void OnAboutButtonClick(object sender, RoutedEventArgs e)
        {
            var about = new AboutDialog();

            about.ShowDialog();
        }
    }
}
