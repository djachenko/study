using System.Windows.Input;

namespace WpfApplicationPacMan.Model.Settings
{
    public sealed class KeyBindingSettings
    {
        public Key UpKey
        {
            get;
            set;
        }
        public Key DownKey
        {
            get;
            set;
        }
        public Key LeftKey
        {
            get;
            set;
        }
        public Key RightKey
        {
            get;
            set;
        }
        public Key PauseKey
        {
            get;
            set;
        }

        public KeyBindingSettings()
        {
            UpKey = Key.Up;
            DownKey = Key.Down;
            LeftKey = Key.Left;
            RightKey = Key.Right;
            PauseKey= Key.Space;
        }
    }
}
