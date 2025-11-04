//
// Created by Lazar on 11/1/2025.
//

#include "game_loop.h"

#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_log.h>
#include <algorithm>

#include "sprite_loader.h"
#include "bullet.h"

static SDL_Renderer* renderer{nullptr};
static platform::input::input_t input;

static bullet_pool bullets{platform::bullet::MAX_AMOUNT};

void game::loop::init(SDL_Renderer* _renderer, const platform::input::input_t& _input)
{
    renderer = _renderer;
    input = _input;
}


void game::loop::set_background_color(const SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void game::loop::move_player(SDL_FRect& pos, const float player_speed,
                             const float delta_time)
{
    float dx = 0.0f;
    float dy = 0.0f;
    float current_speed{player_speed};

    auto any_key = [&](auto... k)
    {
        return (IS_DOWN(k) || ...);
    };

    const bool is_hor = any_key(platform::input::LEFT, platform::input::RIGHT, platform::input::A, platform::input::D);
    const bool is_ver = any_key(platform::input::UP, platform::input::DOWN, platform::input::W, platform::input::S);

    current_speed = is_hor && is_ver ? player_speed * 0.5f : player_speed;

    if (IS_DOWN(platform::input::LEFT) || IS_DOWN(platform::input::A))
    {
        dx -= current_speed;
    }
    if (IS_DOWN(platform::input::RIGHT) || IS_DOWN(platform::input::D))
    {
        dx += current_speed;
    }
    if (IS_DOWN(platform::input::UP) || IS_DOWN(platform::input::W))
    {
        dy -= current_speed;
    }
    if (IS_DOWN(platform::input::DOWN) || IS_DOWN(platform::input::S))
    {
        dy += current_speed;
    }

    SDL_FRect new_pos = pos;
    new_pos.x += dx * delta_time;
    new_pos.y += dy * delta_time;

    new_pos.x = std::clamp(new_pos.x, 0.0f, static_cast<float>(platform::window::WIDTH) - new_pos.w);
    new_pos.y = std::clamp(new_pos.y, 0.0f, static_cast<float>(platform::window::HEIGHT) - new_pos.h);

    pos = new_pos;
    sprite_loader::display_sprite(renderer, platform::sprite::ship::PATH, new_pos);
}

void game::loop::shoot(const SDL_FRect player_pos, const float delta_time)
{
    if (IS_PRESSED(platform::input::SPACE))
    {
        const float bw = 10.0f;
        const float bh = 10.0f;
        const float spawn_x = player_pos.x + (player_pos.w * 0.5f) - (bw * 0.5f);
        const float spawn_y = player_pos.y - bh; // spawn just above the player

        auto handle = bullets.spawn(spawn_x, spawn_y,
                      0.0f, -platform::bullet::SPEED,
                      platform::bullet::LIFE_TIME);
        if (handle == 0)
        {
            SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Bullet pool full; dropping shot");
        }
    }

    bullets.update(delta_time,
                   0.0f, static_cast<float>(platform::window::WIDTH),
                   0.0f, static_cast<float>(platform::window::HEIGHT));

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    bullets.draw([&](const bullet_t& bullet)
    {
        SDL_FRect pos = {bullet.x, bullet.y, 10.0f, 10.0f};
        SDL_RenderFillRect(renderer, &pos);
    });
}




