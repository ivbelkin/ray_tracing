//
// Created by ivb on 11.03.17.
//
#include "Light.h"
#include "Additional.h"

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

Color Light::get_color(Point3D point, Point3D normal) const
{
    ld coef = norm_distance * norm_distance * power / norm_power;
    ld cos_r_n = (ld)(normal ^ (position - point)) / (point - position).len();

    return color * (coef * cos_r_n / (point - position).len2());
}

Point3D Light::get_position() const
{
    return position;
}
