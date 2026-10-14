namespace PacMan.Model.Entities
{
    sealed class MegaPill : EatableEntity
	{
		public MegaPill(Field field, int x, int y) : base(field, x, y)
		{
		}
	}
}
