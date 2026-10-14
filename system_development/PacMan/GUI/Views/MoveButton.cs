using System.Windows;
using System.Windows.Controls;
using GUI.ViewModels;
using PacMan.Model;

namespace GUI.Views
{
    public sealed class MoveButton : Button
    {
        private Direction Direction { get; set; }
        private Game Origin { get; set; }

        public MoveButton()
        {
            DataContextChanged += (sender, args) =>
            {
                var viewModel = DataContext as MoveButtonViewModel;

                if (viewModel != null)
                {
                    Direction = viewModel.Direction;
                    Origin = viewModel.Origin;
                }
            };
        }

        protected override void OnIsPressedChanged(DependencyPropertyChangedEventArgs e)
        {
            base.OnIsPressedChanged(e);

            Origin.PlayerDirection = IsPressed ? Direction : null;
        }
    }
}
