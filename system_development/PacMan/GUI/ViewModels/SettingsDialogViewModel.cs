using System.Collections.ObjectModel;
using System.Windows.Input;
using PacMan.Annotations;
using PacMan.Model;

namespace GUI.ViewModels
{
    public sealed class SettingsDialogViewModel
    {
        public sealed class SettingEntry
        {
            public Direction Direction { get; set; }
            public string Key { get; set; }
            [UsedImplicitly]
            public int Index { get; set; }
        }

        public ObservableCollection<SettingEntry> Entries { get; private set; }

        public int Count
        {
            get { return Entries != null ? Entries.Count : 0; }
        }

        public SettingsDialogViewModel()
        {
            Entries = new ObservableCollection<SettingEntry>();

            Refresh();

            Settings.Instance.SettingsChanged += (sender, args) => Refresh();
        }

        void Refresh()
        {
            Entries.Clear();
            var count = 0;

            foreach (var mapping in Settings.Instance.Keys)
            {
                Entries.Add(new SettingEntry
                {
                    Direction = mapping.Key,
                    Key = mapping.Value,
                    Index = count++
                });
            }
        }

        internal void ChangeSettings(Direction direction, Key key)
        {
            switch (key)
            {
                case Key.Back:
                    Settings.Instance.Remove(direction);
                    break;
                default:
                    Settings.Instance.Change(direction, key.ToString());
                    break;
            }
        }

        internal void Reset()
        {
            Settings.Instance.ResetDefaults();
        }
    }
}
