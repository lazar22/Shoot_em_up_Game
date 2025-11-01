//
// Created by Lazar on 11/1/2025.
//

#include "sprite_loader.h"

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

void game::sprite_loader::display_sprite(SDL_Renderer* renderer, const char* path, const SDL_FRect pos)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, path);
    SDL_RenderTexture(renderer, texture, nullptr, &pos);
}
