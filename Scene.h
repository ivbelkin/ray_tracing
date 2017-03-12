//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_SCENE_H
#define RAY_TRACING_SCENE_H

#include "Additional.h"
#include "Shape.h"

#include "geometry.h"

#include <vector>

class Scene {
public:
    bool add_shape(Shape* obj);

//private: //TODO
    std::vector<Shape*> shapes;
};

#endif //RAY_TRACING_SCENE_H
