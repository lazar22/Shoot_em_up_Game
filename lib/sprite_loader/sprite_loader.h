//
// Created by Lazar on 11/1/2025.
//

#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H
#include <SDL3/SDL_render.h>

namespace game
{
    namespace sprite_loader
    {
        void display_sprite(SDL_Renderer* renderer, const char* path, SDL_FRect pos);
    }
}

#endif //SPRITE_LOADER_H
