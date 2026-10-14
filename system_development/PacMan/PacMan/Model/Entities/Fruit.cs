namespace PacMan.Model.Entities
{
    sealed class Fruit : EatableEntity
	{
		public Fruit(Field field, int x, int y) : base(field, x, y)
		{
		}
	}
}
