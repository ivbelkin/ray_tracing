//
// Created by ivb on 12.03.17.
//

#include "Render.h"
#include <iostream>
#include <cassert>
#include <cmath>

#include <ctime>

const ld eps = 1e-3;

Render::Render() :
    depth(2)
{
    window = nullptr;
    scene = nullptr;
}

void Render::set_window(rt::Window *_window, Point3D _topleft,
                        Point3D _buttomleft, Point3D _topright)
{
    window = _window;
    topleft = _topleft;
    buttomleft = _buttomleft;
    topright = _topright;
}

void Render::set_scene(Scene *_scene)
{
    scene = _scene;
}

void Render::set_viewpoint(Point3D _viewpoint)
{
    viewpoint = _viewpoint;
}

void Render::set_depth(int d)
{
    if(d >= 0 && d <= 10) {
        depth = d;
    } else {
        depth = 0;
    }
}

void Render::draw()
{
    assert(window != nullptr);
    assert(scene != nullptr);

    std::cout << "Build..." << std::endl;

    tree.build_from_shapes(scene->shapes);

    int height = window->get_height();
    int width = window->get_width();

    std::cout << "Rendering..." << std::endl;

    time_t time1 = clock();

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            Color c = get_color_xy(x, y);
            window->set_pixel_at(x, y, c);
        }
    }

    time1 = clock() - time1;

    std::cerr << "Time: " << (ld)time1 / CLOCKS_PER_SEC << std::endl;
}

Point3D Render::to_point(int x, int y)
{
    return topleft + (ld)x / window->get_width() * (topright - topleft) +
            (ld)y / window->get_height() * (buttomleft - topleft);
}

Color Render::get_color_xy(int x, int y)
{
    // луч, исходящий из точки наблюдения и проходящий
    // через текущюю точку экрана, а также его длина
    Point3D xy = to_point(x, y);

    return get_color_point(xy, xy - viewpoint, depth);
}

Color Render::get_color_point(Point3D p, Point3D v, int d)
{
    // проверяем, не глубоко ли опустилась рекурсия
    if(d < 0) {
        return Color{0, 0, 0};
    }
    Point3D intersection;
    Shape *object;

    // проверяем существование пересечения
    if(ray_trace(p, v, &intersection, &object)) {
        // данные о материале объекта
        const Material *obj_mat = object->get_material(intersection);
        int illum = object->get_illum();

        // итоговый цвет
        Color color(0, 0, 0);

        // вычисляем цвет в зависимости от установленной модели отражения
        if(illum == 0) {
            // цвет ни от чего не зависит
            color = obj_mat->Kd;
        } else {
            // фоновое освещение
            color = obj_mat->Ka ^ scene->backlight;

            // единичный вектор в точку наблюдения
            Point3D view_vector = -1.0 * v.unit();

            // считаем составляющую от первичных источников
            color = color + scan_lights(intersection, view_vector, object);

            // считаем составляющие от вторичных источников
            if(illum > 2) {
                // отраженный луч наблюдения
                Point3D reflected = object->reflected_ray(v, intersection);

                // ищем рекурсивно дополнительный цвет
                Color Ir = get_color_point(intersection + eps * reflected, reflected, d - 1);
                color = color + (obj_mat->Ks ^ Ir);
            }

            // считаем составляющие от преломления
            if(illum == 6) {
                // преломленный луч наблюдения
                Point3D refracted = object->refracted_ray(v, intersection);

                // ищем рекурсивно дополнительный цвет
                Color It = get_color_point(intersection + eps * refracted, refracted, d - 1);
                color = color + ((1.0 - obj_mat->Ks) ^ obj_mat->Tf ^ It);
            }
        }
        return color;
    } else {
        // цвет по-умолчанию, на бесконечности
        return scene->backgroud;
    }
}

bool Render::ray_trace(Point3D p, Point3D v, Point3D *nearest_intersection, Shape **object)
{
    return tree.traverse(p, v, nearest_intersection, object);
}

bool Render::is_reachable(Point3D A, Point3D B)
{
    Shape *object;
    Point3D intersection;
    // немного отступаем от поверхности в сторону B и запускаем луч
    Point3D p = A + eps * (B - A);
    Point3D v = B - A;
    if(ray_trace(p, v, &intersection, &object)) {
        return false;
    }
    return true;
}

Color Render::scan_lights(Point3D point, Point3D view_vector, Shape *obj)
{
    // материал объекта
    const Material *mt = obj->get_material(point);
    int illum = obj->get_illum();

    // нормаль в точке
    Point3D normal = obj->get_normal(point);

    Color color(0, 0, 0);
    // проходим по всем первичным источникам
    for(Light *light : scene->lights) {
        // проверяем, идет ли отраженный свет к наблюдателю
        if(((view_vector)^normal) *
           ((light->get_position() - point)^normal) >= 0)
        {
            // проверяем, нет ли тени от других объектов
            if(is_reachable(point, light->get_position())) {
                // интенсивность света от источника
                Color inten = light->get_intensity(point);

                // единичный вектор в сторону источника
                Point3D light_vector = (light->get_position() - point).unit();

                // вклад за счет диффузного отражения
                color = color + (mt->Kd ^ inten) * (normal ^ light_vector);

                // вклад за счет прямого отражения
                if(illum >= 2) {
                    // направляющий вектор отраженного луча
                    Point3D reflected = obj->reflected_ray(-1.0 * light_vector, point);

                    // вклад от источника
                    ld coef = powl((std::max(reflected.unit() ^ view_vector, 0.0l)), mt->Ns);
                    color = color + (mt->Ks ^ inten) * coef;
                }
            }
        }
    }
    return color;
}

void Render::set_window(rt::Window *_window)
{
    window = _window;
}

void Render::set_camera(Camera &camera)
{
    viewpoint = camera.get_viewpoint();
    topleft = camera.get_topleft();
    topright = camera.get_topright();
    buttomleft = camera.get_bottomleft();
}
