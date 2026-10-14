using PacMan.Annotations;
using PacMan.Model;
using PacMan.Model.Entities;

namespace Blinky
{
    [UsedImplicitly]
	public sealed class Blinky : Ghost
	{
		public Blinky(Field field, int x, int y)
			: base(field, x, y)
		{ }

		protected override void GetDestinationCoordinates(Player player, out int toX, out int toY)
		{
			toX = player.X;
			toY = player.Y; 
		}
	}
}