//
// Created by ivb on 11.03.17.
//

#include "Triangle.h"
#include "geometry.h"

Triangle::Triangle(Point3D _A, Point3D _B, Point3D _C, Point3D _n)
{
    init(_A, _B, _C, _n);
}

Triangle::Triangle(Point3D _A, Point3D _B, Point3D _C, Color _color, Point3D _n) :
        Shape(_color)
{
    init(_A, _B, _C, _n);
}

bool Triangle::ray_intersection(Point3D p, Point3D v, Point3D *point) const
{
    ld tp = tripleProduct(C - A, v, B - A);
    // проверка на существование точки пересечения с плоскостью треугольника
    if(isZero(tp)) {
        return false;
    } else {
        // координаты точки пересечения в базисе (AB, AC) на плоскости
        ld alpha = -tripleProduct(C - A, v, A - p) / tp;
        ld beta = tripleProduct(B - A, v, A - p) / tp;

        // проверка на принадлежность точки пересечения треугольнику
        if(alpha >= 0 && beta >= 0 && alpha + beta <= 1) {
            Point3D pp = A + alpha * (B - A) + beta * (C - A);
            // проверка на пересечение с лучом
            if(((v) ^ (pp - p)) > 0) {
                *point = pp;
                return true;
            }
        }
        return false;
    }
}

Point3D Triangle::get_normal(Point3D &point) const
{
    return n;
}

void Triangle::set_normal(Point3D _n)
{
    // если получен нулевой вектор, то ставим правовинтовую нормаль
    if(_n == Point3D{0, 0, 0}) {
        n = ((B - A) * (C - A)) * (1 / ((B - A) * (C - A)).len());
    } else {
        n = _n / _n.len();
    }
}

void Triangle::init(Point3D _A, Point3D _B, Point3D _C, Point3D _n)
{
    A = _A;
    B = _B;
    C = _C;
    set_normal(_n);
}


