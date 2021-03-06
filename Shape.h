//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_SHAPE_H
#define RAY_TRACING_SHAPE_H

#include "geometry.h"
#include "Color.h"
#include "Material.h"

class Shape {
public:
    // нет данных о материале
    Shape();

    // устанавливается модель чисто диффузного отражения
    explicit Shape(Color color);

    // Первое пересечение объекта с лучом с началом в p и направлением v
    // в point сохраняется точка пересечения
    virtual bool ray_intersection(Point3D p, Point3D v, Point3D *point) const = 0;

    // Единичная внешняя нормаль к объекту в указанной точке
    virtual Point3D get_normal(Point3D &point) const = 0;

    // ограничивающий параллелепипед минимального объема
    // точка A - имеет наименьшие координаты, B - наибольшие
    virtual void limiting_box(Point3D *A, Point3D *B) const = 0;

    // Отраженный в точке point луч с направлением v
    Point3D reflected_ray(Point3D v, Point3D point) const;

    // Преломленный при проходе через поверхность объекта луч
    Point3D refracted_ray(Point3D v, Point3D point) const;

    // Получить структуру, описывающую своиства материала в точке
    virtual Material get_material(Point3D p) const;

    // Установить материал, старая структура не удаляется
    void reset_material(Appearance *_appearance);

    // получить установленную модель отражения
    int get_illum();

protected:
    const ld eps = 1e-3; // TODO
    // данные о материале и модели отражения
    Appearance *appearance;

private:

};

#endif //RAY_TRACING_SHAPE_H
