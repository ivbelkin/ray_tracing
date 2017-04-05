//
// Created by ivb on 03.04.17.
//

#include "Camera.h"

#include <cmath>

Camera::Camera(Point3D _p, Point3D center, Point3D n, ld focus, ld width, ld height) :
    p(_p)
{
    // верктор наблюдения
    Point3D v = (center - p).unit();

    // нормируем вектор вертикали
    n = n.unit();

    // u1, u2 - ОНБ в пространстве экрана
    ld vn = v^n;
    ld alpha = 1.0 / sqrtl(1.0 - vn * vn);
    ld beta = -alpha * vn;
    Point3D u1 = alpha * n + beta * v;
    Point3D u2 = u1 * v;

    // вычисляем положения углов экрана
    topleft = p + focus * v + u1 * height / 2 + u2 * width / 2;
    topright = p + focus * v + u1 * height / 2 - u2 * width / 2;
    bottomleft = p + focus * v - u1 * height / 2 + u2 * width / 2;
}

Point3D Camera::get_viewpoint()
{
    return p;
}

Point3D Camera::get_topleft()
{
    return topleft;
}

Point3D Camera::get_topright()
{
    return topright;
}

Point3D Camera::get_bottomleft()
{
    return bottomleft;
}
