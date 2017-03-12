//
// Created by ivb on 11.03.17.
//
#include "Light.h"
#include "Additional.h"

#include "geometry.h"

#include <cassert>


Light::Light(Point3D _position, double _power) :
    position(_position)
{
    assert(_power >= 0);
    power = _power;
}

Color Light::get_color(Point3D point) const
{
    return Color();
}
