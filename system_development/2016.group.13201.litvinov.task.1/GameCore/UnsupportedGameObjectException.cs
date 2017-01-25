using System;

namespace GameCore {
    [Serializable]
    internal sealed class UnsupportedGameObjectException : SystemException {
        internal UnsupportedGameObjectException(string msg) : base(msg) {}
    }
}
