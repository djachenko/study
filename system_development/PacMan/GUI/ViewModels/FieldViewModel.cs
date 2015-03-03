using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using PacMan.Annotations;
using PacMan.Helpers;
using PacMan.Model;

namespace GUI.ViewModels
{
    public sealed class FieldViewModel : INotifyPropertyChanged
    {
        [UsedImplicitly]
        public ObservableCollection<GridFieldLayerViewModel> Layers { get; private set; }

        public FieldViewModel(Field source)
        {
            Layers = new ObservableCollection<GridFieldLayerViewModel>();
            
            var count = 0;

            foreach (var type in source.OrderedTypes.Reverse())
            {
                Layers.Add(new GridFieldLayerViewModel(source.Layers[type], count++));
            }

            source.FieldUpdated += (sender, args) => OnPropertyChanged("Layers");
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        private void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged.Raise(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
