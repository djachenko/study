using System.Linq;
using System.Windows;
using Gui.ViewModels;
using GameCore;

namespace Gui.Views {
    internal sealed class ShowHiscoresService : IShowHiscoresService {
        public void ShowHiscores(HiscoresTable scores) { 
            var win = new HiscoresWindow();
            var dc = new HiscoresWindowViewModel();
            dc.SetHiscores(scores.Select(record => new HiscoreViewModel(record)));
            win.DataContext = dc;
            win.Owner = Application.Current.MainWindow;
            win.Show();
        }
    }
}
