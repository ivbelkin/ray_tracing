//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_RENDER_H
#define RAY_TRACING_RENDER_H

#include "Scene.h"
#include "Window.h"
#include "geometry.h"
#include "TraversalTree.h"


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

    // KD-дерево для ускорения поиска пересечений объектов
    // сцены с лучом
    TraversalTree tree;

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

    // составляющая цвета, зависящая от первичных источников
    Color scan_lights(Point3D point, Point3D view_vector, Shape *obj);
};

#endif //RAY_TRACING_RENDER_H
