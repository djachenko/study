using System;
using System.Globalization;
using System.Windows.Data;
using PacMan.Model;

namespace GUI.Converters
{
    public sealed class DirectionToShortNameConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var direction = value as Direction;

            return direction != null ? direction.Name : null;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
