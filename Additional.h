//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_ADDITIONAL_H
#define RAY_TRACING_ADDITIONAL_H

#include "geometry.h"
#include <cmath>

// Цвет
class Color {
public:
    Color() :
        red_inten(0),
        green_inten(0),
        blue_inten(0)
    {}

    Color(int _red, int _green, int _blue)
    {
        compare_and_set(&red_inten, _red);
        compare_and_set(&green_inten, _green);
        compare_and_set(&blue_inten, _blue);
    }

    Color operator+(Color c) const
    {
        return Color{std::min((int)red_inten + c.red_inten, 255),
                     std::min((int)green_inten + c.green_inten, 255),
                     std::min((int)blue_inten + c.blue_inten, 255)};
    }

    Color operator*(ld num) const
    {
        return Color(std::min(int(num * red_inten), 255),
                     std::min(int(num * green_inten), 255),
                     std::min(int(num * blue_inten), 255));
    }

    Color operator/(ld num) const
    {
        return Color((unsigned char)((ld)red_inten / num),
                     (unsigned char)((ld)green_inten / num),
                     (unsigned char)((ld)blue_inten / num));
    }

    Color operator^(Color mask) const
    {
        return Color((unsigned char)((ld)red_inten * mask.red_inten / 255),
                     (unsigned char)((ld)green_inten * mask.green_inten / 255),
                     (unsigned char)((ld)blue_inten * mask.blue_inten / 255));
    }

    inline unsigned char red()
    {
        return red_inten;
    }

    inline unsigned char green()
    {
        return green_inten;
    }

    inline unsigned char blue()
    {
        return blue_inten;
    }

private:
    unsigned char red_inten;
    unsigned char green_inten;
    unsigned char blue_inten;

    void compare_and_set(unsigned char *c, int _c)
    {
        if(_c >= 0 && _c < 256) {
            *c = _c;
        } else {
            *c = 0;
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
