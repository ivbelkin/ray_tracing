//
// Created by ivb on 07.04.17.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <array>

#include "Application.h"
#include "ObjLoader.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Quadrangle.h"
#include "Material.h"


Application::Application(int argc, char **argv)
{
    if(argc != 2) {
        std::cerr << "Expected name of input file\n";
        print_usage(argv[0]);
        exit(1);
    }
    if(strcmp(argv[1], "-h") == 0) {
        print_usage(argv[0]);
    }
    fin.open(argv[1]);
    if(!fin) {
        std::cerr << "Unable open file \"" << argv[1] << "\"" << std::endl;
        exit(1);
    }
}

void Application::print_usage(const char *prgname)
{
    std::cout << "Usage: " << prgname << " <filename>" << std::endl;
}

void Application::exec()
{
    read_rt();

    rt::Window window(win_width, win_height);

    render.set_viewpoint(viewpoint);

    render.set_window(&window, topleft, bottomleft, topright);

    render.set_scene(&scene);

    render.draw();

    window.show();
}

void Application::read_rt()
{
    std::string cmd;
    while(fin >> cmd) {
        if(cmd[0] == '#') {
            std::getline(fin, cmd, '\n');
        } else if(cmd == "depth") {
            read_depth();
        } else if(cmd == "rays_number") {
            read_rays_number();
        } else if(cmd == "background") {
            read_background();
        } else if(cmd == "scene"){
            read_scene();
        } else if(cmd == "viewport") {
            read_viewport();
        } else if(cmd == "camera") {
            read_camera();
        } else if(cmd == "window") {
            read_window();
        } else if(cmd == "lights") {
            read_lights();
        } else if(cmd == "geometry") {
            read_geometry();
        } else if(cmd == "materials") {
            read_materials();
        } else {
            ignore(cmd);
        }
    }
}

void Application::read_depth()
{
    int d = 0;
    fin >> d;
    render.set_depth(d);
}

void Application::read_rays_number()
{
    int rn = 0;
    fin >> rn;
    render.set_rays_number(rn);
}

void Application::read_scene()
{
    std::string filename;
    fin >> filename;
    ObjLoader loader;
    loader.load(filename, &scene);
}

void Application::read_viewport()
{
    std::string cmd;
    fin >> cmd;
    while(cmd != "endviewport") {
        if(cmd == "origin") {
            fin >> viewpoint;
        } else if(cmd == "topleft") {
            fin >> topleft;
        } else if(cmd == "bottomleft") {
            fin >> bottomleft;
        } else if(cmd == "topright") {
            fin >> topright;
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
}

void Application::read_camera()
{
    std::string cmd;
    ld w, h, d;
    Point3D t, v;
    fin >> cmd;
    while(cmd != "endcamera") {
        if(cmd == "origin") {
            fin >> viewpoint;
        } else if(cmd == "width") {
            fin >> w;
        } else if(cmd == "height") {
            fin >> h;
        } else if(cmd == "distance") {
            fin >> d;
        } else if(cmd == "target") {
            fin >> t;
        } else if(cmd == "vertical") {
            fin >> v;
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
    Camera camera(viewpoint, t, v, d, w, h);
    topleft = camera.get_topleft();
    topright = camera.get_topright();
    bottomleft = camera.get_bottomleft();
}

void Application::read_window()
{
    std::string cmd;
    fin >> cmd;
    while(cmd != "endwindow") {
        if(cmd == "width") {
            fin >> win_width;
        } else if(cmd == "height") {
            fin >> win_height;
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
}

void Application::read_lights()
{
    std::string cmd;
    fin >> cmd;
    while(cmd != "endlights") {
        if(cmd == "reference") {
            read_lights_reference();
        } else if(cmd == "point") {
            read_lights_point();
        } else if(cmd == "backlight") {
            read_lights_backlight();
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
}

void Application::read_lights_reference()
{
    std::string cmd;
    fin >> cmd;
    while(cmd != "endreference") {
        if(cmd == "power") {
            ld power = 0;
            fin >> power;
            Light::set_norm_power(power);
        } else if(cmd == "distance") {
            ld distance;
            fin >> distance;
            Light::set_norm_distance(distance);
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
}

void Application::read_lights_point()
{
    std::string cmd;
    fin >> cmd;
    Point3D p{0, 0, 0};
    ld power = 0;
    Color color(0, 0, 0);
    while(cmd != "endpoint") {
        if(cmd == "coords") {
            fin >> p;
        } else if(cmd == "power") {
            fin >> power;
        } else if(cmd == "color") {
            fin >> color;
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
    scene.add_light(new Light(p, power, color));
}

void Application::ignore(std::string s)
{
    std::cerr << "Ignore: " << s << std::endl;
}

void Application::read_background()
{
    fin >> scene.backgroud;
}

void Application::read_lights_backlight()
{
    fin >> scene.backlight;
}

void Application::read_geometry()
{
    std::string cmd;
    fin >> cmd;
    while(cmd != "endgeometry") {
        if(cmd == "sphere") {
            read_sphere();
        } else if(cmd == "triangle") {
            read_triangle();
        } else if(cmd == "quadrangle") {
            read_quadrangle();
        }
        fin >> cmd;
    }
}

void Application::read_sphere()
{
    std::string cmd;
    fin >> cmd;
    Point3D center{0, 0, 0};
    ld radius = 0.0;
    Appearance *appearance = nullptr;
    while(cmd != "endsphere") {
        if(cmd == "coords") {
            fin >> center;
        } else if(cmd == "radius") {
            fin >> radius;
        } else if(cmd == "material") {
            appearance = read_geometry_material();
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
    Sphere *sphere = new Sphere(center, radius);
    sphere->reset_material(appearance);
    scene.add_shape(sphere);
}

void Application::read_triangle()
{
    std::string cmd;
    fin >> cmd;
    std::array<Point3D, 3> v;
    int i = 0;
    Appearance *appearance = nullptr;
    while(cmd != "endtriangle") {
        if(cmd == "vertex") {
            if(i < 3) {
                fin >> v[i++];
            } else {
                ignore(cmd);
            }
        } else if(cmd == "material") {
            appearance = read_geometry_material();
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
    Triangle *triangle = new Triangle(v[0], v[1], v[2]);
    triangle->reset_material(appearance);
    scene.add_shape(triangle);
}

void Application::read_quadrangle()
{
    std::string cmd;
    fin >> cmd;
    std::array<Point3D, 4> v;
    int i = 0;
    Appearance *appearance = nullptr;
    while(cmd != "endquadrangle") {
        if(cmd == "vertex") {
            if(i < 4) {
                fin >> v[i++];
            } else {
                ignore(cmd);
            }
        } else if(cmd == "material") {
            appearance = read_geometry_material();
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
    Quadrangle *quadrangle = new Quadrangle(v[0], v[1], v[2], v[3]);
    quadrangle->reset_material(appearance);
    scene.add_shape(quadrangle);
}

Appearance *Application::read_geometry_material()
{
    std::string name;
    fin >> name;
    return scene.materials[name];
}

void Application::read_materials()
{
    std::string cmd;
    fin >> cmd;
    while(cmd != "endmaterials") {
        if(cmd == "entry") {
            read_materials_entry();
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
}

void Application::read_materials_entry()
{
    std::string cmd;
    fin >> cmd;
    std::string name;
    Appearance *appearance = new Appearance;
    appearance->base = new Material;
    appearance->illum = 6;
    appearance->base->Ns = 100;
    appearance->map_Kd = nullptr;
    while(cmd != "endentry") {
        if(cmd == "name") {
            fin >> name;
        } else if(cmd == "color") {
            Color c;
            fin >> c;
            appearance->base->Ka = c;
            appearance->base->Kd = c;
        } else if(cmd == "alpha") {
            ld alpha = 0.0;
            fin >> alpha;
            appearance->base->Tf = Color(alpha, alpha, alpha);
        } else if(cmd == "reflect") {
            ld reflect = 0.0;
            fin >> reflect;
            appearance->base->Ks = Color(reflect, reflect, reflect);
        } else if(cmd == "refract") {
            fin >> appearance->Ni;
        } else if (cmd == "illum") {
            fin >> appearance->illum;
        } else {
            ignore(cmd);
        }
        fin >> cmd;
    }
    scene.materials[name] = appearance;
}