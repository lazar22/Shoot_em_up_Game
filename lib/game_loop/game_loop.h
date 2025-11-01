//
// Created by Lazar on 11/1/2025.
//

#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

namespace game
{
    namespace game_loop
    {
        void set_background_color(SDL_Renderer* renderer, SDL_Color color);
    }
}

#endif //GAME_LOOP_H
