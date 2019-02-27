//
// Created by ivb on 07.04.17.
//

#include "Quadrangle.h"
#include "Triangle.h"

inline ld min_of_four(ld a, ld b, ld c, ld d)
{
    return std::fminl(std::fminl(a, b), std::fminl(c, d));
}

inline ld max_of_four(ld a, ld b, ld c, ld d)
{
    return std::fmaxl(std::fmaxl(a, b), std::fmaxl(c, d));
}

Quadrangle::Quadrangle(Point3D _A, Point3D _B, Point3D _C, Point3D _D, Point3D _n)
{
    init(_A, _B, _C, _D, _n);
}

Quadrangle::Quadrangle(Point3D _A, Point3D _B, Point3D _C, Point3D _D, Color _color, Point3D _n) :
        Shape(_color)
{
    init(_A, _B, _C, _D, _n);
}

bool Quadrangle::ray_intersection(Point3D p, Point3D v, Point3D *point) const
{
    Triangle t1(A, B, D);
    Triangle t2(C, B, D);
    if(t1.ray_intersection(p, v, point)) {
        return true;
    } else if(t2.ray_intersection(p, v, point)) {
        return true;
    } else {
        return false;
    }
}

Point3D Quadrangle::get_normal(Point3D &point) const
{
    return n;
}

void Quadrangle::set_normal(Point3D _n)
{
    // если получен нулевой вектор, то ставим правовинтовую нормаль
    if(_n == Point3D{0, 0, 0}) {
        n = ((B - A) * (C - A)) * (1 / ((B - A) * (C - A)).len());
    } else {
        n = _n / _n.len();
    }
}

void Quadrangle::init(Point3D _A, Point3D _B, Point3D _C, Point3D _D, Point3D _n)
{
    A = _A;
    B = _B;
    C = _C;
    D = _D;
    set_normal(_n);
}

void Quadrangle::limiting_box(Point3D *p1, Point3D *p2) const
{
    p1->x = min_of_four(A.x, B.x, C.x, D.x);
    p1->y = min_of_four(A.y, B.y, C.y, D.y);
    p1->z = min_of_four(A.z, B.z, C.z, D.z);
    *p1 = *p1 - Point3D{eps, eps, eps};

    p2->x = max_of_four(A.x, B.x, C.x, D.x);
    p2->y = max_of_four(A.y, B.y, C.y, D.y);
    p2->z = max_of_four(A.z, B.z, C.z, D.z);
    *p2 = *p2 + Point3D{eps, eps, eps};
}

Quadrangle::Quadrangle(Point3D _A, Point3D _B, Point3D _C, Point3D _D,
                       Point2D _a, Point2D _b, Point2D _c, Point2D _d,
                       Point3D _n) :
        Quadrangle(_A, _B, _C, _D, _n)
{
    a = _a;
    b = _b;
    c = _c;
    d = _d;
}

Material Quadrangle::get_material(Point3D p) const
{
    if(appearance->map_Kd == nullptr) {
        return *appearance->base;
    } else {
        Triangle t1(A, B, D, a, b, d);
        Triangle t2(C, B, D, c, b, d);

        t1.reset_material(appearance);
        t2.reset_material(appearance);

        Point3D point;

        if(t1.ray_intersection(p + eps*Point3D{0, 0, 1}, Point3D{0, 0, -1}, &point)) {
            return t1.get_material(p);
        } else {
            return t2.get_material(p);
        }
    }
}