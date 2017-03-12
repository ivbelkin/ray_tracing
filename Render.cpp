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
    Point3D nearest{1e50, 1e50, 1e50};
    Color c;

    for(Shape * obj: scene->shapes) {
        Point3D intersection;
        Line3D ray{viewpoint, to_point(x, y)};
        if(obj->ray_intersection(ray, &intersection)) {
            if((viewpoint - intersection).len2() < (viewpoint - nearest).len2()) {
                nearest = intersection;
                c = obj->get_color(intersection);
            }
        }
    }
    return c;
}
