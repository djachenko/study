using System;
using System.Runtime.Serialization;

namespace PacMan.Model.Exceptions
{
    [Serializable]
    public sealed class KeyBindedException : Exception
    {
        public KeyBindedException()
        {
        }

        public KeyBindedException(string message) : base(message)
        {
        }

        public KeyBindedException(string message, Exception inner) : base(message, inner)
        {
        }

        private KeyBindedException(
            SerializationInfo info,
            StreamingContext context) : base(info, context)
        {
        }
    }
}
