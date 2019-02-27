//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include "Shape.h"
#include "Color.h"

#include "geometry.h"

#include "Material.h"

// Пространственный треугольник
class Triangle : public Shape {
public:
    // Треугольник по трем точкам и нормали
    Triangle(Point3D _A, Point3D _B, Point3D _C, Point3D _n = {0, 0, 0});

    // Треугольник по трем точкам, текстурным координатам и нормали
    Triangle(Point3D _A, Point3D _B, Point3D _C, Point2D _a, Point2D _b, Point2D _c, Point3D _n = {0, 0, 0});

    // Треугольник по трем точкам, цвету и внешней нормали
    Triangle(Point3D _A, Point3D _B, Point3D _C,
             Color _color, Point3D _n = {0, 0, 0});

    // Пересечение треугольника с лучом
    bool ray_intersection(Point3D p, Point3D v, Point3D *point) const;

    // Единичная внешняя нормаль к треугольнику в указанной точке
    Point3D get_normal(Point3D &point) const;

    // ограничивающий параллелепипед минимального объема
    // точка p1 - имеет наименьшие координаты, p2 - наибольшие
    void limiting_box(Point3D *p1, Point3D *p2) const;

    // Получить структуру, описывающую своиства материала в точке
    Material get_material(Point3D p) const;

private:
    // Вершины треугольника
    Point3D A;
    Point3D B;
    Point3D C;

    // Единичная внешняя нормаль
    Point3D n;

    // Текстурные координаты
    Point2D a;
    Point2D b;
    Point2D c;

    void set_normal(Point3D _n);

    // установить поля класса
    void init(Point3D _A, Point3D _B, Point3D _C, Point3D _n);
};

#endif //RAY_TRACING_TRIANGLE_H
