//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_SCREEN_H
#define RAY_TRACING_SCREEN_H

#include "Additional.h"

#include <vector>
#include <X11/Xlib.h>

namespace rt {

// Окно, в котором будет отрисована рендером сцена
// обертка над Xlib
class Window {
public:
    // экран заданной ширины и высоты
    Window(int _width, int _height);

    // закрасить пиксель
    void set_pixel_at(int x, int y, Color c);

    // высота
    int get_height();

    // ширина
    int get_width();

    // отобразить на мониторе в указанной позиции
    void show(int x = 0, int y = 0);

    ~Window();

private:
    int width; // ширина

    int height; // высота

    // далее расположено то, что необходимо
    // для работы с Xlib

    Display *display; // используемый дисплей

    int screen; // дескриптор экран

    GC gc; // графический контекст

    ::Window window; // окно

    XImage *image; // клиентское представление изображения

    // создать окно Window
    void create_window(int _width, int _height);
};

}
#endif //RAY_TRACING_SCREEN_H
