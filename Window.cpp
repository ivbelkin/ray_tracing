//
// Created by ivb on 11.03.17.
//

#include "Additional.h"
#include "Window.h"

#include <iostream>

#include <X11/Xlib.h>

rt::Window::Window(int _width, int _height)
{
    if(_height > 0 && _height <= 768 &&
       _width > 0 && _width <= 1366)
    {
        height = _height;
        width = _width;
    } else {
        height = 100;
        width = 100;
    }
    vbuf.assign(height * width, Color{0, 0, 0});
}

void rt::Window::set_pixel_at(int x, int y, Color c)
{
    if(x >= 0 && x < width &&
       y >= 0 && y < height)
    {
        vbuf[x + y * width] = c;
    }
}

int rt::Window::get_height()
{
    return height;
}

int rt::Window::get_width()
{
    return width;
}

void rt::Window::show(int x, int y)
{
    // устанавливаем соединение с X сервером
    Display *display = XOpenDisplay(NULL);

    // получаем дескриптор экрана
    int screen_number = XDefaultScreen(display);

    // создаем окно, в котором будет отображена пиксельная карта
    ::Window window = XCreateSimpleWindow(display, XRootWindow(display, screen_number),
                                          x, y, width, height, 0,
                                          XBlackPixel(display, screen_number),
                                          XWhitePixel(display, screen_number));

    // глубина цвета, установленная в системе
    int depth = XDefaultDepth(display, screen_number);

    // создаем пиксельную карту
    Pixmap pixmap = XCreatePixmap(display, window, width, height, depth);

    // выделяем на сервере графический контекст
    XGCValues gcv;
    gcv.foreground = 0xFFFFFF;
    GC gc = XCreateGC(display, window, GCForeground, &gcv);

    // отрисовываем содержание vbuf на пиксельную карту
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            gcv.foreground = convert_color(vbuf[x + width*y]);
            XChangeGC(display, gc, GCForeground, &gcv);
            XDrawPoint(display, pixmap, gc, x, y);
        }
    }

    // выбираем события, которые будет обрабатывать окно
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // выводим окно
    XMapWindow(display, window);

    // здесь будем хранить очередное событие
    XEvent event;

    // обрабатываем события окна
    while(true) {
        XNextEvent(display, &event);
        switch(event.type) {
            case Expose: // перерисовать
                if(event.xexpose.count != 0) {
                    continue;
                }
                XCopyArea(display, pixmap, window, gc,
                          0, 0, height, width, 0, 0);
                break;

            case KeyPress: // завершаем работу по нажатию клавиши
                // освобождаем ресурсы
                XFreeGC(display, gc);
                XFreePixmap(display, pixmap);

                // закрываем соединение
                XCloseDisplay(display);

                return;
        }
    }
}

unsigned long rt::Window::convert_color(Color &c) {
    return (unsigned long)c.blue + ((unsigned long)c.green << 8ul) + ((unsigned long)c.red << 16ul);
}
