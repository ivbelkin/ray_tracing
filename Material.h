//
// Created by ivb on 25.03.17.
//
// описнание формата mtl (Material Template Library):
//      http://paulbourke.net/dataformats/mtl/

#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H

#include "Additional.h"

#include <SDL/SDL_image.h>

// материал
// имена атрибутов соответствуют именам из фаила .mtl
struct Material {
    Material(Color _Ka, Color _Kd, Color _Ks, Color _Tf, ld _Ns, ld _d) :
            Ka(_Ka),
            Kd(_Kd),
            Ks(_Ks),
            Tf(_Tf),
            Ns(_Ns),
            d(_d)
    {}
    // ambient reflectance
    // цвет, который имеет объект при отсутствии прямого света
    Color Ka;

    // diffuse reflectance
    // диффузный цвет, т.е. рассеиваемый во все стороны
    // с одинаковой интенсивностью
    Color Kd;

    // specular reflectance
    // зеркальный цвет, определяет цвет бликов на объекте
    Color Ks;

    // transmission filter
    // прозрачность объекта, определяет компоненты прошедшего света
    Color Tf;

    // specular exponent
    // определяет форму диаграммы направленности отраженного излучения
    ld Ns;

    // factor
    // коэффициент прозрачности
    ld d;
};

struct Appearance {
    // основные своиства материала
    // будут смешиваться с текстурами
    Material *base;

    // optical_density
    // коэффициент преломления
    ld Ni;

    // текстура диффузного цвета
    SDL_Surface *map_Kd;

    // модель освещения
    int illum; // TODO сделать enum
};

#endif //RAY_TRACING_MATERIAL_H
