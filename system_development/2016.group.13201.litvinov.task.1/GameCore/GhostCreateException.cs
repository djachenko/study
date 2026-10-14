using System;

namespace GameCore {
    [Serializable]
    public sealed class GhostCreateException : SystemException {
        internal GhostCreateException(string msg) : base(msg) {}
    }
}
