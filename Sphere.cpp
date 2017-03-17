//
// Created by ivb on 12.03.17.
//

#include "Sphere.h"

#include "geometry.h"
#include <cassert>
#include <cmath>

Sphere::Sphere(Point3D _center, ld _radius, Color _color) :
    center(_center),
    color(_color)
{
    assert(_radius > 0);
    radius = _radius;
}

bool Sphere::ray_intersection(Line3D &line, Point3D *point) const
{
    // напрявляющий вектор прямой
    Point3D v = line.B - line.A;

    // коэффициенты квадратного уравнения
    ld a = v.len2();
    ld b = -2.0 * ((center - line.A)^v);
    ld c = ((center - line.A)^(center - line.A)) - radius * radius;

    // его дискриминант
    ld D = b * b - 4 * a * c;

    if(D < 0) {
        // нет пересечений
        return false;
    } else {
        // пересечения с прямой есть, выберем из них первое.
        // корни уравнения
        ld alpha1 = (-b - sqrtl(D)) / (2 * a);
        ld alpha2 = (-b + sqrtl(D)) / (2 * a);

        // выберем из них корень соответствующий ближайшей
        // точке пересечения сферы с лучом
        if(alpha1 >= 0) {
            *point = line.A + alpha1 * v;
            return true;
        } else if(alpha2 >= 0) {
            *point = line.A + alpha2 * v;
            return true;
        } else {
            // иначе луч не пересекает сферу
            return true;
        }
    }
}

Color Sphere::get_color(Point3D &point) const
{
    return color;
}

Point3D Sphere::get_normal(Point3D &point) const
{
    return (point - center) / (point - center).len();
}