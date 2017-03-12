//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include "Shape.h"
#include "Additional.h"

#include "geometry.h"

// Пространственный треугольник
class Triangle : public Shape {
public:
    // Треугольник по трем точкам
    Triangle(Point3D _A, Point3D _B, Point3D _C, Color _color);

    // Пересечение треугольника с прямой
    bool ray_intersection(Line3D & line, Point3D* point) const;

    // Цвет треугольника в указанной точке
    Color get_color(Point3D & point) const;

private:
    // Вершины треугольника
    Point3D A;
    Point3D B;
    Point3D C;

    // Цвет треугольника
    Color color;
};

#endif //RAY_TRACING_TRIANGLE_H
