using System;

namespace GameCore {
    [Serializable]
    public sealed class FieldIoError : SystemException {
        internal FieldIoError(string msg) : base(msg) {
        }
    }
}
