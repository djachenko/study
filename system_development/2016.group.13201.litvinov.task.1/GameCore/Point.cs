using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace GameCore {
    internal static class PointExtension {
        internal static Point<T> ToPoint<T>(this IEnumerable<T> en) {
            return new Point<T>(en.ToArray());
        }
    }

    internal interface IPointOps<T> {
        T Add(T a, T b);
        T Sub(T a, T b);
        T Mul(T a, T b);
        double MulByDouble(T a, double b);
        T Neg(T a);
        T Abs(T a);
        double ToDouble(T a);
    }

    internal sealed class IntPointOps : IPointOps<int> {  
        public int Add(int a, int b) {
            return a + b;
        }

        public int Sub(int a, int b) {
            return a - b;
        }

        public int Mul(int a, int b) {
            return a * b;
        }

        public int Neg(int a) {
            return -a;
        }

        public int Abs(int a) {
            return a > 0 ? a : -a;
        }

        public double ToDouble(int a) {
            return a;
        }

        public double MulByDouble(int a, double b) {
            return a * b;
        }
    }

    internal sealed class DoublePointOps : IPointOps<double> {
        public double Add(double a, double b) {
            return a + b;
        }

        public double Sub(double a, double b) {
            return a - b;
        }

        public double Mul(double a, double b) {
            return a * b;
        }

        public double Neg(double a) {
            return -a;
        }

        public double Abs(double a) {
            return a > 0 ? a : -a;
        }

        public double ToDouble(double a) {
            return a;
        }

        public double MulByDouble(double a, double b) {
            return a * b;
        }
    }

    internal static class PointOpsManager {
        private static readonly IntPointOps IntPointOps = new IntPointOps();
        private static readonly DoublePointOps DoublePointOps = new DoublePointOps();

        public static IPointOps<T> GetOps<T>() {
            if (typeof(T) == typeof(int)) {
                return IntPointOps as IPointOps<T>;
            }
            if (typeof(T) == typeof(double)) {
                return DoublePointOps as IPointOps<T>;
            }
            throw new NotImplementedException();
        }
    }

    public sealed class Point<T> : IEnumerable<T> {
        private readonly T[] _point;

        internal int Dims => _point.Length;
        private static IPointOps<T> Ops => PointOpsManager.GetOps<T>();

        public T X { get { return _point[0]; }
            private set { _point[0] = value; } }
        public T Y { get { return _point[1]; }
            private set { _point[1] = value; } }

        // ReSharper disable once UnusedParameter.Local
        private void DimNumberCheck(int dim) {
            if (dim < 0 || dim >= Dims) {
                throw new ArgumentException("dim number can't be null");
            }
        }

        internal T this[int dim] {
            get {
                DimNumberCheck(dim);
                return _point[dim];
            }
            set {
                DimNumberCheck(dim);
                _point[dim] = value;
            }
        }

        internal Point(int n) {
            if (n <= 0) {
                throw new ArgumentException("n has to be positive", nameof(n));
            }
            _point = new T[n];            
        }

        internal Point(T[] pt) {
            if (pt == null) {
                throw new ArgumentException("point arr can't be null", nameof(pt));
            }
            _point = pt;
        }

        internal Point(T x, T y) {
            _point = new T[2];
            X = x;
            Y = y;
        }

        public IEnumerator<T> GetEnumerator() {
            return ((IEnumerable<T>)_point).GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator() {
            return _point.GetEnumerator();
        }

        private static void DimsCheck<TS>(Point<T> point1, Point<TS> point2) {
            NullCheck(point1);
            NullCheck(point2);
            if (point1.Dims != point2.Dims) {
                throw new DimsMismatchError(point1.Dims, point2.Dims);
            }
        }

        // ReSharper disable once UnusedParameter.Local
        private static void NullCheck<TS>(Point<TS> pt) {
            if (pt == null) {
                throw new ArgumentException("point can't be null");
            }
        }

        internal double L2Norm() {
            return this.Sum(coord => Ops.ToDouble(Ops.Abs(coord))); // .net, where is my composition :-\
        }

        public static Point<T> operator + (Point<T> point1, Point<T> point2) {
            DimsCheck(point1, point2);
            return point1.Zip(point2, Ops.Add).ToPoint();
        }

        public static Point<T> operator - (Point<T> point1, Point<T> point2) {
            DimsCheck(point1, point2);
            return point1.Zip(point2, Ops.Sub).ToPoint();
        }

        public static Point<T> operator -(Point<T> point) {
            NullCheck(point);
            return point.Select(Ops.Neg).ToPoint();
        }

        public static Point<double> operator /(Point<T> point, double coef) {
            NullCheck(point);
            double revCoef = 1.0 / coef;
            return point.Select(coord => Ops.MulByDouble(coord, revCoef)).ToPoint();
        }

        internal bool IsCollinear(Point<T> point, double epsAbs) {
            DimsCheck(this, point);
            if (Dims == 1) {
                return true;
            }
            if (Dims > 2) {
                throw new NotImplementedException("Dims > 2, this is unimplemented");
            }
            var normalizedVec1 = point / point.L2Norm();
            var normalizedVec2 = this / L2Norm();
            var crossProd = normalizedVec1.X * normalizedVec2.Y - normalizedVec1.Y * normalizedVec2.X;
            return Math.Abs(crossProd) < epsAbs;
        }

        public static Point<double> operator *(Point<T> point, double coef) {
            NullCheck(point);
            return point.Select(coord => Ops.MulByDouble(coord, coef)).ToPoint();
        }

        public static Point<T> operator *(Point<T> point, T coef) {
            NullCheck(point);
            return point.Select(coord => Ops.Mul(coord, coef)).ToPoint();
        }

        internal bool EqualTo(object ptObj) {
            if (!(ptObj is Point<T>)) {
                return false;
            }
            var pt = (Point<T>) ptObj;
            if (pt.Dims != Dims) {
                return false;
            }
            return this.SequenceEqual(pt);
        }
    }
}
