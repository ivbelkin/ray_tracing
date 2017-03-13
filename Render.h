//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_RENDER_H
#define RAY_TRACING_RENDER_H

#include "Scene.h"
#include "Window.h"
#include "geometry.h"


class Render {
public:
    Render();

    void set_window(rt::Window * _window, Point3D _topleft,
                    Point3D _buttomleft, Point3D _topright);

    void set_scene(Scene * _scene);

    void set_viewpoint(Point3D _vievpoint);

    void draw();

private:
    rt::Window * window;
    Point3D topleft;
    Point3D buttomleft; //TODO
    Point3D topright;
    Scene * scene;
    Point3D viewpoint;

    // преобразует точку экрана в локальных координатах
    // в пространственную точку сцены
    Point3D to_point(int x, int y);

    // определяет цвет, в который необходимо покрасить
    // пиксель (x, y) экрана
    Color get_color_xy(int x, int y);

    // определяет цвет, который увидел бы наблюдатель
    // в центре поля зрения если бы находился в точке ray.A
    // и смотрел в направлении вектора (ray.B - ray.A)
    Color get_color_point(Line3D ray);

    // находит первое пересечение луча с объектом сцены, сохраняет
    // точку пересечения и указатель на объект и возвращает true,
    // если пересечения нет - возвращает false
    bool ray_trace(Line3D ray, Point3D *nearest_intersection, Shape **obj);
};

#endif //RAY_TRACING_RENDER_H
