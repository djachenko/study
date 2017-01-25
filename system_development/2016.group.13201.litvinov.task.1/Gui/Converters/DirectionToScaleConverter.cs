using System;
using System.Globalization;
using GameCore;

namespace Gui.Converters {
    internal sealed class DirectionToScaleConverter : System.Windows.Data.IValueConverter {
        public const char KindX = 'x', KindY = 'y';

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture) {
            if (value == null ||  parameter == null) {
                return 1;
            }
            char dimKind = (char)parameter;
            PointInt point = (PointInt)value;
            if (dimKind == KindX) {
                return point.X == 0 ? 1 : (point.X < 0 ? -1 : 1);
            }
            return 1;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture) {
            throw new NotImplementedException();
        }

        private static DirectionToScaleConverter _instance;
        public static DirectionToScaleConverter Instance {
            get {
                return _instance = _instance ?? new DirectionToScaleConverter();
            }
        }
    }
}
