using PacMan.Annotations;
using PacMan.Model;
using PacMan.Model.Entities;

namespace Clyde
{
    [UsedImplicitly]
	public sealed class Clyde : Ghost
	{
	    private const int ClydeDistance = 9;

		private readonly int _destX;
		private readonly int _destY;

		public Clyde(Field field, int x, int y)
			: base(field, x, y)
		{
			_destX = Field.Width - 1;
			_destY = Field.Height - 1;
		}

		protected override void GetDestinationCoordinates(Player player, out int toX, out int toY)
		{
			var distance = (X - player.X) * (X - player.X) + (Y - player.Y) * (Y - player.Y);

			if (distance > ClydeDistance * ClydeDistance)
			{
				toX = player.X;
				toY = player.Y;
			}
			else
			{
				toX = _destX;
				toY = _destY;
			}
		}
	}
}
