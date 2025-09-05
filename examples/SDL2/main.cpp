#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <autorelease/AutoRelease.hpp>

int main()
{
    AutoRelease<int, 1> sdl_init(SDL_Init(SDL_INIT_VIDEO), [](const int &) { SDL_Quit(); });

    AutoRelease<bool> img_init(IMG_Init(IMG_INIT_PNG), [](const bool &) { IMG_Quit(); });

    const AutoRelease<SDL_Window *> window(
            SDL_CreateWindow(
                    "SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                    SDL_WINDOW_SHOWN),
            SDL_DestroyWindow);

    const AutoRelease<SDL_Renderer *> renderer(
            SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);

    const AutoRelease<SDL_Texture *> texture(
            IMG_LoadTexture(renderer, "resources/red_square.png"), SDL_DestroyTexture);
    const SDL_Rect dst = {10, 10, 50, 50};

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, nullptr, &dst);

        SDL_RenderPresent(renderer);
    }

    return 0;
}
