//
// Created by ivb on 02.03.17.
//
// Библиотека реализует основные операции над векторами в трехмерном
// пространстве, арифметику чисел с плавающей точкой,
// а также некоторые алгоритмы вычислительной геометрии.

#ifndef RAY_TRACING_GEOMETRY_H
#define RAY_TRACING_GEOMETRY_H

#include <vector>
#include <array>

struct Point2D;

// Многоугольник. Вершины задаются в порядке обхода.
typedef std::vector<Point2D> Polygon;

typedef long double ld;

// точка на плоскости
// координаты декартовы прямоугольные
struct Point2D {
    ld x, y;

    ld len() const;
    ld len2() const;
};

// точка на плоскости
// координаты декартовы прямоугольные
struct Point3D {
    ld x, y, z;

    ld len() const;
    ld len2() const;
};

// линия на плоскости
struct Line2D {
    Point2D A, B;
};

// линия в пространстве
struct Line3D {
    Point3D A, B;
};

// z == 0
bool isZero(ld z);

// знак числа: -1, 0, +1
int sign(ld z);

// x == y
bool areEqual(ld x, ld y);

// x < y
bool isLessThan(ld x, ld y);

// x > y
bool isMoreThan(ld x, ld y);

// x <= y
bool isLessEqual(ld x, ld y);

// x >= y
bool isMoreEqual(ld x, ld y);

// Геометрическая сумма векторов
Point2D operator+(const Point2D p1, const Point2D p2);
Point3D operator+(const Point3D p1, const Point3D p2);

// геометрическая разность векторов
Point2D operator-(const Point2D p1, const Point2D p2);
Point3D operator-(const Point3D p1, const Point3D p2);

// Умножение вектора на скаляр
Point2D operator*(const Point2D p, ld d);
Point2D operator*(ld d, const Point2D p);
Point3D operator*(const Point3D p, ld d);
Point3D operator*(ld d, const Point3D p);

// векторное произведение на плоскости возвращает число
ld operator*(const Point2D p1, const Point2D p2);

// векторное произведение в пространстве есть вектор
Point3D operator*(const Point3D p1, const Point3D p2);

// скалярное произведение
ld operator^(const Point2D p1, const Point2D p2);
ld operator^(const Point3D p1, const Point3D p2);

// смешанное произведение
ld tripleProduct(const Point3D p1, const Point3D p2, const Point3D p3);

// p1 == p2
bool areEqual(const Point2D p1, const Point2D p2);
bool areEqual(const Point3D p1, const Point3D p2);

// коллинеарность двух векторов
bool areCollinear(const Point2D p1, const Point2D p2);
bool areCollinear(const Point3D p1, const Point3D p2);

// принадлежность точки линии
bool isOnLine(const Point2D p, const Line2D l);
bool isOnLine(const Point3D p, const Line3D l);

// принадлежность точки отрезку
bool isOnSegment(const Point2D p, const Point2D A, const Point2D B);
bool isOnSegment(const Point3D p, const Point3D A, const Point3D B);

// проверка линий на параллельность
bool areLinesParallelOrEqual(const Line2D l1, const Line2D l2);
bool areLinesParallelOrEqual(const Line3D l1, const Line3D l2);

// проверка прямых в пространстве на принадлежность одной плоскости
bool areLinesInOnePlane(const Line3D l1, const Line3D l2);

// точка пересечения прямых
// ожидает что она сцществует, иначе assert
Point2D findLinesIntersection(const Line2D l1, const Line2D l2);
Point3D findLinesIntersection(const Line3D l1, const Line3D l2);

// проверка пересечения линии и отрезка
bool doesSegmentIntersectLine(const Point2D A, const Point2D B,
                              const Line2D l);
bool doesSegmentIntersectLine(const Point3D A, const Point3D B,
                              const Line3D l);

// проверка пересечения двух отрезков
bool areSegmentsIntersected(const Point2D A, const Point2D B,
                            const Point2D C, const Point2D D);
bool areSegmentsIntersected(const Point3D A, const Point3D B,
                            const Point3D C, const Point3D D);

// ориентированный угол между векторами
ld findAngle(const Point2D p1, const Point2D p2);
ld findAngle(const Point3D p1, const Point3D p2);

// многоугольник обходиться против часовой стрелки?
bool isCounterClockwise(const Polygon &polygon);

// ориентированная площадь многоугольника
ld findArea(const Polygon &polygon);

// точка лежит внутри полигона?
// полигон произвольный
//bool isPointInPolygon(const Polygon &polygon); //TODO

// точка лежит внутри полигона?
// полигон выпуклый, обходится против ч/с
//bool isPointInConvexPolygon(const Polygon &polygon); //TODO

#endif //RAY_TRACING_GEOMETRY_H
