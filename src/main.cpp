//
// Created by Lazar on 11/1/2025.
//

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>

#include <sprite_loader.h>
#include <platform.h>

#include "game_loop.h"

static platform::input::input_t input;

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (!TTF_Init())
    {
        SDL_Log("Fail to Init TTF [%s]", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(platform::window::TITLE,
                                          platform::window::WIDTH, platform::window::HEIGHT,
                                          SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP);

    if (SDL_Surface* icon = IMG_Load(platform::sprite::ship::PATH))
    {
        SDL_SetWindowIcon(window, icon);
        SDL_DestroySurface(icon);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    // Persistent player position
    SDL_FRect player_pos{100, 100, platform::sprite::SIZE, platform::sprite::SIZE};

    unsigned long long start_time = SDL_GetPerformanceCounter();
    bool is_running = true;

    while (is_running)
    {
        for (int i = 0; i < platform::input::COUNT; i++)
        {
            input.buttons[i].changed = false;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                is_running = false;
                break;

            case SDL_EVENT_KEY_UP:
            case SDL_EVENT_KEY_DOWN:
                {
                    const unsigned int key = event.key.key;
                    const bool is_down = (event.type == SDL_EVENT_KEY_DOWN);

                    switch (key)
                    {
                        // Alternative CH movement
                    READ_KEY(platform::input::UP, SDLK_UP);
                    READ_KEY(platform::input::DOWN, SDLK_DOWN);
                    READ_KEY(platform::input::LEFT, SDLK_LEFT);
                    READ_KEY(platform::input::RIGHT, SDLK_RIGHT);

                        // Main CH movement
                    READ_KEY(platform::input::W, SDLK_W);
                    READ_KEY(platform::input::S, SDLK_S);
                    READ_KEY(platform::input::A, SDLK_A);
                    READ_KEY(platform::input::D, SDLK_D);


                    READ_KEY(platform::input::SPACE, SDLK_SPACE);
                    }
                }
                break;

            default:
                break;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        const unsigned long long current_time = SDL_GetPerformanceCounter();
        const unsigned long long freq = SDL_GetPerformanceFrequency();
        float delta_time = static_cast<float>(current_time - start_time) / static_cast<float>(freq);
        start_time = current_time;

        if (delta_time > 0.1) { delta_time = 0.1; }

        game::loop::init(renderer, input);
        game::loop::set_background_color({199, 197, 197, 255});

        game::loop::move_player(player_pos, platform::player_spec::SPEED, delta_time);
        game::loop::shoot(player_pos, delta_time);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
