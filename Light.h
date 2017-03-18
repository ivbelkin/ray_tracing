//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_LIGHT_H
#define RAY_TRACING_LIGHT_H

#include "Additional.h"

#include "geometry.h"

// Источник света света
class Light { // TODO
public:
    // Источник в заданной позиции, заданной мощности и цвета
    Light(Point3D _position, double _power, Color _color = {255, 255, 255});

    // Освещенность малой площадки, помещенной в точку point
    // с вектором нормали normal
    Color get_color(Point3D point, Point3D normal) const;

    // Положение источника на сцене
    Point3D get_position() const;

private:
    // положение источника
    Point3D position;

    // мощность источника
    double power;

    // цвет источника света
    Color color;

    // нормировочные коэфиициенты
    static double norm_power;
    static double norm_distance;
};

#endif //RAY_TRACING_LIGHT_H
