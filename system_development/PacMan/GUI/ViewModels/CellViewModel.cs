using System.ComponentModel;
using System.Runtime.CompilerServices;
using PacMan.Annotations;
using PacMan.Helpers;
using PacMan.Model.Cells;

namespace GUI.ViewModels
{
    public sealed class CellViewModel : INotifyPropertyChanged
    {
        [UsedImplicitly]
        public int X
        {
            get { return Origin.X; }
        }

        [UsedImplicitly]
        public int Y
        {
            get { return Origin.Y; }
        }

        public int Value
        {
            get { return Origin.GetRepresentation(); }
        }

        public Cell Origin { get; private set; }

        public CellViewModel(Cell origin)
        {
            Origin = origin;

            origin.CoordinatesChanged += (sender, args) =>
            {
                OnPropertyChanged("X");
                OnPropertyChanged("Y");
            };

            origin.RepresentationChanged += (sender, args) => OnPropertyChanged("Value");
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        private void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged.Raise(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
