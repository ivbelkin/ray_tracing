//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include "Shape.h"
#include "Additional.h"

#include "geometry.h"

#include "Material.h"

// Пространственный треугольник
class Triangle : public Shape {
public:
    // Треугольник по трем точкам и нормали
    Triangle(Point3D _A, Point3D _B, Point3D _C, Point3D _n = {0, 0, 0});

    // Треугольник по трем точкам, цвету и внешней нормали
    Triangle(Point3D _A, Point3D _B, Point3D _C,
             Color _color, Point3D _n = {0, 0, 0});

    // Пересечение треугольника с лучом
    bool ray_intersection(Point3D p, Point3D v, Point3D *point) const;

    // Единичная внешняя нормаль к треугольнику в указанной точке
    Point3D get_normal(Point3D &point) const;

private:
    // Вершины треугольника
    Point3D A;
    Point3D B;
    Point3D C;

    // Единичная внешняя нормаль
    Point3D n;

    void set_normal(Point3D _n);

    // установить поля класса
    void init(Point3D _A, Point3D _B, Point3D _C, Point3D _n);
};

#endif //RAY_TRACING_TRIANGLE_H
