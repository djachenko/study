namespace GameCore {
    internal sealed class DefaultGameObjectLoader : IGameObjectLoader {
        private readonly GameObjectProducer _producer;
        private readonly char _featureType;
        public DefaultGameObjectLoader(GameObjectProducer producer, char featureType) {
            _producer = producer;
            _featureType = featureType;
        }

        public GameObjectProducer GetProducer() {
            return _producer;
        }

        public char GetOriginFeatureType() {
            return _featureType;
        }
    }
}
