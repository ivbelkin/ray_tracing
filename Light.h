//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_LIGHT_H
#define RAY_TRACING_LIGHT_H

#include "Additional.h"

#include "geometry.h"

// Источник белого света
class Light { // TODO
public:
    // Источник в заданной позиции и заданной мощности
    Light(Point3D _position, double _power);

    // Освещенность малой площадки, помещенной в точку point
    // перпендикулярно вектору (point - position)
    Color get_color(Point3D point) const;

private:
    // положение источника
    Point3D position;

    // мощность источника
    double power;

    // нормировочные коэфиициенты
    static double norm_power;
    static double norm_distance;
};

#endif //RAY_TRACING_LIGHT_H
