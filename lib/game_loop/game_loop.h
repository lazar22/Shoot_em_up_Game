//
// Created by Lazar on 11/1/2025.
//

#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

#include <platform.h>
#include <bullet.h>

namespace game
{
    namespace loop
    {
        void init(SDL_Renderer* _renderer, const platform::input::input_t& _input);

        void set_background_color(SDL_Color color);

        void move_player(SDL_FRect& pos, float player_speed, float delta_time);

        void shoot(SDL_FRect player_pos, float delta_time);
    }
}

#endif //GAME_LOOP_H
