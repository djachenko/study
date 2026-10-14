using System;
using System.Globalization;
using GameCore;

namespace Gui.Converters {
    internal sealed class DirectionToAngleConverter : System.Windows.Data.IValueConverter {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture) {
            if (value == null) {
                return 0;
            }

            PointInt point = (PointInt)value;
            const double radToDeg = 180.0 / Math.PI;
            return point.X == 0 && point.Y != 0
                ? Math.Atan2(point.Y, point.X) * radToDeg
                : 0;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture) {
            throw new NotImplementedException();
        }

        private static DirectionToAngleConverter _instance;
        public static DirectionToAngleConverter Instance {
            get {
                return _instance = _instance ?? new DirectionToAngleConverter();
            }
        }
    }
}
