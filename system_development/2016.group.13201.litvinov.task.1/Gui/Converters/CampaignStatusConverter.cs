using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows.Data;
using Gui.ViewModels;

namespace Gui.Converters {
    internal sealed class CampaignStatusConverter : IValueConverter {
        private static readonly Dictionary<CampaignStatus, string> StatusToIcon =
            new Dictionary<CampaignStatus, string>();

        static CampaignStatusConverter() {
            StatusToIcon.Add(CampaignStatus.Gaming, @"/Resources/none.png");
            StatusToIcon.Add(CampaignStatus.Gameover, @"/Resources/loose.png");
            StatusToIcon.Add(CampaignStatus.Win, @"/Resources/win.png");
        }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture) {
            if (!(value is CampaignStatus)) {
                return @"/Resources/none.png";
            }
            return StatusToIcon[(CampaignStatus) value];
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture) {
            throw new NotImplementedException();
        }

        private static CampaignStatusConverter _instance;
        public static CampaignStatusConverter Instance {
            get {
                return _instance = _instance ?? new CampaignStatusConverter();
            }
        }
    }
}
