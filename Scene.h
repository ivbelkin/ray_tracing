//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_SCENE_H
#define RAY_TRACING_SCENE_H

#include "Additional.h"
#include "Shape.h"
#include "Light.h"

#include "geometry.h"

#include <vector>

class Scene {
public:
    bool add_shape(Shape *obj);

    bool add_light(Light *obj);

//private: //TODO
    std::vector<Shape*> shapes;

    std::vector<Light*> lights;

    Color backlight;

    Color backgroud;
};

#endif //RAY_TRACING_SCENE_H
