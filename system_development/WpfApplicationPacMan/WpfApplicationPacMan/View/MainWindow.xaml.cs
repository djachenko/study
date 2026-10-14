using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using WpfApplicationPacMan.Model;
using WpfApplicationPacMan.Model.Settings;
using WpfApplicationPacMan.ViewModel;

namespace WpfApplicationPacMan.View
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        private Ellipse _pacmanShape;
        private readonly MainViewModel _mainViewModel;
        private readonly KeyBindingSettings _keyBindingSettings = new KeyBindingSettings();
        private readonly List<UIElement> _wallsList = new List<UIElement>();
        private readonly List<UIElement> _powerPillsList = new List<UIElement>();
        private readonly List<UIElement> _ghostsList = new List<UIElement>();

        private readonly Dictionary<Position, UIElement> _dictionary = new Dictionary<Position, UIElement>(); 
        private Color _ghostsColor = Colors.Red;
        
        public MainWindow()
        {
            InitializeComponent();
            _mainViewModel = new MainViewModel();
            DataContext = _mainViewModel;
            _mainViewModel.PropertyChanged += PropertyChangedEventHandler;
            _mainViewModel.GameFinishedHandler(FinishGameCanvas);
            InitPacman();
            _mainViewModel.NewLevelLoadedHandler(DrawNewLevelHadler);
            BindMyKeys();
            // DrawNewLevel();
        }

        private void DrawNewLevelHadler(object sender, EventArgs e)
        {
            Dispatcher.Invoke((DrawNewLevel));
        }

        #region bindings
        /// <summary>
        ///применяем все биндинги 
        /// </summary>
        private void BindMyKeys()
        {
            
            InputBindings.Clear();
            InputBindings.Add(new KeyBinding { Command = _mainViewModel.UpCommand, CommandParameter = _keyBindingSettings.UpKey, Key = _keyBindingSettings.UpKey }); //(_mainViewModel.UpCommand, _keyBindingSettings.UpKey, ModifierKeys.None));
            InputBindings.Add(new KeyBinding { Command = _mainViewModel.DownCommand, CommandParameter = _keyBindingSettings.DownKey, Key = _keyBindingSettings.DownKey });
            InputBindings.Add(new KeyBinding { Command = _mainViewModel.LeftCommand, CommandParameter = _keyBindingSettings.LeftKey, Key = _keyBindingSettings.LeftKey });
            InputBindings.Add(new KeyBinding { Command = _mainViewModel.RightCommand, CommandParameter = _keyBindingSettings.RightKey, Key = _keyBindingSettings.RightKey });
            InputBindings.Add(new KeyBinding { Command = _mainViewModel.PauseCommand, CommandParameter = _keyBindingSettings.PauseKey, Key = _keyBindingSettings.PauseKey });
        }

        #endregion

        private void PropertyChangedEventHandler(object sender, PropertyChangedEventArgs propertyChangedEventArgs)
        {
            switch (propertyChangedEventArgs.PropertyName)
            {
                case "PacmanPosition":
                    Dispatcher.Invoke((DrawPacman));
                    break;
                case "SwitchToNewLevel":
                    Dispatcher.Invoke((DrawNewLevel));
                    break;
                case "GhostsPositions":
                    Dispatcher.Invoke((RedrawGhosts));
                    break;
                case "PillsPositions":
                    Dispatcher.Invoke((RedrawPills));
                    break;
                case "PowerPillsPositions":
                    Dispatcher.Invoke((RedrawPowerPills));
                    break;
                case "IsAttackedModeOn":
                    Dispatcher.Invoke((SetGhostsColor));
                    break;
                case "GameOver":
                    Dispatcher.Invoke((GameOver));
                    break;
                case "Pause":
                    break;
            }
        }

        private void GameOver()
        {
            GameCanvas.Children.Clear();
            GameCanvas.Children.Add(new TextBlock { Text = "GAME OVER" , HorizontalAlignment = HorizontalAlignment.Center, VerticalAlignment = VerticalAlignment.Center});
        }

        #region draw objects

        void InitPacman()
        {
            _pacmanShape = new Ellipse
            {
                Fill = new SolidColorBrush(Colors.Yellow),
                Height = _mainViewModel.PixelsOnCell,
                Width = _mainViewModel.PixelsOnCell,
                Name = "pacmanShape"
            };
            RegisterName(_pacmanShape.Name, _pacmanShape);
            var myDoubleAnimation = new DoubleAnimation
            {
                From = 1.0,
                To = 0.5,
                Duration = new Duration(TimeSpan.FromMilliseconds(600)),
                AutoReverse = true,
                RepeatBehavior = RepeatBehavior.Forever
            };

            var myStoryboard = new Storyboard();
            myStoryboard.Children.Add(myDoubleAnimation);
            Storyboard.SetTargetName(myDoubleAnimation, _pacmanShape.Name);
            Storyboard.SetTargetProperty(myDoubleAnimation, new PropertyPath(OpacityProperty));

            // Use the Loaded event to start the Storyboard.
            //GameCanvas.Children.Add(_pacmanShape);
            myStoryboard.Begin(this);
        }

        private void DrawNewLevel()
        {
            GameCanvas.Children.Clear();
            
            DrawPacman();
            GameCanvas.Children.Add(_pacmanShape);
            GameCanvas.Height = _mainViewModel.FieldHeight;
            GameCanvas.Width = _mainViewModel.FieldWidth;

            NewRedrawPills();
            RedrawPowerPills();
            RedrawWalls();
            RedrawGhosts();
        }

        private void DrawPacman()
        {
            Canvas.SetLeft(_pacmanShape, _mainViewModel.PacmanPosition.CoordinateX * _mainViewModel.PixelsOnCell);
            Canvas.SetTop(_pacmanShape, _mainViewModel.PacmanPosition.CoordinateY * _mainViewModel.PixelsOnCell);
        }

        #endregion draw objects

        #region init shapes for walls, pills, ghosts
        //TODO: сжать до одного метода

        /// <summary>
        /// рисует стены. удаление стен из канваса происходит в начале метода DrawNewLevel
        /// там сносится все, поэтому отдельно здесь не нужно удалять стены 
        /// </summary>
        private void RedrawWalls()
        {
            _wallsList.Clear();

            var list = _mainViewModel.GetListWalls();
            foreach (var position in list)
            {
                var rect = new Rectangle
                {
                    Height = _mainViewModel.PixelsOnCell,
                    Width = _mainViewModel.PixelsOnCell,
                    Fill = new SolidColorBrush(Colors.DarkSlateGray)
                };
                Canvas.SetLeft(rect, position.CoordinateX*_mainViewModel.PixelsOnCell);
                Canvas.SetTop(rect, position.CoordinateY*_mainViewModel.PixelsOnCell);
                _wallsList.Add(rect);
            }
            foreach (var rectangle in _wallsList)
            {
                GameCanvas.Children.Add(rectangle);
            }
        }

        private void RedrawGhosts()
        {
            foreach (var element in _ghostsList)
            {
                GameCanvas.Children.Remove(element);
            }
            _ghostsList.Clear();
            foreach (var position in _mainViewModel.GhostsPositions)
            {
                var rect = new Rectangle
                {
                    Height = _mainViewModel.PixelsOnCell,
                    Width = _mainViewModel.PixelsOnCell,
                    Fill = new SolidColorBrush(_ghostsColor)
                };
                Canvas.SetLeft(rect, position.CoordinateX*_mainViewModel.PixelsOnCell);
                Canvas.SetTop(rect, position.CoordinateY*_mainViewModel.PixelsOnCell);
                _ghostsList.Add(rect);
            }
            foreach (var rectangle in _ghostsList)
            {
                GameCanvas.Children.Add(rectangle);
            }
        }


        private void RedrawPowerPills()
        {
            if (_powerPillsList == null) return;

            foreach (var element in _powerPillsList)
            {
                GameCanvas.Children.Remove(element);
            }
            _powerPillsList.Clear();
            foreach (var position in _mainViewModel.PowerPillsPositions)
            {
                var pill = new Ellipse
                {
// ReSharper disable PossibleLossOfFraction
                    Height = _mainViewModel.PixelsOnCell / 2,
// ReSharper restore PossibleLossOfFraction
// ReSharper disable PossibleLossOfFraction
                    Width = _mainViewModel.PixelsOnCell / 2,
// ReSharper restore PossibleLossOfFraction
                    Fill = new SolidColorBrush(Colors.Green)
                };
                Canvas.SetLeft(pill,
                    (position.CoordinateX) * _mainViewModel.PixelsOnCell +
                    (_mainViewModel.PixelsOnCell - pill.Height) / 3);
                Canvas.SetTop(pill,
                    (position.CoordinateY) * _mainViewModel.PixelsOnCell +
                    (_mainViewModel.PixelsOnCell - pill.Height) / 3);
                _powerPillsList.Add(pill);
            }
            foreach (var ellipse in _powerPillsList)
            {
                GameCanvas.Children.Add(ellipse);
            }
        }


        private void NewRedrawPills()
        {
            _dictionary.Clear();

            foreach (var position in _mainViewModel.PillsPositions)
            {
                var pill = new Ellipse
                {
                    // ReSharper disable once PossibleLossOfFraction
                    Height = _mainViewModel.PixelsOnCell / 2,
                    // ReSharper disable once PossibleLossOfFraction
                    Width = _mainViewModel.PixelsOnCell / 2,
                    Fill = new SolidColorBrush(Colors.Yellow)
                };
                Canvas.SetLeft(pill,
                    (position.CoordinateX) * _mainViewModel.PixelsOnCell +
                    (_mainViewModel.PixelsOnCell - pill.Height) / 3);
                Canvas.SetTop(pill,
                    (position.CoordinateY) * _mainViewModel.PixelsOnCell +
                    (_mainViewModel.PixelsOnCell - pill.Height) / 3);
                _dictionary.Add(position, pill);

            }
            foreach (var ellipse in _dictionary.Values)
            {
                GameCanvas.Children.Add(ellipse);
            }
        }

        private void RedrawPills()
        {
            var a = from element in _dictionary where IsDeleted(element) select element.Key;
            foreach (var ellipse in a)
            {
                GameCanvas.Children.Remove(_dictionary[ellipse]);
            }
        }

        private bool IsDeleted(KeyValuePair<Position, UIElement> element)
        {
            return _mainViewModel.PillsPositions.All(position => position.CoordinateX != element.Key.CoordinateX || position.CoordinateY != element.Key.CoordinateY);
        }

        #endregion


        #region on buttons clicks liststeners
        private void OnSettingsClickListener(object sender, RoutedEventArgs e)
        {
            var settings = new Settings(_keyBindingSettings);
            _mainViewModel.Pause(null);
            settings.ShowDialog();
            BindMyKeys();
            
        }
        private void OnChampionsClickListener(object sender, RoutedEventArgs e)
        {
            var champions = new Champions {DataContext = _mainViewModel};
            _mainViewModel.Pause(null);
            champions.ShowDialog();
            BindMyKeys();
        }
        private void OnAboutClickListener(object sender, RoutedEventArgs e)
        {
            var about = new About();
            _mainViewModel.Pause(null);
            about.ShowDialog();
        }

        private void OnExitButtonClick(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void OnNewGameClickListener(object sender, RoutedEventArgs e)
        {
            _mainViewModel.NewGame();
        }


        #endregion on buttons clicks liststeners

        private void SetGhostsColor()
        {
            _ghostsColor = _mainViewModel.IsAttackedModeOn ? Colors.Red : Colors.Orchid;
        }

        private void FinishGameCanvas(object sender, EventArgs e)
        {
            Dispatcher.Invoke(FinishGameCanvasFromDispatcher);
            
        }
        private void FinishGameCanvasFromDispatcher()
        {
            var setNameDialog = new SetNameDialog {DataContext = _mainViewModel};
            if(_mainViewModel.IsNewRecordsman())
                setNameDialog.ShowDialog();
        }
    }
}
