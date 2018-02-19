//
// Created by ivb on 07.04.17.
//

#ifndef RAY_TRACING_APPLICATION_H
#define RAY_TRACING_APPLICATION_H

#include <string>

#include "Render.h"
#include "Scene.h"

class Application {
public:
    Application(int argc, char **argv);

    // начать выполнение
    void exec();

private:
    // поток, связанный с rt файлом
    std::ifstream fin;

    // рендер
    Render render;

    // сцена
    Scene scene;

    // ширина экрана
    int win_width;

    // высота экрана
    int win_height;

    // положение наблюдателя
    Point3D viewpoint;

    // углы экрана
    Point3D topleft;
    Point3D bottomleft;
    Point3D topright;

    // разбирает rt фаил и настраивает рендер
    void read_rt();

    // сообщение об формате использования
    void print_usage(const char *prgname);

    // вызываются из read_rt для обработки блоков
    void read_depth();
    void read_rays_number();
    void read_background();
    void read_scene();
    void read_viewport();
    void read_camera();
    void read_window();
    void read_lights();
    void read_lights_backlight();
    void read_lights_reference();
    void read_lights_point();
    void read_geometry();
    void read_sphere();
    void read_triangle();
    void read_quadrangle();
    Appearance* read_geometry_material();
    void read_materials();
    void read_materials_entry();

    // если s не было обработано, вывод в stderr
    inline void ignore(std::string s);
};

#endif //RAY_TRACING_APPLICATION_H
