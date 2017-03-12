//
// Created by ivb on 12.03.17.
//

#include "Render.h"
#include <iostream>
#include <cassert>

Render::Render() {
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

void Render::draw()
{
    assert(window != nullptr);
    assert(scene != nullptr);

    int height = window->get_height();
    int width = window->get_width();

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            Color c = get_color_at(x, y);
            window->set_pixel_at(x, y, c);
        }
    }
}

Point3D Render::to_point(int x, int y)
{
    return topleft + (ld)x / window->get_width() * (topright - topleft) +
            (ld)y / window->get_height() * (buttomleft - topleft);
}

Color Render::get_color_at(int x, int y)
{
    Color c;
    // перебираем объекты сцены
    for(Shape * obj: scene->shapes) {
        // точка пересечения луча и объекта
        Point3D intersection;

        // расстояние до ближайшей точки пересечения
        ld cur_min_len2 = 1e50;

        // луч, исходящий из точки наблюдения и проходящий
        // через текущюю точку экрана
        Line3D ray{viewpoint, to_point(x, y)};
        ld ray_len2 = (ray.B - ray.A).len2();

        // есть ли пересечение объекта с лучом?
        if(obj->ray_intersection(ray, &intersection)) {
            // выбираем самое близкое пересечение, находящееся
            // за экраном
            ld len2 = (viewpoint - intersection).len2();
            if(len2 > ray_len2 && len2 < cur_min_len2) {
                cur_min_len2 = len2;
                c = obj->get_color(intersection);
            }
        }
    }
    return c;
}
