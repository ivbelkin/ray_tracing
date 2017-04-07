//
// Created by ivb on 11.03.17.
//
#include "Light.h"
#include "Color.h"

#include "geometry.h"

#include <cassert>

ld Light::norm_power = 1;
ld Light::norm_distance = 1;

Light::Light(Point3D _position, double _power, Color _color) :
    position(_position),
    color(_color)
{
    assert(_power >= 0);
    power = _power;
}

Color Light::get_intensity(Point3D point) const
{
    ld coef = norm_distance * norm_distance * power / norm_power;

    return color * (coef / (point - position).len2());
}

Point3D Light::get_position() const
{
    return position;
}

void Light::set_norm_power(ld _norm_power)
{
    norm_power = _norm_power;
}

void Light::set_norm_distance(ld _norm_distance)
{
    norm_distance = _norm_distance;
}
