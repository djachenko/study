namespace PacMan.Model.Entities
{
    public interface IEntity
    {
        bool Alive { get; }

        void Interact(IEntity otherEntity);
    }
}