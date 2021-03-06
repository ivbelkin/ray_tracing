//
// Created by ivb on 26.03.17.
//

#include "Shape.h"

Shape::Shape()
{
    appearance = nullptr;
}

Shape::Shape(Color color)
{
    appearance = new Appearance;
    appearance->base = new Material(color, color, color, Color(255, 255, 255), 70l, 0.0l);
    appearance->Ni = 1.0;
    appearance->illum = 1;
    appearance->map_Kd = nullptr;
}

Material Shape:: get_material(Point3D p) const
{
    return *appearance->base;
}

void Shape::reset_material(Appearance *_appearance)
{
    appearance = _appearance;
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
        beta = asinl((n * v).len() * appearance->Ni);
        e1 = -1.0 * n;
    } else {
        beta = asinl((n * v).len() / appearance->Ni);
        e1 = n;
    }

    // проверим на эффект полного внутреннего отражения
    if(isnanl(beta)) {
        return reflected_ray(v, point);
    }

    e2 = (-1.0 * e1 + v / (v ^ e1)).unit();

    return e1 * cosl(beta) + e2 * sinl(beta);
}

int Shape::get_illum()
{
    return appearance->illum;
}
