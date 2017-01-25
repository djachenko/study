using System;

namespace GameCore {
    internal static class PointCasts {
        internal static PointInt DoubleToInt(PointDouble pointDouble, Func<double, int> caster) {
            if (caster == null) {
                throw new ArgumentException("caster can't be null");
            }
            return new PointInt(caster(pointDouble.X), caster(pointDouble.Y));
        }

        internal static PointDouble IntToDouble(PointInt pointInt) {
            return new PointDouble(pointInt.X, pointInt.Y);
        }
    }

    public struct PointInt {
        public int X { get; private set; }

        public int Y { get; private set; }

        internal int this[int dim] {
            set {
                if (dim == 0) {
                    X = value;
                } else if (dim == 1) {
                    Y = value;
                } else {
                    throw new ArgumentException("dim can't be negative or more than two");
                }
            }
        }

        internal PointInt(int x, int y) {
            X = x;
            Y = y;
        }

        public static PointInt operator +(PointInt left, PointInt right) {
            return new PointInt(left.X + right.X, left.Y + right.Y);
        }

        public static PointInt operator -(PointInt left, PointInt right) { 
            return new PointInt(left.X - right.X, left.Y - right.Y);
        }

        public static PointInt operator *(PointInt left, PointInt right) {
            return new PointInt(left.X * right.X, left.Y * right.Y);
        }

        public static PointInt operator -(PointInt point) {
            return new PointInt(-point.X, -point.Y);
        }

        internal bool IsNonOrthogonal(PointInt point) {
            return point.X * X != 0 && point.Y * Y != 0;
        }

        internal bool EqualTo(PointInt point) {
            return point.X == X && point.Y == Y;
        }
    }

    public struct PointDouble {
        internal static int Dims => 2;

        public double X { get; }
        public double Y { get; }

        internal bool IsIntegerPoint(double doubleToIntThreshold) {
            if (doubleToIntThreshold < 0) {
                throw new ArgumentException("double to integer threshold can't be negative");
            }
            double sumFraction = (X+Y) - Math.Floor(X+Y);
            return sumFraction <= doubleToIntThreshold || sumFraction >= (1 - doubleToIntThreshold);
        }

        internal double this[int dim] {
            get {
                switch (dim) {
                    case 0:
                        return X;
                    case 1:
                        return Y;
                    default:
                        throw new ArgumentException("dim can't be negative or more than two");
                }
            }
        }

        internal PointDouble(double x, double y) {
            X = x;
            Y = y;
        }

        internal double L2Norm() {
            return Math.Abs(X) + Math.Abs(Y);
        }

        public static PointDouble operator +(PointDouble left, PointDouble right) {
            return new PointDouble(left.X + right.X, left.Y + right.Y);
        }

        public static PointDouble operator -(PointDouble left, PointDouble right) {
            return new PointDouble(left.X - right.X, left.Y - right.Y);
        }

        public static PointDouble operator *(PointDouble left, PointDouble right) { 
            return new PointDouble(left.X * right.X, left.Y * right.Y);
        }

        public static PointDouble operator -(PointDouble point) {
            return new PointDouble(-point.X, -point.Y);
        }

        public static PointDouble operator *(PointDouble point, double scalarCoefficient) {
            return new PointDouble(point.X * scalarCoefficient, point.Y * scalarCoefficient);
        }

        internal bool EqualTo(PointDouble point) {
            // abs difference compared to 0 sponsored by resharper
            return Math.Abs(point.X - X) <= 0 && Math.Abs(point.Y - Y) <= 0; 
        }
    }
}
