//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_ADDITIONAL_H
#define RAY_TRACING_ADDITIONAL_H

#include "geometry.h"
#include <cmath>

#include <cassert>
#include <iostream>

// Цвет
class Color {
public:
    Color() :
        red_inten(0),
        green_inten(0),
        blue_inten(0)
    {}

    Color(ld _red, ld _green, ld _blue)
    {
        compare_and_set(&red_inten, _red);
        compare_and_set(&green_inten, _green);
        compare_and_set(&blue_inten, _blue);
    }

    Color(int _red, int _green, int _blue) :
            Color((ld)_red / 255,
                  (ld)_green / 255,
                  (ld)_blue / 255)
    {}

    Color operator+(Color c) const
    {
        return Color(red_inten + c.red_inten,
                     green_inten + c.green_inten,
                     blue_inten + c.blue_inten);
    }

    Color operator*(ld num) const
    {
        return Color(num * red_inten,
                     num * green_inten,
                     num * blue_inten);
    }

    Color operator/(ld num) const
    {
        return Color(red_inten / num,
                     green_inten / num,
                     blue_inten / num);
    }

    Color operator^(Color mask) const
    {
        return Color(red_inten * mask.red_inten,
                     green_inten * mask.green_inten,
                     blue_inten * mask.blue_inten);
    }

    inline int red()
    {
        return int(red_inten * 255);
    }

    inline int green()
    {
        return int(green_inten * 255);
    }

    inline int blue()
    {
        return int(blue_inten * 255);
    }

private:
    ld red_inten;
    ld green_inten;
    ld blue_inten;

    void compare_and_set(ld *c, ld _c)
    {
        if(isMoreEqual(_c, 0.0)) {
            if(isLessEqual(_c, 1.0)) {
                *c = _c;
            } else {
                *c = 1.0;
            }
        } else {
            *c = 0.0;
        }
    }
};

// Плоская волна определенного цвета и направления
struct Wave {
    Wave(Color c, Point3D p)
    {
        color = c;
        k = p * (1.0 / p.len());
    }

    // Цвет
    Color color;

    // Направление. Единичный вектор
    Point3D k;

    // Проекция волны на вектор n
    Wave operator^(Point3D n) const
    {
        return Wave(color * ((k ^ n) / n.len()), (k ^ n) / n.len() * n);
    }
};

#endif //RAY_TRACING_ADDITIONAL_H
