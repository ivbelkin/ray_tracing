//
// Created by ivb on 03.04.17.
//

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include "geometry.h"

class Camera {
public:
    // p - положение наблюдателя
    // center - задает точку, в направлении которой смотрит наблюдатель
    // n - направление, соответствующее вертикали
    // focus - расстояние от точки наблюдения до экрана
    // width, height - ширина и высота экрана
    Camera(Point3D _p, Point3D center, Point3D n, ld focus, ld width, ld height);

    // положение наблюдателя
    Point3D get_viewpoint();

    // верхний левый угол экрана
    Point3D get_topleft();

    // верхний правый угол экрана
    Point3D get_topright();

    // нижний левый угол экрана
    Point3D get_bottomleft();

private:
    // положение наблюдателя
    Point3D p;

    // координаты углов экрана
    Point3D topleft;
    Point3D bottomleft;
    Point3D topright;
};

#endif //RAY_TRACING_CAMERA_H
