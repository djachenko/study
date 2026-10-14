using System;
using System.Globalization;
using System.Windows.Data;

namespace GUI.Converters
{
    sealed class IncrementConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var i = value as int?;

            return i != null ? i + 1 : value;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
