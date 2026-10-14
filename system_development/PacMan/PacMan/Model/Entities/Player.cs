using System;
using PacMan.Helpers;

namespace PacMan.Model.Entities
{
    public sealed class Player : GameEntity
	{
        private int _highCount;
        private const int DefaultHighCount = 1000 / Game.TimerInterval * 5;

		internal bool High
		{
			get { return HighCount > 0; }
		    private set
		    {
		        HighCount = value ? DefaultHighCount : 0;
		    }
		}

        private int HighCount
        {
            get { return _highCount; }
            set
            {
                _highCount = value;

                OnHighStateChanged.Raise(this);
            }
        }

        public Direction LastDirection { get; private set; }

        internal event EventHandler OnHighStateChanged;
        internal event EventHandler ResetAll;

		public Player(Field game, int x, int y) : base(game, x, y)
		{
            LastDirection = Direction.Up;
		}

        internal void Move(Direction direction)
		{
            if (!Alive)
            {
                return;
            }

            Field.NotifyMovement(X, Y, direction, this);
		}

        protected internal override void NotifyMovement(Direction direction)
        {
            base.NotifyMovement(direction);

            LastDirection = direction;
        }

        public override void Interact(IEntity otherEntity)
        {
            var eatable = otherEntity as EatableEntity;

            if (eatable != null)
			{
				Eat(eatable);
			}
			else
			{
			    var ghost = otherEntity as Ghost;

			    if (ghost != null)
			    {
			        if (High)
			        {
			            ghost.Hit();
			        }
			        else
			        {
			            Hit();
			        }
			    }
			}
        }

        private void Eat(EatableEntity pill)
		{
		    if (pill is MegaPill)
		    {
		        High = true;
		    }

		    pill.Eat();
		}

		public void Tick(Direction moveDirection)
        {
            if (!Alive)
            {
                ResetAll.Raise(this);
            }
            else 
            {
                if (High)
                {
                    HighCount--;
                }

                if (moveDirection != null)
                {
                    Field.NotifyMovement(X, Y, moveDirection, this);
                }
            }
        }
	}
}
