using System;
using System.Collections.Generic;

namespace GameCore {
    public sealed class GhostBfsDecider  {
        private readonly PathHelper _evilPathHelper;
        private readonly PathHelper _rescuePathHelper;
        private GhostRandomDecider GhostRandomDecider { get; }

        public GhostBfsDecider(Field<GameObject> staticGameObjects, int evilIdeaMaxAge, int rescueIdeaMaxAge) 
        {
            if (staticGameObjects == null) {
                throw new ArgumentException("staticGameObjects can't be null", nameof(staticGameObjects));
            }
            if (evilIdeaMaxAge < 0 || rescueIdeaMaxAge < 0) {
                throw new ArgumentException("idea age can't be negative");
            }
            GhostRandomDecider = new GhostRandomDecider(staticGameObjects);
            _evilPathHelper = new PathHelper(staticGameObjects, evilIdeaMaxAge);
            _rescuePathHelper = new PathHelper(staticGameObjects, rescueIdeaMaxAge);
        }

        private sealed class BfsMarker {
            public Field<int> BfsMarks { get;  }
            public Field<PointInt> Sources { get;  }

            private readonly HashSet<PointInt> _marked;
            private readonly Field<GameObject> _staticGameObjects;

            public const int InfMark = int.MaxValue;

            public BfsMarker(Field<GameObject> staticGameObjects) {
                if (staticGameObjects == null) {
                    throw new ArgumentException("staticGameObjects can't be null", nameof(staticGameObjects));
                }
                BfsMarks = new Field<int>(staticGameObjects.Width, staticGameObjects.Height);
                Sources = new Field<PointInt>(staticGameObjects.Width, staticGameObjects.Height);
                _marked = new HashSet<PointInt>();
                _staticGameObjects = staticGameObjects;
            }

            private void InitBfs() {
                BfsMarks.Foreach((i, j, value) => { BfsMarks[i, j] = InfMark; });
                Sources.Foreach((i, j, value) => { Sources[i, j] = new PointInt(i,j); });

                _marked.Clear();
            }

            public void MarkFrom(PointInt startPoint) {
                InitBfs();

                Queue<PointInt> bfsQueue = new Queue<PointInt>();
                bfsQueue.Enqueue(startPoint);
                BfsMarks[startPoint] = 0;

                while (bfsQueue.Count != 0) {
                    PointInt bfsPoint = bfsQueue.Dequeue();
                    int step = BfsMarks[bfsPoint];
                    foreach (var neigh in GeomHelper.Get1Neighbors(bfsPoint)) {
                        if (!_marked.Contains(neigh) && _staticGameObjects.IsBoundsOk(neigh.X, neigh.Y) 
                            && _staticGameObjects[neigh].IsPassable)
                        {
                            if (step + 1 < BfsMarks[neigh]) {
                                BfsMarks[neigh] = step + 1;
                                Sources[neigh] = bfsPoint;
                                bfsQueue.Enqueue(neigh);
                            }
                        }
                    }
                    _marked.Add(bfsPoint);
                }
            }
        }

        private sealed class PathHelper {
            public bool Invalid { get; set; }
            public BfsMarker BfsMarker { get; }

            private readonly int _ideaMaxAge;
            private int _ideaAge;
            private readonly Stack<PointInt> _ideaPath;

            public PathHelper(Field<GameObject> staticGameObjects, int ideaMaxAge) {
                BfsMarker = new BfsMarker(staticGameObjects);
                _ideaPath = new Stack<PointInt>();
                _ideaMaxAge = ideaMaxAge;
                _ideaAge = 0;
            }

            public void IdeaAgeStep() {
                _ideaAge = (_ideaAge + 1) % _ideaMaxAge;
            }

            public bool IsPathOld() {
                return _ideaAge == 0;
            }

            public void BuildIdeaPathTo(PointInt toWhere) {
                _ideaPath.Clear();
                _ideaPath.Push(toWhere);
                PointInt source = BfsMarker.Sources[toWhere];
                while (!BfsMarker.Sources[source].EqualTo(source)) {
                    _ideaPath.Push(source);
                    source = BfsMarker.Sources[source];
                }
                _ideaPath.Push(source);
            }

            public int IdeaPathSize => _ideaPath.Count;

            public PointInt PeekIdeaPath() {
                return _ideaPath.Peek();
            }

            public void PopIdeaPath() {
                _ideaPath.Pop();
            }
        }

        private PointInt Decide(PointInt intPosition, PathHelper pathHelper, Action<PathHelper> buildNewPath) {
            if (pathHelper == null) {
                throw new ArgumentException("pathhelper can't be null", nameof(pathHelper));
            }
            
            if (pathHelper.IsPathOld() || pathHelper.Invalid) {
                buildNewPath?.Invoke(pathHelper);
                pathHelper.Invalid = false;
            }
            pathHelper.IdeaAgeStep();

            const int nearTargetPathSize = 2;
            if (pathHelper.IdeaPathSize < nearTargetPathSize || pathHelper.IdeaPathSize == 0 || !intPosition.EqualTo(pathHelper.PeekIdeaPath())) {
                if (pathHelper.IdeaPathSize != 0 && !intPosition.EqualTo(pathHelper.PeekIdeaPath())) {
                    pathHelper.Invalid = true;
                }
                return GhostRandomDecider.DecideRandom(intPosition);
            } else {
                pathHelper.PopIdeaPath();
                return pathHelper.PeekIdeaPath() - intPosition;
            }
        }

        public PointInt DecideAsEvil(PointInt intPosition, PointInt lastPacmanIntPosition) {
            return Decide(intPosition, _evilPathHelper, ph => {
                ph.BfsMarker.MarkFrom(intPosition);
                ph.BuildIdeaPathTo(lastPacmanIntPosition);
            });
        }

        public PointInt DecideAsFood(PointInt intPosition, PointInt lastPacmanIntPosition) {
            return Decide(intPosition, _rescuePathHelper, ph => {
                ph.BfsMarker.MarkFrom(lastPacmanIntPosition);

                PointInt maxMarkIdx = new PointInt();
                int maxMark = int.MinValue;
                ph.BfsMarker.BfsMarks.Foreach((i, j, mark) => {
                    if (mark != BfsMarker.InfMark && mark > maxMark) {
                        maxMark = mark;
                        maxMarkIdx[0] = i;
                        maxMarkIdx[1] = j;
                    }
                });
                ph.BfsMarker.MarkFrom(intPosition);
                ph.BuildIdeaPathTo(maxMarkIdx);
            });
        }
    }
}
