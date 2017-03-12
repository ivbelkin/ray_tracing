//
// Created by ivb on 11.03.17.
//

#ifndef RAY_TRACING_SCREEN_H
#define RAY_TRACING_SCREEN_H

#include "Additional.h"

#include <vector>

namespace rt {

// Окно, в котором будет отрисована рендером сцена
// обертка над XLib
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

private:
    // ширина
    int width;

    // высота
    int height;

    // видеобуфер
    std::vector<Color> vbuf;

    unsigned long convert_color(Color & c);
};

}
#endif //RAY_TRACING_SCREEN_H
