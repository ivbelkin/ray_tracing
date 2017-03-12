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

    // лежит ли сфера в полупространстве луча
    if((v^(center - line.A + v * (radius / v.len()))) <= 0) {
        return false;
    } else {
        // коэффициенты квадратного уравнения
        ld a = v.len2();
        ld b = -2.0 * ((center - line.A)^v);
        ld c = ((center - line.A)^(center - line.A)) - radius * radius;

        // его дискриминант
        ld D = b * b - 4 * a * c;

        if(D < 0) {
            return false;
        } else {
            // берем меньший корень
            ld alpha = (-b - sqrtl(D)) / (2 * a);
            *point = line.A + alpha * v;
            return true;
        }
    }
}

Color Sphere::get_color(Point3D &point) const
{
    return color;
}
