//
// Created by ivb on 12.03.17.
//

#include "Sphere.h"

#include "geometry.h"
#include <cassert>
#include <cmath>

Sphere::Sphere(Point3D _center, ld _radius)
{
    init(_center, _radius);
}

Sphere::Sphere(Point3D _center, ld _radius, Color _color) :
        Shape(_color)
{
    init(_center, _radius);
}

bool Sphere::ray_intersection(Point3D p, Point3D v, Point3D *point) const
{
    // коэффициенты квадратного уравнения
    ld a = v.len2();
    ld b = -2.0 * ((center - p)^v);
    ld c = ((center - p)^(center - p)) - radius * radius;

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
            *point = p + alpha1 * v;
            return true;
        } else if(alpha2 >= 0) {
            *point = p + alpha2 * v;
            return true;
        } else {
            // иначе луч не пересекает сферу
            return false;
        }
    }
}

Point3D Sphere::get_normal(Point3D &point) const
{
    return (point - center) / (point - center).len();
}

void Sphere::init(Point3D _center, ld _radius)
{
    center = _center;
    assert(_radius > 0);
    radius = _radius;
}

void Sphere::limiting_box(Point3D *A, Point3D *B) const
{
    Point3D bias{radius + eps, radius + eps, radius + eps};
    *A = center - bias;
    *B = center + bias;
}
