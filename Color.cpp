//
// Created by ivb on 07.04.17.
//

#include "Color.h"

Color::Color() :
        red_inten(0),
        green_inten(0),
        blue_inten(0)
{}

Color::Color(ld _red, ld _green, ld _blue)
{
    compare_and_set(&red_inten, _red);
    compare_and_set(&green_inten, _green);
    compare_and_set(&blue_inten, _blue);
}

Color::Color(int _red, int _green, int _blue) :
        Color((ld)_red / 255,
              (ld)_green / 255,
              (ld)_blue / 255)
{}

Color Color::operator+(Color c) const
{
    return Color(red_inten + c.red_inten,
                 green_inten + c.green_inten,
                 blue_inten + c.blue_inten);
}

Color Color::operator+(ld num) const
{
    return Color(red_inten + num,
                 green_inten + num,
                 blue_inten + num);
}

Color Color::operator-(ld num) const
{
    return *this + (-num);
}

Color Color::operator*(ld num) const
{
    return Color(num * red_inten,
                 num * green_inten,
                 num * blue_inten);
}

Color Color::operator/(ld num) const
{
    return Color(red_inten / num,
                 green_inten / num,
                 blue_inten / num);
}

Color Color::operator^(Color mask) const
{
    return Color(red_inten * mask.red_inten,
                 green_inten * mask.green_inten,
                 blue_inten * mask.blue_inten);
}

int Color::red()
{
    return int(red_inten * 255);
}

int Color::green()
{
    return int(green_inten * 255);
}

int Color::blue()
{
    return int(blue_inten * 255);
}

void Color::compare_and_set(ld *c, ld _c)
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

Color operator+(ld num, Color color)
{
    return color + num;
}

Color operator-(ld num, Color color)
{
    return Color(num - color.red_inten,
                 num - color.green_inten,
                 num - color.blue_inten);
}

std::ifstream& operator>>(std::ifstream &in, Color &color)
{
    in >> color.red_inten >> color.green_inten >> color.blue_inten;
    return in;
}