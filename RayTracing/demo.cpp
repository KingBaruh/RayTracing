#include "SDL.h"
#include <iostream>

using std::cout;
using std::endl;

int main123(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("First SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer Creation Failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    int running = 1;
    SDL_Event event;
    int red = 0, green = 255, blue = 0;
    SDL_Rect r{ 10,10,125,125 };

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_r:
                    red = 255; green = 0; blue = 0;
                    break;
                case SDLK_g:
                    red = 0; green = 255; blue = 0;
                    break;
                case SDLK_b:
                    red = 0; green = 0; blue = 255;
                    break;

                case SDLK_RIGHT:
                    if (r.x + 5 <= 475)
                    {
                        cout << r.x + 5 << endl;
                        r.x += 5;
                    }
                    break;
                
                case SDLK_LEFT:
                    if (r.x - 5 >= 0)
                    {
                        r.x -= 5;
                    }
                    break;
                case SDLK_UP:
                    if (r.y - 5 >= 0)
                    {
                        r.y -= 5;
                    }
                    break;
                case SDLK_DOWN:
                    if (r.y + 5 <= 275)
                    {
                        r.y += 5;
                    }
                    break;

                }
            }
        }

        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer,&r);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // Prevent CPU overload (~60 FPS)
        
        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
