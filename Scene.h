//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_SCENE_H
#define RAY_TRACING_SCENE_H

#include "Color.h"
#include "Shape.h"
#include "Light.h"
#include "Material.h"
#include "geometry.h"

#include <vector>
#include <map>

struct Scene {
    // список объектов
    std::vector<Shape*> shapes;

    // список источников света
    std::vector<Light*> lights;

    // фоновое освещение
    Color backlight;

    // цвет на бесконечности
    Color backgroud;

    // библиотека материалов
    std::map<std::string, Appearance*> materials;

    // добавить новый объект
    bool add_shape(Shape *obj);

    // добавить новый источник освещения
    bool add_light(Light *obj);
};

#endif //RAY_TRACING_SCENE_H
