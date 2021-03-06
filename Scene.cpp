//
// Created by ivb on 11.03.17.
//

#include "Scene.h"

#include <cassert>

bool Scene::add_shape(Shape *obj)
{
    assert(obj != nullptr);

    shapes.push_back(obj);

    return true;
}

bool Scene::add_light(Light *obj)
{
    assert(obj != nullptr);

    lights.push_back(obj);

    return true;
}
