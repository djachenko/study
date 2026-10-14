using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace Gui.ViewModels {
    internal sealed class HiscoresWindowViewModel : INotifyPropertyChanged {
        public event PropertyChangedEventHandler PropertyChanged;

        private ObservableCollection<HiscoreViewModel> _hiscores;

        public ObservableCollection<HiscoreViewModel> Hiscores {
            get { return _hiscores; }
            private set {
                _hiscores = value; 
                OnPropertyChanged(nameof(Hiscores));
            }
        }

        public void SetHiscores(IEnumerable<HiscoreViewModel> vms) {
            Hiscores = new ObservableCollection<HiscoreViewModel>(vms);
        }

        private void OnPropertyChanged(string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
