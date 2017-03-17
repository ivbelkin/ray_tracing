//
// Created by ivb on 11.03.17.
//

#include "Triangle.h"
#include "geometry.h"

Triangle::Triangle(Point3D _A, Point3D _B, Point3D _C, Color _color, Point3D _n) :
    A(_A),
    B(_B),
    C(_C),
    color(_color)
{
    if(_n == Point3D{0, 0, 0}) {
        n = ((B - A) * (C - A)) * (1 / ((B - A) * (C - A)).len());
    } else {
        n = _n / _n.len();
    }
}

bool Triangle::ray_intersection(Line3D & line, Point3D* point) const
{
    ld tp = tripleProduct(C - A, line.B - line.A, B - A);
    // проверка на существование точки пересечения с плоскостью треугольника
    if(isZero(tp)) {
        return false;
    } else {
        // координаты точки пересечения в базисе (AB, AC) на плоскости
        ld alpha = -tripleProduct(C - A, line.B - line.A, A - line.A) / tp;
        ld beta = tripleProduct(B - A, line.B - line.A, A - line.A) / tp;

        // проверка на принадлежность точки пересечения треугольнику
        if(alpha >= 0 && beta >= 0 && alpha + beta <= 1) {
            Point3D p = A + alpha * (B - A) + beta * (C - A);
            // проверка на пересечение с лучом
            if(((line.B - line.A) ^ (p - line.A)) > 0) {
                *point = p;
                return true;
            }
        }
        return false;
    }
}

Color Triangle::get_color(Point3D &point) const
{
    return color;
}

Point3D Triangle::get_normal(Point3D &point) const
{
    return n;
}