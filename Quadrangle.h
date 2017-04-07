//
// Created by ivb on 07.04.17.
//

#ifndef RAY_TRACING_QUADRANGLE_H
#define RAY_TRACING_QUADRANGLE_H

#include "geometry.h"
#include "Shape.h"

// Плоский четырехугольник в пространстве
class Quadrangle : public Shape {
public:
    // Четырехугольник по трем точкам и нормали
    Quadrangle(Point3D _A, Point3D _B, Point3D _C, Point3D _D,
             Point3D _n = {0, 0, 0});

    // Четырехугольник по трем точкам, текстурным координатам и нормали
    Quadrangle(Point3D _A, Point3D _B, Point3D _C, Point3D _D,
             Point2D _a, Point2D _b, Point2D _c, Point2D _d,
             Point3D _n = {0, 0, 0});

    // Четырехугольник по трем точкам, цвету и внешней нормали
    Quadrangle(Point3D _A, Point3D _B, Point3D _C, Point3D _D,
             Color _color, Point3D _n = {0, 0, 0});

    // Пересечение четырехугольника с лучом
    bool ray_intersection(Point3D p, Point3D v, Point3D *point) const;

    // Единичная внешняя нормаль к четырехугольнику в указанной точке
    Point3D get_normal(Point3D &point) const;

    // ограничивающий параллелепипед минимального объема
    // точка p1 - имеет наименьшие координаты, p2 - наибольшие
    void limiting_box(Point3D *p1, Point3D *p2) const;

    // Получить структуру, описывающую своиства материала в точке
    Material get_material(Point3D p) const;

private:
    // Вершины четырехугольника
    Point3D A;
    Point3D B;
    Point3D C;
    Point3D D;

    // Единичная внешняя нормаль
    Point3D n;

    // Текстурные координаты
    Point2D a;
    Point2D b;
    Point2D c;
    Point2D d;

    void set_normal(Point3D _n);

    // установить поля класса
    void init(Point3D _A, Point3D _B, Point3D _C, Point3D _D, Point3D _n);
};

#endif //RAY_TRACING_QUADRANGLE_H
