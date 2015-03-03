using PacMan.Annotations;
using PacMan.Model;
using PacMan.Model.Entities;

namespace Pinky
{
    [UsedImplicitly]
	public sealed class Pinky : Ghost
	{
		public Pinky(Field field, int x, int y)
			: base(field, x, y)
		{ }

		protected override void GetDestinationCoordinates(Player player, out int toX, out int toY)
		{
			toX = player.X;
			toY = player.Y;

			toX += player.LastDirection.Dx * 4;
			toY += player.LastDirection.Dy * 4;
		}
	}
}
