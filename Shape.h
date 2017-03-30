//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_SHAPE_H
#define RAY_TRACING_SHAPE_H

#include "geometry.h"
#include "Additional.h"
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

    // Отраженный в точке point луч с направлением v
    Point3D reflected_ray(Point3D v, Point3D point) const;

    // Преломленный при проходе через поверхность объекта луч
    Point3D refracted_ray(Point3D v, Point3D point) const;

    // Получить структуру, описывающую своиства материала и модель отражения
    const Material* get_material() const;

    // Установить материал, старая структура удаляется
    void set_material(const Material *_material);

    // Установить материал, старая структура не удаляется
    void reset_material(const Material *_material);

private:
    // данные о материале и модели отражения
    const Material *material;
};

#endif //RAY_TRACING_SHAPE_H
