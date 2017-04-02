//
// Created by ivb on 12.03.17.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "Shape.h"
#include "Additional.h"
#include "geometry.h"

// Пространственная сфера
class Sphere : public Shape {
public:
    // создать сферу по ее центру и радиусу
    Sphere(Point3D _center, ld _radius);

    // создать сферу по ее центру, радиусу и диффузному цвету
    Sphere(Point3D _center, ld _radius, Color _color);

    // Пересечение сферы с лучом
    bool ray_intersection(Point3D p, Point3D v, Point3D *point) const;

    // Единичная внешняя нормаль к сфере в указанной точке
    Point3D get_normal(Point3D &point) const;

    // ограничивающий параллелепипед минимального объема
    // точка A - имеет наименьшие координаты, B - наибольшие
    void limiting_box(Point3D *A, Point3D *B) const;

private:
    // центр сферы
    Point3D center;

    // радиус сферы
    ld radius;

    // установить поля класса
    void init(Point3D _center, ld _radius);
};

#endif //RAY_TRACING_SPHERE_H
