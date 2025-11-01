//
// Created by Lazar on 11/1/2025.
//

#include "game_loop.h"


void game::game_loop::set_background_color(SDL_Renderer* renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}
