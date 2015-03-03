using System;
using System.Globalization;
using System.Windows.Data;

namespace GUI.Converters
{
    public sealed class ButtonEnableConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var s = value as string;

            if (s != null)
            {
                return s.Length > 0;
            }

            return false;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
