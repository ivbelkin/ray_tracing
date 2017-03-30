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
    material = new Material(color, color, {0, 0, 0},
                            Color(255, 255, 255), 0.8l, 70l, 0.0l, 2);
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

Point3D Shape::reflected_ray(Point3D v, Point3D point) const
{
    Point3D N = get_normal(point);
    ld alpha = -1.0 * N ^ v;
    return v + 2 * alpha * N;
}

Point3D Shape::refracted_ray(Point3D v, Point3D point) const
{
    v = v.unit();
    // нормаль в точке падения
    Point3D n = get_normal(point);

    // угол преломления
    ld beta = 0;

    // ОНБ в плоскости падения
    // выберем базис так, чтобы e1 и e2 смотрели в полуплоскость
    // распространения преломленного луча
    Point3D e1, e2;

    if(isZero(v ^ n) || areCollinear(v, n)) {
        return v;
    } else if(sign(v ^ n) < 0) {
        beta = asinl((n * v).len() * get_material()->Ni);
        e1 = -1.0 * n;
    } else {
        beta = asinl((n * v).len() / get_material()->Ni);
        e1 = n;
    }

    // проверим на эффект полного внутреннего отражения
    if(isnanl(beta)) {
        return reflected_ray(v, point);
    }

    e2 = (-1.0 * e1 + v / (v ^ e1)).unit();

    return e1 * cosl(beta) + e2 * sinl(beta);
}