//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_ADDITIONAL_H
#define RAY_TRACING_ADDITIONAL_H

#include "geometry.h"
#include <cmath>

#include <cassert>
#include <iostream>
#include <fstream>

// Цвет
class Color {
    friend Color operator-(ld num, Color color);
    friend std::ifstream& operator>>(std::ifstream &in, Color &color);

public:
    Color();

    // значения компонент [0, 1]
    Color(ld _red, ld _green, ld _blue);

    // значения компонент 0..255
    Color(int _red, int _green, int _blue);

    // покомпонентное сложение
    Color operator+(Color c) const;

    // сложение с каждой компонентой
    Color operator+(ld num) const;

    // вычитание из каждой компоненты
    Color operator-(ld num) const;

    // умножение каждой компоненты
    Color operator*(ld num) const;

    // деление каждой комоненты
    Color operator/(ld num) const;

    // покомпонентное умножение
    Color operator^(Color mask) const;

    // интенсивность красного
    int red();

    // интенсивность зеленого
    int green();

    // интенсивность синего
    int blue();

private:
    // значения интенсивностей от 0 до 1
    ld red_inten;
    ld green_inten;
    ld blue_inten;

    // проверка на допустимое значение компоненты и присваивание
    void compare_and_set(ld *c, ld _c);
};

Color operator+(ld num, Color color);

Color operator-(ld num, Color color);

std::ifstream& operator>>(std::ifstream &in, Color &color);

#endif //RAY_TRACING_ADDITIONAL_H
