using System;

namespace GameCore {
    [Serializable]
    public sealed class GhostsLoadException : SystemException {
        internal GhostsLoadException(string msg) : base(msg) {}
    }
}
