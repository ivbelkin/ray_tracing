//
// Created by ivb on 12.03.17.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "Shape.h"
#include "Additional.h"

#include "geometry.h"

// ПРространственная сфера
class Sphere : public Shape {
public:
    // создать сферу по ее сентру и радиусу
    Sphere(Point3D _center, ld _radius, Color _color);

    // Пересечение сферы с лучом
    bool ray_intersection(Line3D & line, Point3D* point) const;

    // Цвет объекта в указанной точке
    Color get_color(Point3D & point) const;

    // Единичная внешняя нормаль к сфере в указанной точке
    Point3D get_normal(Point3D &point) const;

private:
    // центр сферы
    Point3D center;

    // радиус сферы
    ld radius;

    // цвет сферы
    Color color;
};

#endif //RAY_TRACING_SPHERE_H
