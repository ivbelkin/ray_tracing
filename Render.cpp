//
// Created by ivb on 12.03.17.
//

#include "Render.h"
#include <iostream>
#include <cassert>

Render::Render() :
    depth(0)
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

    int height = window->get_height();
    int width = window->get_width();

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            Color c = get_color_xy(x, y);
            window->set_pixel_at(x, y, c);
        }
    }
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
    Line3D ray{xy, 2 * xy - viewpoint};

    return get_color_point(ray, 0);
}

Color Render::get_color_point(Line3D ray, int d)
{
    // проверяем, не глубоко ли опустилась рекурсия
    if(d > depth) {
        return Color{0, 0, 0};
    }
    Point3D intersection;
    Shape *object;

    // проверяем существование пересечения
    if(ray_trace(ray, &intersection, &object)) {
        // собственный цвет объекта
        Color obj_color = object->get_color(intersection);

        // нормаль к объекту в точке падения
        Point3D normal = object->get_normal(intersection);

        // наблюдаемый цвет объекта
        Color color = obj_color ^ scene->backlight;

        // опрашиваем источники света
        for(Light *light : scene->lights) {
            // проверяем, нет ли тени от других объектов
            if(is_reachable(object, intersection, light->get_position())) {
                // цвет от источника
                Color c = light->get_color(intersection, normal);

                // добавляем к уже полученному освещению объекта
                color = color + (obj_color ^ c);
            }
        }
        return color;
    } else {
        // цвет по-умолчанию, на бесконечности
        return scene->backgroud;
    }
}

bool Render::ray_trace(Line3D ray, Point3D *nearest_intersection, Shape **object)
{
    // расстояние до ближайшей точки пересечения
    ld cur_min_len2 = 1e50;

    // флаг существования пересечения
    bool F = false;

    // перебираем объекты сцены
    for(Shape *obj: scene->shapes) {
        // точка пересечения луча и объекта
        Point3D intersection;

        // есть ли пересечение объекта с лучом?
        if(obj->ray_intersection(ray, &intersection)) {
            // выбираем самое близкое пересечение
            ld len2 = (viewpoint - intersection).len2();
            if(len2 < cur_min_len2) {
                // обновляем данные
                cur_min_len2 = len2;
                *nearest_intersection = intersection;
                *object = obj;

                // пересечение уже точно есть
                F = true;
            }
        }
    }
    return F;
}

bool Render::is_reachable(Shape *obj, Point3D A, Point3D B)
{
    Shape *object;
    Point3D intersection;
    if(ray_trace(Line3D{A, B}, &intersection, &object)) {
        return obj == object;
    }
    return true;
}