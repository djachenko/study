using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Input;
using PacMan.Annotations;
using PacMan.Model;
using PacMan.Helpers;
using PacMan.Model.Exceptions;

namespace GUI.ViewModels
{
    public sealed class GameViewModel : INotifyPropertyChanged
    {
        [UsedImplicitly]
        public ObservableCollection<MoveButtonViewModel> MoveButtons { get; set; }
        
        private Game Game { get; set; }

        public FieldViewModel Field { get; set; }
        public string Text 
        {
            get { return Game.Started ? "Stop" : "Start"; }
        }

        public int Points
        {
            get { return Game.LevelPoints; }
        }

        public int Lives
        {
            get { return Game.PlayerLives; }
        }

        public int Total
        {
            get { return Game.CampaignPoints; }
        }

        public int Level
        {
            get { return Game.LevelNumber; }
        }

        private Dictionary<Key, Direction> KeyMappings { get; set; }

        internal event EventHandler<SaveRecordEventArgs> SaveRecord;

        internal GameViewModel()
        {
            Game = new Game();

            Field = new FieldViewModel(Game.Field);
            KeyMappings = new Dictionary<Key, Direction>();

            try
            {
                SetKeyMappings();
            }
            catch (SettingsNotValidException)
            {
                const string header = "Settings error";
                const string text = "An error was encountered while trying to load settings. Maybe you've changed them or they were corruppted somewhere outside. So, settings were reset to defaults.";
                const MessageBoxButton button = MessageBoxButton.OK;
                const MessageBoxImage icon = MessageBoxImage.Warning;

                MessageBox.Show(text, header, button, icon);
            }
            

            Game.StateChanged += (sender, args) => OnPropertyChanged("Text");
            Game.FieldReseted += (sender, args) =>
            {
                Field = new FieldViewModel(Game.Field);

                OnPropertyChanged("Field");
            };

            Game.PointsChanged += (sender, args) =>
            {
                OnPropertyChanged("Points");
                OnPropertyChanged("Total");
            };
            Game.PlayerLivesChanged += (sender, args) => OnPropertyChanged("Lives");
            Game.PlayerDied += (sender, args) => SaveRecord.Raise(sender, args);
            Game.LevelChanged += (sender, args) => OnPropertyChanged("Level");

            Settings.Instance.SettingsChanged += (sender, args) => SetKeyMappings();

            var count = 0;

            MoveButtons = new ObservableCollection<MoveButtonViewModel>(Direction.Values.Select(direction => new MoveButtonViewModel
            {
                Direction = direction, 
                Origin = Game, 
                Name = direction.Name.Substring(0, 1),
                Index = count++
            }));
        }

        private void SetKeyMappings()
        {
            var settings = Settings.Instance;

            foreach (var keyPair in settings.Keys)
            {
                Key key;

                if (Enum.TryParse(keyPair.Value, out key))
                {
                    KeyMappings[key] = keyPair.Key;
                }
            }
        }

        internal void StartStop()
        {
            Game.StartStop();
        }

        internal void RestartLevel()
        {
            Game.RestartLevel();
        }

        public void RestartCampaign()
        {
            Game.RestartCampaign();
        }

        internal void HandleKeyDown(object sender, KeyEventArgs e)
        {
            var key = e.Key;

            if (KeyMappings.ContainsKey(key) && Game.PlayerDirection != KeyMappings[key])
            {
                Game.PlayerDirection = KeyMappings[key];
            }
        }

        internal void HandleKeyUp(object sender, KeyEventArgs e)
        {
            var key = e.Key;

            if (KeyMappings.ContainsKey(key) && Game.PlayerDirection == KeyMappings[key])
            {
                Game.PlayerDirection = null;
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        private void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged.Raise(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
