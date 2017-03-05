//
// Created by ivb on 02.03.17.
//

#include "geometry.h"
#include <cmath>
#include <cassert>

const ld eps = 1e-5;

ld Point2D::len2() const
{
    return x*x + y*y;
}

ld Point2D::len() const
{
    return sqrtl(len());
}

ld Point3D::len2() const
{
    return x*x + y*y + z*z;
}

ld Point3D::len() const
{
    return sqrtl(len());
}

bool isZero(ld z)
{
    return fabsl(z) < eps;
}

int sign(ld z)
{
    if(isZero(z)) {
        return 0;
    } else {
        return z < 0 ? -1 : 1;
    }
}

bool areEqual(ld x, ld y)
{
    return sign(x - y) == 0;
}

bool isLessThan(ld x, ld y)
{
    return sign(x - y) < 0;
}

bool isMoreThan(ld x, ld y)
{
    return sign(x - y) > 0;
}

bool isLessEqual(ld x, ld y)
{
    return sign(x - y) <= 0;
}

bool isMoreEqual(ld x, ld y)
{
    return sign(x - y) >= 0;
}

Point2D operator+(const Point2D p1, const Point2D p2)
{
    return Point2D{p1.x + p2.x, p1.y + p2.y};
}

Point3D operator+(const Point3D p1, const Point3D p2)
{
    return Point3D{p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

Point2D operator-(const Point2D p1, const Point2D p2)
{
    return Point2D{p1.x - p2.x, p1.y - p2.y};
}

Point3D operator-(const Point3D p1, const Point3D p2)
{
    return Point3D{p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}

Point2D operator*(const Point2D p, ld d)
{
    return Point2D{d * p.x, d * p.y};
}

Point3D operator*(const Point3D p, ld d)
{
    return Point3D{d * p.x, d * p.y, d * p.z};
}

Point2D operator*(ld d, const Point2D p)
{
    return p * d;
}

Point3D operator*(ld d, const Point3D p)
{
    return p * d;
}

ld operator*(const Point2D p1, const Point2D p2)
{
    return p1.x * p2.y - p1.y * p2.x;
}

Point3D operator*(const Point3D p1, const Point3D p2)
{
    return Point3D{p1.y * p2.z - p1.z * p2.y,
                   -(p1.x * p2.z - p1.z * p2.x),
                   p1.x * p2.y - p1.y * p2.x};
}

ld operator^(const Point2D p1, const Point2D p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

ld operator^(const Point3D p1, const Point3D p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

ld tripleProduct(const Point3D p1, const Point3D p2, const Point3D p3)
{
    return p1^(p2*p3);
}

bool areEqual(const Point2D p1, const Point2D p2)
{
    return areEqual(p1.x, p2.x) &&
           areEqual(p1.y, p2.y);
}

bool areEqual(const Point3D p1, const Point3D p2)
{
    return areEqual(p1.x, p2.x) &&
           areEqual(p1.y, p2.y) &&
           areEqual(p1.z, p2.z);
}

bool areCollinear(const Point2D p1, const Point2D p2)
{
    return isZero(p1 * p2);
}

bool areCollinear(const Point3D p1, const Point3D p2)
{
    return isZero((p1 * p2).len2());
}

bool isOnLine(const Point2D p, const Line2D l)
{
    return areCollinear(l.B - l.A, p - l.A);
}

bool isOnLine(const Point3D p, const Line3D l)
{
    return areCollinear(l.B - l.A, p - l.A);
}

bool isOnSegment(const Point2D p, const Point2D A, const Point2D B)
{
    return areCollinear(p - A, B - A) &&
           sign((p - A)^(p - B)) <= 0;
}

bool isOnSegment(const Point3D p, const Point3D A, const Point3D B)
{
    return areCollinear(p - A, B - A) &&
           sign((p - A)^(p - B)) <= 0;
}

bool areLinesParallelOrEqual(const Line2D l1, const Line2D l2)
{
    areCollinear(l1.B - l1.A, l2.B - l2.A);
}

bool areLinesParallelOrEqual(const Line3D l1, const Line3D l2)
{
    areCollinear(l1.B - l1.A, l2.B - l2.A);
}

bool areLinesInOnePlane(const Line3D l1, const Line3D l2)
{
    return isZero(tripleProduct(l1.B - l1.A, l2.B - l2.A, l2.A - l1.A));
}

Point2D findLinesIntersection(const Line2D l1, const Line2D l2)
{
#ifndef NOASSERT
    assert(!areLinesParallelOrEqual(l1, l2));
#endif
    // Пусть точка пересечения:
    // l1.A + t(l1.B - l1.A)
    // Имеем уравнение относительно t:
    // [l1.A + t(l1.B - l1.A) - l2.A, l2.B - l2.A] == 0
    // Обозначая:

    ld a = (l1.A - l2.A) * (l2.B - l2.A);
    ld b = (l1.B - l1.A) * (l2.B - l2.A);

    // Оно преобразовывается к скалярному:
    // a + tb = 0
    // откуда находим t

    ld t = - a / b;

    return l1.A + t * (l1.B - l1.A);
}

Point3D findLinesIntersection(const Line3D l1, const Line3D l2)
{
#ifndef NOASSERT
    assert(areLinesInOnePlane(l1, l2) &&
           !areLinesParallelOrEqual(l1, l2));
#endif
    Point3D a = (l1.A - l2.A) * (l2.B - l2.A);
    Point3D b = (l1.B - l1.A) * (l2.B - l2.A);

    // (a, b) + t(b, b) = 0

    ld t = - (a ^ b) / (b ^ b);

    return l1.A + t * (l1.B - l1.A);
}

bool doesSegmentIntersectLine(const Point2D A, const Point2D B,
                              const Line2D l)
{
    return sign((l.B - l.A)*(A - l.A)) * sign((l.B - l.A)*(B - l.A)) <= 0;
}

bool doesSegmentIntersectLine(const Point3D A, const Point3D B,
                              const Line3D l)
{
    return areLinesInOnePlane(Line3D{A, B}, l) &&
           sign(((l.B - l.A)*(A - l.A)) ^ ((l.B - l.A)*(B - l.A))) <= 0;
}

bool areSegmentsIntersected(const Point2D A, const Point2D B,
                            const Point2D C, const Point2D D)
{
    return doesSegmentIntersectLine(A, B, Line2D{C, D}) &&
           doesSegmentIntersectLine(C, D, Line2D{A, B});
}

bool areSegmentsIntersected(const Point3D A, const Point3D B,
                            const Point3D C, const Point3D D)
{
    return doesSegmentIntersectLine(A, B, Line3D{C, D}) &&
           doesSegmentIntersectLine(C, D, Line3D{A, B});
}

ld findAngle(const Point2D p1, const Point2D p2)
{
    return atan2l(p1*p2, p1^p2);
}

ld findAngle(const Point3D p1, const Point3D p2)
{
    return atan2l((p1*p2).len2(), p1^p2);
}

bool isCounterClockwise(const Polygon &polygon)
{
    return sign(findArea(polygon)) > 0;
}

ld findArea(const Polygon &polygon)
{
    ld Area = 0;
    size_t N = polygon.size();
    for(size_t i = 0; i < N; ++i) {
        Area += polygon[i] * polygon[(i + 1) % N];
    }
    return Area / 2.0;
}