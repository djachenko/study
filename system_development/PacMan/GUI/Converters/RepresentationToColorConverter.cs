using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Media;
using PacMan.Model.Cells;

namespace GUI.Converters
{
    sealed class RepresentationToColorConverter : IValueConverter
    {
        private static readonly Dictionary<int, SolidColorBrush> Brushes = new Dictionary<int, SolidColorBrush>();
        
        static RepresentationToColorConverter()
        {
            Brushes.Add(CellRepresentations.WallCellRepresentation, new SolidColorBrush(Colors.DarkSlateGray));
            Brushes.Add(CellRepresentations.SpaceCellRepresentation, new SolidColorBrush(Colors.Gray));
            Brushes.Add(CellRepresentations.PlayerCellRepresentation, new SolidColorBrush(Colors.Yellow));
            Brushes.Add(CellRepresentations.HighPlayerCellRepresentation, new SolidColorBrush(Colors.Red));
            Brushes.Add(CellRepresentations.PillCellRepresentation, new SolidColorBrush(Colors.Peru));
            Brushes.Add(CellRepresentations.MegaPillCellRepresentation, new SolidColorBrush(Colors.Plum));
            Brushes.Add(CellRepresentations.FruitCellRepresentation, new SolidColorBrush(Colors.GreenYellow));
            Brushes.Add(CellRepresentations.GhostCellRepresentation, new SolidColorBrush(Colors.WhiteSmoke));
        }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (Brushes.ContainsKey((int)value))
            {
                return Brushes[(int) value];
            }

            return Colors.Gray;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
