#include <iostream>
#include <SDL/SDL_image.h>
#include "Window.h"
#include "Additional.h"
#include <SDL/SDL.h>

#include "tests.h"

int main()
{
    test_all();
//    IMG_Init(IMG_INIT_JPG);
//
//    SDL_Surface *sfr = IMG_Load("BRAKDISC.jpg");
//
//
//    if(sfr == nullptr) {
//        std::cerr << "Error " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    std::cout << sfr->w << ' ' << sfr->h << ' ' << sfr->pitch << std::endl;
//
//    rt::Window window(sfr->w, sfr->h);
//
//    SDL_LockSurface(sfr);
//
//    for(int y = 0; y < sfr->w; ++y) {
//        for(int x = 0; x < sfr->h; ++x) {
//            Uint8 r, g, b;
//            SDL_GetRGB(*(Uint32*)(sfr->pixels + y * sfr->pitch + 3 * x),
//                       sfr->format,
//                       &r, &g, &b);
//            std::cout << (int)r << ' ' << (int)g << ' ' << (int)b << std::endl;
//            Color color(r, g, b);
//            window.set_pixel_at(x, y, color);
//        }
//    }
//
//    SDL_UnlockSurface(sfr);
//
//    window.show(100, 100);

    return 0;
}