namespace GameCore {
    public delegate GameObject GameObjectProducer(PointInt initialPosition, Field<GameObject> otherObjects);

    public interface IGameObjectLoader {
        GameObjectProducer GetProducer();
        char GetOriginFeatureType();
    }
}