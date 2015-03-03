using System;
using System.Linq;
using PacMan.Model.Entities.Ghosts;

namespace PacMan.Model.Entities
{
    public abstract class Ghost : GameEntity
    {
        private const int TickInterval = 1000;
        private const int TickRate = TickInterval / Game.TimerInterval;

        private Labyrinth Labyrinth { get; set; }

        protected Ghost(Field field, int x, int y) : base(field, x, y)
        {
            Labyrinth = field.Labyrinth;
        }

        public override void Interact(IEntity otherEntity)
		{
		    var player = otherEntity as Player;

		    if (player != null)
			{
			    if (player.High)
			    {
                    Hit();
			    }
			    else
			    {
			        player.Hit();
			    }                
			}
		}

        public void Tick(int iteration, Player player)
        {
            if (!Alive)
            {
                Reset();
            }
            else if (iteration % TickRate == 0)
            {
                if (!player.High)
                {
                    Pursuit(player);
                }
                else
                {
                    Scare();
                }
            }
        }

        private void Scare()
        {
            var index = new Random().Next() % Direction.Values.Count();

            foreach (var direction in Direction.Values)
            {
                if (index == 0)
                {
                    Field.NotifyMovement(X, Y, direction, this);
                }
                else
                {
                    index--;
                }
            }
        }

        private void Pursuit(Player player)
        {
            int toX;
            int toY;

            GetDestinationCoordinates(player, out toX, out toY);

            var moveDirection = Labyrinth.GetNextDirection(X, Y, toX, toY);

            Field.NotifyMovement(X, Y, moveDirection, this);
        }

        protected abstract void GetDestinationCoordinates(Player player, out int toX, out int toY);
	}
}
