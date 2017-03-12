//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_SHAPE_H
#define RAY_TRACING_SHAPE_H

#include "geometry.h"
#include "Additional.h"

class Shape {
public:
    // Пересечение объекта с прямой
    virtual bool ray_intersection(Line3D & line, Point3D* point) const = 0;

    // Цвет объекта в указанной точке
    virtual Color get_color(Point3D & point) const = 0;
};

#endif //RAY_TRACING_SHAPE_H