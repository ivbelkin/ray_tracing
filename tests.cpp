//
// Created by ivb on 12.03.17.
//

#include "tests.h"
#include "geometry.h"
#include "Render.h"
#include "Color.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Light.h"
#include "Scene.h"
#include "Window.h"
#include "ObjLoader.h"
#include "Camera.h"

#include <iostream>

void test_all()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}

void test1()
{
    Point3D A1{0, 0, 0};
    Point3D B1{3, 0, 0};
    Point3D C1{-2, 3, 0};
    Color color1(0, 0, 255);
    Triangle triangle1(A1, B1, C1, color1);

    Point3D A2{0, 0, 0};
    Point3D B2{-2, -3, 0};
    Point3D C2{3, -0, 0};
    Color color2(255, 0, 0);
    Triangle triangle2(A2, B2, C2, color2);

    Point3D A3{0, 0, 0};
    Point3D B3{-2, 3, 0};
    Point3D C3{-2, -3, 0};
    Color color3(0, 255, 0);
    Triangle triangle3(A3, B3, C3, color3);

    Point3D tl{-1, -1, 4};
    Point3D bl{1, -1, 4};
    Point3D tr{-1, 1, 4};

    Scene sc;
    sc.add_shape(&triangle1);
    sc.add_shape(&triangle2);
    sc.add_shape(&triangle3);

    sc.backgroud = Color{50, 50, 50};
    sc.backlight = Color(100, 100, 100);

    Point3D point{0, 0, 5};

    rt::Window win(300, 300);

    Render render;

    render.set_window(&win, tl, bl, tr);
    render.set_scene(&sc);
    render.set_viewpoint(point);

    render.draw();

    std::cout << "Press any key to close the window." << std::endl;

    win.show();
}

void test2()
{
    Triangle t1({-1, 2, 0}, {4, 0, 0}, {-1, -2, 0}, Color(255, 0, 0));

    Triangle t2({1, 2, 1}, {1, -2, 1}, {-4, 0, 1}, Color(0, 255, 0));

    Scene sc;
    sc.add_shape(&t1);
    sc.add_shape(&t2);

    sc.backgroud = Color{50, 50, 50};
    sc.backlight = Color(100, 100, 100);

    rt::Window win(300, 300);

    Render render;
    render.set_window(&win, {-5, 5, 4}, {-5, -5, 4}, {5, 5, 4});
    render.set_scene(&sc);
    render.set_viewpoint({0, 0, 10});

    render.draw();

    win.show();
}

void test3()
{
    Triangle t1({-2, 2, -1}, {3, 0, 1}, {-2, -2, -1}, Color(255, 0, 0));

    Triangle t2({1, 2, -1}, {1, -2, -1}, {-4, 0, 2}, Color(0, 255, 0));

    Triangle t3({-4, 2, -1}, {1, 0, 1}, {-4, -2, -1}, Color(0, 0, 255));

    Scene sc;
    sc.add_shape(&t1);
    sc.add_shape(&t2);
    sc.add_shape(&t3);

    sc.backgroud = Color{50, 50, 50};
    sc.backlight = Color(100, 100, 100);

    rt::Window win(300, 300);

    Render render;
    render.set_window(&win, {-5, 5, 4}, {-5, -5, 4}, {5, 5, 4});
    render.set_scene(&sc);
    render.set_viewpoint({0, 0, 10});

    render.draw();

    win.show();
}

void test4()
{
    Triangle t1({-2, 2, 0}, {3, 0, 0}, {-2, -2, 0}, Color(255, 0, 0));

    Triangle t2({1, 2, 16}, {1, -2, 16}, {-4, 0, 16}, Color(0, 255, 0));

    Scene sc;
    sc.add_shape(&t1);
    sc.add_shape(&t2);

    sc.backgroud = Color{50, 50, 50};
    sc.backlight = Color(100, 100, 100);

    rt::Window win(300, 300);

    Render render;
    render.set_window(&win, {-5, 5, 4}, {-5, -5, 4}, {5, 5, 4});
    render.set_scene(&sc);
    render.set_viewpoint({0, 0, 10});

    render.draw();

    win.show();
}

void test5()
{
    Sphere s1({0, 0, 1.4}, 3, Color(255, 0, 0));
    Triangle t1({3, 2, 3.5}, {3, -2, 3.5}, {-4, 0, 3.5}, Color(0, 255, 0));
    Triangle t2({-4, 2, 0}, {-4, -2, 0}, {5, 0, 0}, Color(0, 0, 255));

    Scene sc;

    sc.add_shape(&s1);
    sc.add_shape(&t1);
    sc.add_shape(&t2);

    sc.backgroud = Color{50, 50, 50};
    sc.backlight = Color(100, 100, 100);

    rt::Window win(300, 300);

    Render render;
    render.set_window(&win, {-5, 5, 4}, {-5, -5, 4}, {5, 5, 4});
    render.set_scene(&sc);
    render.set_viewpoint({0, 0, 10});

    render.draw();

    win.show();
}

void test6()
{
    Sphere s1({0, 0, 2}, 2, Color(100, 50, 50));
    Sphere s2({30, -60, 0}, 5, Color(0, 200, 0));
    Light l1({-2, 6, 7}, 50, Color(100, 100, 100));
    Light l2({20, -40, 20}, 4000);
    Triangle t1({0, 12, 0}, {80, -100, 0}, {-80, -100, 0}, Color(200, 50, 50), {0, 0, 1});
    Triangle t2({30, -50, 2}, {20, -70, 7}, {40, -70, 7}, Color(200, 50, 50));

    //Triangle t3({0, 5, 10}, {-5, 5, 0}, {5, 5, 0}, Color(10, 10, 10));

    Scene sc;
    sc.add_shape(&s1);
    sc.add_shape(&s2);
    sc.add_light(&l1);
    sc.add_light(&l2);
    sc.add_shape(&t1);
    sc.add_shape(&t2);
    //sc.add_shape(&t3);

    sc.backgroud = Color(0, 0, 0);
    sc.backlight = Color(100, 100, 100);

    rt::Window win(600, 600);

    Render render;
    render.set_window(&win, {2, 8, 4}, {2, 8, 0}, {-2, 8, 4});
    render.set_scene(&sc);
    render.set_viewpoint({0, 12, 2});

    render.draw();

    win.show();
}

void test7()
{
    Scene sc;

    Light l({20, 10, 30}, 500);

    ObjLoader loader;
    loader.load("model3.obj", &sc); // человек

    sc.backgroud = Color(10, 10, 10);
    sc.backlight = Color(0, 0, 0);

    sc.add_light(&l);

    rt::Window win(600, 600);

    Render render;

    render.set_window(&win);

    Camera camera({1, 10, 30}, {0, 10, 0}, {0, 1, 0}, 5, 4, 4);

    render.set_scene(&sc);
    render.set_camera(camera);

    render.draw();

    win.show();
}

void test8()
{
    Scene sc;

    Light l({30000, 5000, 30000}, 700000000);

    Triangle t1({10, 0, -5}, {10, 0, 5}, {10, 10, 0}, Color(100, 100, 100), {1, 0, 0});

    ObjLoader loader;
    loader.load("BMW_M3_GTR.obj", &sc); // гном

    sc.backgroud = Color(10, 10, 10);
    sc.backlight = Color(0, 0, 0);

    sc.add_light(&l);

    //sc.add_shape(&t1);

    rt::Window win(1000, 500);
    Camera cam({30000, 5000, 30000}, {1000, 3000, 0}, {0, 1, 0}, 12, 5, 2.5);

    Render render;
    render.set_window(&win);
    render.set_scene(&sc);
    render.set_camera(cam);

    render.draw();

    win.show();
}

void test9()
{
    Scene sc;

    Light l({2, 0, 2}, 10);

    ObjLoader loader;
    loader.load("model4.obj", &sc); // гном

    sc.backgroud = Color(10, 10, 10);
    sc.backlight = Color(0, 0, 0);

    sc.add_light(&l);


    rt::Window win(600, 600);
    Camera cam({5, 0.5, 0.5}, {0, 0.5, 0.5}, {0, 0, 1}, 3.99, 2, 2);

    Render render;
    render.set_window(&win);
    render.set_scene(&sc);
    render.set_camera(cam);

    render.draw();

    win.show();
}

void test10()
{
    Scene sc;

    Point3D p{60, 20, -40};

    Light l(p, 100000);

    ObjLoader loader;
    loader.load("model2.obj", &sc); // гном

    sc.backgroud = Color(10, 10, 10);
    sc.backlight = Color(0, 0, 0);

    sc.add_light(&l);


    rt::Window win(600, 600);
    Camera cam(p, {0, 10, 0}, {0, 1, 0}, 2, 2, 2);

    Render render;
    render.set_window(&win);
    render.set_scene(&sc);
    render.set_camera(cam);

    render.draw();

    win.show();
}

void test11()
{
    Scene sc;

    Point3D p{60, 20, -40};

    Light l(p, 100000);

    ObjLoader loader;
    loader.load("model2.obj", &sc); // гном

    sc.backgroud = Color(10, 10, 10);
    sc.backlight = Color(0, 0, 0);

    sc.add_light(&l);


    rt::Window win(600, 600);
    Camera cam(p, {0, 10, 0}, {0, 1, 0}, 2, 2, 2);

    Render render;
    render.set_window(&win);
    render.set_scene(&sc);
    render.set_camera(cam);

    render.draw();

    win.show();
}