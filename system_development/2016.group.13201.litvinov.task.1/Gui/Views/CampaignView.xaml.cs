using Gui.ViewModels;

namespace Gui.Views {
    /// <summary>
    /// Логика взаимодействия для CampaignView.xaml
    /// </summary>
    internal sealed partial class CampaignView {
        public  CampaignView() {
            InitializeComponent();
            DataContextChanged += (sender, args) => {
                if (!(DataContext is CampaignViewModel)) {
                    return;
                }
                var dc = (CampaignViewModel)DataContext;
                dc.ShowErrorService = new WinapiShowErrorService();
                dc.AskNameService = new AskNameService();
            };

        }
    }
}
