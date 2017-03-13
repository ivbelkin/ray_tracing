//
// Created by ivb on 11.03.17.
//

#include "Additional.h"
#include "Window.h"

#include <iostream>
#include <X11/Xlib.h>

rt::Window::Window(int _width, int _height)
{
    // устанавливаем соединение с X сервером
    display = XOpenDisplay(NULL);

    // получаем дескриптор экрана
    screen = XDefaultScreen(display);

    // создаем окно указанной ширины и высоты
    create_window(_width, _height);

    // память для XImage
    char *data = new char[width * height * 4];

    // создаем графический контекст
    gc = XDefaultGC(display, screen);

    // параметры изображения
    Visual *visual = XDefaultVisual(display, screen);

    // устанавливаем глубину цвета = 24
    int depth = 24;
    visual->bits_per_rgb = depth;

    // создаем изображение
    image = XCreateImage(display, visual, depth,
                         ZPixmap, 0, data,
                         width, height, 8, 0);

    // необходимо для корректной работы Xlib с изображением
    XInitImage(image);
}

void rt::Window::set_pixel_at(int x, int y, Color c)
{
    if(x >= 0 && x < width &&
       y >= 0 && y < height)
    {
        image->data[4 * x + 4 * width * y + 2] = c.red();
        image->data[4 * x + 4 * width * y + 1] = c.green();
        image->data[4 * x + 4 * width * y] = c.blue();
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
    // выбираем события, которые будет обрабатывать окно
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // выводим окно
    XMapWindow(display, window);

    // здесь будем хранить очередное событие
    XEvent event;

    // обрабатываем события окна
    while(true) {
        // получаем следующее событие
        XNextEvent(display, &event);

        switch(event.type) {
            case Expose: // перерисовываем
                if(event.xexpose.count != 0) {
                    continue;
                }
                XPutImage(display, window, gc, image,
                          0, 0, 0, 0, width, height);
                break;

            case KeyPress: // скрываем окно по нажатию клавиши
                XUnmapWindow(display, window);
                return;
        }
    }
}

void rt::Window::create_window(int _width, int _height)
{
    // максимально допустимые размеры изображения
    int max_width = XDisplayWidth(display, screen);
    int max_height = XDisplayHeight(display, screen);

    if(_height > 0 && _height <= max_height &&
       _width > 0 && _width <= max_width)
    {
        height = _height;
        width = _width;
    } else {
        height = 100;
        width = 100;
    }

    // создаем окно
    window = XCreateSimpleWindow(display, XRootWindow(display, screen),
                                 0, 0, width, height, 1,
                                 XBlackPixel(display, screen),
                                 XWhitePixel(display, screen));
}

rt::Window::~Window()
{
    // удаляем окно
    XDestroyWindow(display, window);

    // удаляем изображение
    image->f.destroy_image(image);

    // закрываем соединение с X сервером
    XCloseDisplay(display);
}
