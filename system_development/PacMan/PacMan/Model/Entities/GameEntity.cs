using System;
using PacMan.Helpers;
using PacMan.Model.Exceptions;

namespace PacMan.Model.Entities	
{
    public abstract class GameEntity : IEntity
	{
        private int InitialX { get; set; }
        private int InitialY { get; set; }

        public int X { get; private set; }
        public int Y { get; private set; }

        public bool Alive { get; private set; }

        protected Field Field { get; private set; }

        internal event EventHandler WasHit;

		protected GameEntity(Field field, int x, int y)
		{
			InitialX = x;
			InitialY = y;

		    Field = field;

		    X = InitialX;
		    Y = InitialY;

		    Alive = true;
		}

		protected internal void Hit()
		{
			if (Alive)
		    {
		        Alive = false;

		        WasHit.Raise(this);
		    }
		}

        protected internal virtual void NotifyMovement(Direction direction)
        {
            X += direction.Dx;
            Y += direction.Dy;
        }

		protected internal void Reset()
		{
		    try
		    {
		        Field.ResetActiveCell(X, Y, InitialX, InitialY);

		        X = InitialX;
		        Y = InitialY;

		        Alive = true;
		    }
		    catch (PlaceOccupiedException)
		    {}
		}

        public abstract void Interact(IEntity gameEntity);        
	}
}
