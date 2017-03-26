//
// Created by ivb on 26.03.17.
//

#include "Shape.h"

Shape::Shape()
{
    material = nullptr;
}

Shape::Shape(Color color)
{
    material = new Material(color, color, Color(0, 0, 0),
                            Color(0, 0, 0), 0.0l, 0.0l, 0.0l, 1);
}

const Material* Shape:: get_material() const
{
    return material;
}

void Shape::set_material(const Material *_material)
{
    if(material != nullptr) {
        delete material;
    }
    material = _material;
}

void Shape::reset_material(const Material *_material)
{
    material = _material;
}