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

    Point3D to_point(int x, int y);

    Color get_color_at(int x, int y);
};

#endif //RAY_TRACING_RENDER_H
