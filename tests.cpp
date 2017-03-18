//
// Created by ivb on 12.03.17.
//

#include "tests.h"
#include "geometry.h"
#include "Render.h"
#include "Additional.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Light.h"
#include "Scene.h"
#include "Window.h"

#include <iostream>

void test_all()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
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
    Sphere s1({0, 0, 2}, 2, {100, 100, 100});
    Sphere s2({30, -60, 0}, 5, {0, 200, 0});
    Light l1({-2, 6, 7}, 40, {0, 100, 255});
    Light l2({20, -50, 20}, 400);
    Triangle t1({0, 12, 0}, {80, -100, 0}, {-80, -100, 0}, {200, 50, 50}, {0, 0, 1});
    Triangle t2({30, -50, 7}, {40, -70, 7}, {20, -70, 7}, {200, 50, 50}, {0, 0, 1});

    Scene sc;
    sc.add_shape(&s1);
    sc.add_shape(&s2);
    sc.add_light(&l1);
    sc.add_light(&l2);
    sc.add_shape(&t1);
    sc.add_shape(&t2);

    sc.backgroud = Color{100, 100, 100};
    sc.backlight = Color(10, 10, 10);

    rt::Window win(600, 600);

    Render render;
    render.set_window(&win, {2, 8, 4}, {2, 8, 0}, {-2, 8, 4});
    render.set_scene(&sc);
    render.set_viewpoint({0, 12, 2});

    render.draw();

    win.show();
}