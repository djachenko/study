using System.Collections.Generic;

namespace GameCore {
    internal static class GeomHelper {
        internal static IEnumerable<PointInt> Get1Neighbors(PointInt point) {
            yield return new PointInt(point.X - 1, point.Y);
            yield return new PointInt(point.X + 1, point.Y);
            yield return new PointInt(point.X, point.Y - 1);
            yield return new PointInt(point.X, point.Y + 1);
        }
    }
}
