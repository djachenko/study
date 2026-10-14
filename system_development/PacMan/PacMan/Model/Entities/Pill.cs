namespace PacMan.Model.Entities
{
    sealed class Pill : EatableEntity
	{
		public Pill(Field field, int x, int y) : base(field, x, y)
		{
		}
	}
}
