//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_LIGHT_H
#define RAY_TRACING_LIGHT_H

#include "Color.h"

#include "geometry.h"

// Источник света света
class Light {
public:
    // Источник в заданной позиции, заданной мощности и цвета
    Light(Point3D _position, double _power, Color _color = Color(255, 255, 255));

    // Освещенность малой площадки, помещенной в точку point
    // перпендикулярно падающему лучу
    Color get_intensity(Point3D point) const;

    // Положение источника на сцене
    Point3D get_position() const;

    // установка нормировочных коэффициентов
    static void set_norm_power(ld _norm_power);
    static void set_norm_distance(ld _norm_distance);

private:
    // положение источника
    Point3D position;

    // мощность источника
    double power;

    // цвет источника света
    Color color;

    // нормировочные коэфиициенты
    static ld norm_power;
    static ld norm_distance;
};

#endif //RAY_TRACING_LIGHT_H
