//
// Created by Lazar on 11/1/2025.
//

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>

#include <sprite_loader.h>
#include <platform.h>

#include "game_loop.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // if (TTF_Init() != 0)
    // {
    //     SDL_Log("Fail to Init TTF");
    //     return 1;
    // }

    SDL_Window* window = SDL_CreateWindow("Chicken",
                                          platform::window::WIDTH, platform::window::HEIGHT,
                                          SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    bool is_running = true;

    while (is_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                is_running = false;
                break;

            default:
                break;
            }
        }

        game::game_loop::set_background_color(renderer, {199, 197, 197, 255});

        game::sprite_loader::display_sprite(renderer,
                                            platform::sprite::ship::PATH,
                                            {100, 100, platform::sprite::SIZE, platform::sprite::SIZE});


        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
