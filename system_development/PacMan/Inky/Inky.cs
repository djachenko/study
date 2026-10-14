using PacMan.Annotations;
using PacMan.Model;
using PacMan.Model.Entities;

namespace Inky
{
    [UsedImplicitly]
	public sealed class Inky : Ghost
	{
        public Inky(Field field, int x, int y)
			: base(field, x, y)
		{
		}

		protected override void GetDestinationCoordinates(Player player, out int toX, out int toY)
		{
            toX = player.X;
            toY = player.Y;

            toX += player.LastDirection.Dx * 2;
            toY += player.LastDirection.Dy * 2;

            if (player.LastDirection == Direction.Up)
            {
                toX -= 2;
            }
		}
	}
}
