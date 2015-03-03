using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace GUI
{
    public sealed class GridHelpers
    {
        #region RowCount Property

        public static readonly DependencyProperty RowCountProperty = DependencyProperty.RegisterAttached(
            "RowCount", 
            typeof(int), 
            typeof(GridHelpers),
            new PropertyMetadata(-1, RowCountChanged));

        public static int GetRowCount(DependencyObject obj)
        {
            return (int)obj.GetValue(RowCountProperty);
        }

        public static void SetRowCount(DependencyObject obj, int value)
        {
            obj.SetValue(RowCountProperty, value);
        }

        private static void RowCountChanged(DependencyObject obj, DependencyPropertyChangedEventArgs e)
        {
            if (!(obj is Grid) || (int) e.NewValue < 0)
            {
                return;
            }

            var grid = (Grid)obj;
            grid.RowDefinitions.Clear();

            for (var i = 0; i < (int) e.NewValue; i++)
            {
                grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(1, GridUnitType.Star), 
                    SharedSizeGroup = "layerRows"});
            }

            SetStarRows(grid);
        }

        #endregion

        #region ColumnCount Property

        public static readonly DependencyProperty ColumnCountProperty = DependencyProperty.RegisterAttached(
                "ColumnCount", 
                typeof(int), 
                typeof(GridHelpers),
                new PropertyMetadata(-1, ColumnCountChanged));

        public static int GetColumnCount(DependencyObject obj)
        {
            return (int)obj.GetValue(ColumnCountProperty);
        }

        public static void SetColumnCount(DependencyObject obj, int value)
        {
            obj.SetValue(ColumnCountProperty, value);
        }

        private static void ColumnCountChanged(DependencyObject obj, DependencyPropertyChangedEventArgs e)
        {
            if (!(obj is Grid) || (int) e.NewValue < 0)
            {
                return;
            }

            var grid = (Grid)obj;
            grid.ColumnDefinitions.Clear();

            for (var i = 0; i < (int) e.NewValue; i++)
            {
                grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(1, GridUnitType.Star) });
            }

            SetStarColumns(grid);
        }

        #endregion

        #region StarRows Property

        public static readonly DependencyProperty StarRowsProperty = DependencyProperty.RegisterAttached(
                "StarRows", 
                typeof(string), 
                typeof(GridHelpers),
                new PropertyMetadata(string.Empty, StarRowsChanged));

        private static string GetStarRows(DependencyObject obj)
        {
            return (string)obj.GetValue(StarRowsProperty);
        }

/*
        public static void SetStarRows(DependencyObject obj, string value)
        {
            obj.SetValue(StarRowsProperty, value);
        }
*/

        private static void StarRowsChanged(DependencyObject obj, DependencyPropertyChangedEventArgs e)
        {
            if (!(obj is Grid) || string.IsNullOrEmpty(e.NewValue.ToString()))
                return;

            SetStarRows((Grid)obj);
        }

        #endregion

        #region StarColumns Property

        public static readonly DependencyProperty StarColumnsProperty = DependencyProperty.RegisterAttached(
                "StarColumns", 
                typeof(string), 
                typeof(GridHelpers),
                new PropertyMetadata(string.Empty, StarColumnsChanged));

        private static string GetStarColumns(DependencyObject obj)
        {
            return (string)obj.GetValue(StarColumnsProperty);
        }

/*
        public static void SetStarColumns(DependencyObject obj, string value)
        {
            obj.SetValue(StarColumnsProperty, value);
        }
*/

        private static void StarColumnsChanged(DependencyObject obj, DependencyPropertyChangedEventArgs e)
        {
            if (!(obj is Grid) || string.IsNullOrEmpty(e.NewValue.ToString()))
                return;

            SetStarColumns((Grid)obj);
        }

        #endregion

        private static void SetStarColumns(Grid grid)
        {
            var starColumns = GetStarColumns(grid).Split(',');

            for (var i = 0; i < grid.ColumnDefinitions.Count; i++)
            {
                if (starColumns.Contains(i.ToString()))
                {
                    grid.ColumnDefinitions[i].Width = new GridLength(1, GridUnitType.Star);
                }
            }
        }

        private static void SetStarRows(Grid grid)
        {
            var starRows = GetStarRows(grid).Split(',');

            for (var i = 0; i < grid.RowDefinitions.Count; i++)
            {
                if (starRows.Contains(i.ToString()))
                {
                    grid.RowDefinitions[i].Height = new GridLength(1, GridUnitType.Star);
                }
            }
        }
    }
}