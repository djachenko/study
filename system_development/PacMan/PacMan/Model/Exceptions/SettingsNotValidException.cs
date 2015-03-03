using System;
using System.Runtime.Serialization;

namespace PacMan.Model.Exceptions
{
    [Serializable]
    public sealed class SettingsNotValidException : Exception
    {
        public SettingsNotValidException()
        {
        }

        public SettingsNotValidException(string message) : base(message)
        {
        }

        public SettingsNotValidException(string message, Exception inner) : base(message, inner)
        {
        }

        private SettingsNotValidException(
            SerializationInfo info,
            StreamingContext context) : base(info, context)
        {
        }
    }
}
