using System.ComponentModel;
using System.Runtime.CompilerServices;
using PacMan.Annotations;
using PacMan.Helpers;
using PacMan.Model;

namespace GUI.ViewModels
{
    public sealed class AddNewRecordDialogViewModel : INotifyPropertyChanged
    {
        public const int NameMaxLength = 21;
        private string _name;
        public string Text { get; set; }

        public string Name
        {
            get { return _name; }
            set
            {
                if (_name != value)
                {
                    _name = value;
                    OnPropertyChanged();
                }
            }
        }

        private int Score { get; set; }

        internal AddNewRecordDialogViewModel(int score)
        {
            Score = score;

            Text = "Congratulations! You've scored new record: " +
                   Score +
                   ". In order to save your record, I need your name. So, please, type it here:";

            RecordTable.LoadAndCheck();
        }

        public bool OnOkButtonClick()
        {
            if (Name.Length > NameMaxLength)
            {
                return false;
            }

            RecordTable.Instance.Add(new Record(Name, Score));

            return true;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        private void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged.Raise(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
