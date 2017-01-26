using System.ComponentModel;
using pacman_litvinov.Models;
using System.Collections.ObjectModel;

namespace pacman_litvinov.ViewModels {
    class MultiObjectViewModel : INotifyPropertyChanged {
        public event PropertyChangedEventHandler PropertyChanged;

        private ObservableCollection<PointFeatureViewModel> pointFeatureVms 
            = new ObservableCollection<PointFeatureViewModel>();
        public ObservableCollection<PointFeatureViewModel> PointFeatureVms {
            get { return pointFeatureVms; }
        }

        public MultiObjectViewModel() { }
        public MultiObjectViewModel() {
            pointFeatureVms.Clear();
            for (int i = 0; i < field.M; ++i) {
                for (int j = 0; j < field.N; ++j) {
                    PointFeatureViewModel ftViewModel = new PointFeatureViewModel(field[i, j], i, j);
                    pointFeatureVms.Add(ftViewModel);
                }
            }
            OnPropertyChanged("PointFeatureVms");
        }

        protected void OnPropertyChanged(string propertyName = null) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    class FieldViewModel : MultiObjectViewModel {
        private Field field;

        public int Width {
            get {
                return field != null ? field.M : 0;
            }
        }

        public int Height {
            get {
                return field != null ? field.N : 0;
            }
        }

        public FieldViewModel(Field field) 
            : base()
        {
            this.field = field;
            OnPropertyChanged("Width");
            OnPropertyChanged("Height");
        }
    }
}
