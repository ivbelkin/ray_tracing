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

    void set_depth(int d);

    void draw();

private:
    // окно, в котором будет отрисовываться сцена
    rt::Window * window;

    // координаты углов экрана
    Point3D topleft;
    Point3D buttomleft; //TODO
    Point3D topright;

    // сцена для отрисовки
    Scene * scene;

    // положение наблюдателя
    Point3D viewpoint;

    // глубина рекурсии для поиска вторичных источников
    // значение по-умолчанию 0 - не искать вторичные источники
    int depth;

    // преобразует точку экрана в локальных координатах
    // в пространственную точку сцены
    Point3D to_point(int x, int y);

    // определяет цвет, в который необходимо покрасить
    // пиксель (x, y) экрана
    Color get_color_xy(int x, int y);

    // определяет цвет, который увидел бы наблюдатель
    // в центре поля зрения если бы находился в точке p
    // и смотрел в направлении вектора v
    Color get_color_point(Point3D p, Point3D v, int d);

    // находит первое пересечение луча с объектом сцены, сохраняет
    // точку пересечения и указатель на объект и возвращает true,
    // если пересечения нет - возвращает false
    bool ray_trace(Point3D p, Point3D v, Point3D *nearest_intersection, Shape **object);

    // проверяет, достижима ли B из точки A некоторого объекта по прямой,
    // не пересекая другие объекты
    bool is_reachable(Point3D A, Point3D B);


    // модели освещения

    // illum 0
    // цвет объекта не зависит ни от чего
    Color constant_illum(Shape *obj);

    // illum 1
    // цвет определяется фоновым освещением и диффузным рассеиванием
    Color diffuse_illum(Point3D point, Point3D viev_vector, Shape *obj);

    // illum 2
    // к диффузному рассеиванию добавляется бликовое
    Color specular_illum(Point3D point, Point3D viev_vector, Shape *obj);

    // illum 8, 9
    // добавляется карта отражений
    Color map_illum(Point3D point, Point3D viev_vector, Shape *obj);

    // illum 3, 4
    // добавляются вторичные источники
    Color multireflect_illum(Point3D point, Point3D viev_vector, Shape *obj);

    // illum 6
    // добавляется преломление лучей
    Color multirefract_illum(Point3D point, Point3D viev_vector, Shape *obj);
};

#endif //RAY_TRACING_RENDER_H
