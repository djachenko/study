using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using PacMan.Annotations;
using PacMan.Model;

namespace GUI.ViewModels
{
    public sealed class GridFieldLayerViewModel
    {
        private FieldLayer _source;

        [UsedImplicitly]
        public int Index { get; set; }

        private FieldLayer Source
        {
            get { return _source; }
            set
            {
                _source = value;

                Update();
            }
        }

        public ObservableCollection<CellViewModel> Cells { get; set; }

        public int Width
        {
            get { return Source != null ? Source.Width : 0; }
        }

        public int Height
        {
            get { return Source != null ? Source.Height : 0; }
        }

        internal GridFieldLayerViewModel(FieldLayer source, int index)
        {
            Cells = new ObservableCollection<CellViewModel>();

            Source = source;
            Index = index;

            source.CellChanged += (sender, args) =>
            {
                if (args != null)
                {
                    var add = args.CellAdded;
                    var remove = args.CellRemoved;

                    if (add == remove)
                    {
                        return;
                    }

                    var toRemove = Cells.FirstOrDefault(cellViewModel => cellViewModel.Origin == remove);
                    var toAdd = add != null ? new CellViewModel(add) : null;
                    
                    if (Application.Current != null)
                    {
                        Application.Current.Dispatcher.Invoke(() =>
                        {
                            Cells.Remove(toRemove);

                            if (toAdd != null)
                            {
                                Cells.Add(toAdd);
                            }
                        });
                    }
                }
            };
        }

        void Update()
        {
            Cells.Clear();

            for (var y = 0; y < _source.Height; y++)
            {
                for (var x = 0; x < _source.Width; x++)
                {
                    var cell = _source[x, y];

                    if (cell != null)
                    {
                        Cells.Add(new CellViewModel(cell));
                    }
                }
            }
        }
    }
}
