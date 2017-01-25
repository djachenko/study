using System.Windows;
using System.Windows.Media;
using System.Windows.Shapes;
using Gui.ViewModels;

namespace Gui.Views {
    /// <summary>
    /// Логика взаимодействия для KeybindingEditView.xaml
    /// </summary>
    internal sealed partial class KeybindingEditView {
        private readonly Color _errorColor;
        private readonly Color _successColor;

        public KeybindingEditView() {
            InitializeComponent();
            _errorColor = new Color {R = 255, G = 0, B = 0, A = 128};
            _successColor = new Color {R = 0, G = 255, B = 0, A = 128};
            DataContextChanged += OnDataContextChanged;
        }

        private void OnDataContextChanged(object sender, DependencyPropertyChangedEventArgs dependencyPropertyChangedEventArgs) {
            if (!(DataContext is KeybindingViewModel)) {
                return;
            }
            var dc = (KeybindingViewModel) DataContext;
            
            dc.ChangeSuccessEvent += () => NotifyColor(StatusRect, _successColor);
            dc.ChangeErrorEvent += () => NotifyColor(StatusRect, _errorColor);
        }

        private static void NotifyColor(Rectangle r, Color color) {
            r.Fill = new SolidColorBrush(color); 
        }

    }
}
