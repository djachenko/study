using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Media.Imaging;

namespace Gui.Converters {
    internal sealed class FieldDimsConverter : IValueConverter {
        public const char KindX = 'w';
        public const char KindY = 'h';
        private readonly int _spriteWidth;
        private readonly int _spriteHeight;

        public FieldDimsConverter() {
            var uri = new Uri("pack://application:,,,/Resources/none.png");
            var noneSprite = new BitmapImage(uri);
            _spriteWidth = noneSprite.PixelWidth;
            _spriteHeight = noneSprite.PixelHeight;
        }

        private static double GetDouble(object obj) {
            if (obj is int) {
                return (int) obj;
            } else if (obj is double) {
                return (double) obj;
            } else {
                return 0;
            }
        }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture) {
            if (parameter == null) {
                return 0;
            }
            char dimensionKind = (char)parameter;
            if (dimensionKind == KindX) {
                return (int)Math.Round(_spriteWidth * GetDouble(value));
            }
            if (dimensionKind == KindY) {
                return (int)Math.Round(_spriteHeight * GetDouble(value));
            }
            throw new NotImplementedException("Unknown dim: " + dimensionKind);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture) {
            throw new NotImplementedException();
        }
    }
}
