using System;
using System.Runtime.Serialization;

namespace PacMan.Model.Exceptions
{
    [Serializable]
    public sealed class PlaceOccupiedException : Exception
    {
        public PlaceOccupiedException()
        {
        }

        public PlaceOccupiedException(string message) : base(message)
        {
        }

        public PlaceOccupiedException(string message, Exception inner) : base(message, inner)
        {
        }

        private PlaceOccupiedException(
            SerializationInfo info,
            StreamingContext context) : base(info, context)
        {
        }
    }
}
