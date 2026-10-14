using System;
using PacMan.Helpers;

namespace PacMan.Model.Entities
{
    abstract class EatableEntity : GameEntity
    {
        internal event EventHandler Eaten;

        protected EatableEntity(Field field, int x, int y)
            : base(field, x, y)
        {
        }

        public override void Interact(IEntity otherEntity)
        {
            //eatables aren't active, so they can't interact with anyone
            throw new NotImplementedException();
        }

        internal void Eat()
        {
            Eaten.Raise(this);

            Field.RemovePassiveCell(X, Y);
        }
    }
}
