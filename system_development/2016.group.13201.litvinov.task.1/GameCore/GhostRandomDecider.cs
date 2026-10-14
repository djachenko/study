using System;
using System.Collections.Generic;
using System.Linq;

namespace GameCore {
    public sealed class GhostRandomDecider {
        private readonly Random _random = new Random();
        private Field<GameObject> StaticGameObjects { get; }
        private const int OldPositionsQueueSize = 9;
        private readonly Queue<PointInt> _oldPositionsQueue = new Queue<PointInt>();

        public GhostRandomDecider(Field<GameObject> staticGameObjects) {
            if (staticGameObjects == null) {
                throw new ArgumentException("staticGameObjects can't be null");
            }
            StaticGameObjects = staticGameObjects;
            for (int i = 0; i < OldPositionsQueueSize; ++i) {
                _oldPositionsQueue.Enqueue(new PointInt(int.MinValue, int.MinValue));
            }
        }
        
        private bool WasThere(PointInt point) {
            foreach (PointInt queuePt in _oldPositionsQueue) {
                if (point.EqualTo(queuePt)) {
                    return true;
                }
            }
            return false;
        }

        private PointInt RandomListElem(List<PointInt> list) {
            if (list == null) {
                throw new ArgumentException("list can't be null");
            }
            return list[_random.Next(list.Count)];
        }

        public PointInt DecideRandom(PointInt intPosition) {
            var neigh = GeomHelper.Get1Neighbors(intPosition);
            var availNeigh = new List<PointInt>(neigh.Where(point => StaticGameObjects[point].IsPassable));
            var notvisitedNeigh = new List<PointInt>(availNeigh.Where(point => !WasThere(point)));
            PointInt nextPos;
            if (notvisitedNeigh.Count != 0) {
                nextPos = RandomListElem(notvisitedNeigh);
            } else if (availNeigh.Count != 0) {
                nextPos = RandomListElem(availNeigh);
            } else {
                nextPos = new PointInt(intPosition.X + 1, intPosition.Y);
            }
            
            _oldPositionsQueue.Dequeue();
            _oldPositionsQueue.Enqueue(intPosition);
            return nextPos - intPosition;
        }
    }
}
