using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using WpfApplicationPacMan.Model.Settings;

namespace WpfApplicationPacMan.View
{
    /// <summary>
    /// Interaction logic for Settings.xaml
    /// </summary>
    public partial class Settings
    {
        private bool _ediTmodeOn;
        private Button _currentButton;
        private readonly KeyBindingSettings _keyBindingSettings;
        private Command _currentButtonForChanging;

        public Settings(KeyBindingSettings keyBindingSettings)
        {
            InitializeComponent();
            _keyBindingSettings = keyBindingSettings;
            UpButton.Content = _keyBindingSettings.UpKey.ToString();
            DownButton.Content = _keyBindingSettings.DownKey.ToString();
            LeftButton.Content = _keyBindingSettings.LeftKey.ToString();
            RightButton.Content = _keyBindingSettings.RightKey.ToString();
            PauseButton.Content = _keyBindingSettings.PauseKey.ToString();
        }

        

        private void OnKeyDown(object sender, KeyEventArgs keyEventArgs)
        {
            bool switcher = false;
            
            if (!_ediTmodeOn)
                return;
            _ediTmodeOn = false;

            if (_currentButtonForChanging != Command.Down && keyEventArgs.Key == _keyBindingSettings.DownKey)
            {
                switcher = true;
            }
            if (_currentButtonForChanging != Command.Up && keyEventArgs.Key == _keyBindingSettings.UpKey)
            {
                switcher = true;
            } 
            if (_currentButtonForChanging != Command.Down && keyEventArgs.Key == _keyBindingSettings.LeftKey)
            {
                switcher = true;
            } 
            if (_currentButtonForChanging != Command.Down && keyEventArgs.Key == _keyBindingSettings.RightKey)
            {
                switcher = true;
            } 
            if (_currentButtonForChanging != Command.Down && keyEventArgs.Key == _keyBindingSettings.PauseKey)
            {
                switcher = true;
            }

            switch (_currentButtonForChanging)
            {
                case Command.Down:
                    if (switcher)
                    {
                        _currentButton.Content = _keyBindingSettings.DownKey;
                        return;
                    }
                    _keyBindingSettings.DownKey = keyEventArgs.Key;
                    break;
                case Command.Up:
                    if (switcher)
                    {
                        _currentButton.Content = _keyBindingSettings.UpKey;
                        return;
                    }
                    _keyBindingSettings.UpKey = keyEventArgs.Key;
                    break;
                case Command.Left:
                    if (switcher)
                    {
                        _currentButton.Content = _keyBindingSettings.LeftKey;
                        return;
                    }
                    _keyBindingSettings.LeftKey = keyEventArgs.Key;
                    break;
                case Command.Right:
                    if (switcher)
                    {
                        _currentButton.Content = _keyBindingSettings.RightKey;
                        return;
                    }
                    _keyBindingSettings.RightKey = keyEventArgs.Key;
                    break;
                case Command.Pause:
                    if (switcher)
                    {
                        _currentButton.Content = _keyBindingSettings.PauseKey;
                        return;
                    }
                    _keyBindingSettings.PauseKey = keyEventArgs.Key;
                    break;
            }

            _currentButton.Content = keyEventArgs.Key.ToString();
            //callBack(keyBindingSettings);
            //save();
        }

        private enum Command
        {
            Up,
            Down,
            Left,
            Right,
            Pause
        };


        #region buttons handlers
        //TODO: объединить их в один
        private void RightButton_OnClick(object sender, RoutedEventArgs e)
        {
            _ediTmodeOn = true;
            _currentButton = ((Button)e.Source);
            _currentButton.Content = "PRESS KEY!";
            _currentButtonForChanging = Command.Right;
        }
        private void LeftButton_OnClick(object sender, RoutedEventArgs e)
        {
            _ediTmodeOn = true;
            _currentButton = ((Button)e.Source);
            _currentButton.Content = "PRESS KEY!";
            _currentButtonForChanging = Command.Left;
        }
        private void UpButton_OnClick(object sender, RoutedEventArgs e)
        {
            _ediTmodeOn = true;
            _currentButton = ((Button)e.Source);
            _currentButton.Content = "PRESS KEY!";
            _currentButtonForChanging = Command.Up;
        }
        private void DownButton_OnClick(object sender, RoutedEventArgs e)
        {
            _ediTmodeOn = true;
            _currentButton = ((Button)e.Source);
            _currentButton.Content = "PRESS KEY!";
            _currentButtonForChanging = Command.Down;
        }
        private void PauseButton_OnClick(object sender, RoutedEventArgs e)
        {
            _ediTmodeOn = true;
            _currentButton = ((Button)e.Source);
            _currentButton.Content = "PRESS KEY!";
            _currentButtonForChanging = Command.Pause;
        }

        #endregion
    }
}
