//
// Created by Lazar on 11/3/2025.
//

#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <cstdint>
#include <limits>

typedef struct BULLET
{
    float x{};
    float y{};

    float vx{};
    float vy{};

    float life_time{};

    bool is_active{false};

    uint32_t handle{};
} bullet_t;

class bullet_pool
{
    std::vector<bullet_t> bullets;
    std::vector<uint32_t> generations;
    std::vector<uint32_t> free_list;

public:
    using Handle = uint32_t;

    static constexpr uint32_t K_INDEX_BITS = 20;
    static constexpr uint32_t K_INDEX_MASK = (1U << K_INDEX_BITS) - 1U;
    static constexpr uint32_t K_GENERATION_SHIFT = K_INDEX_BITS;

    explicit bullet_pool(size_t _size) : bullets(_size), generations(static_cast<size_t>(_size), 1u), free_list()
    {
        free_list.reserve(_size);
        for (size_t i = _size; i-- > 0; )
        {
            free_list.push_back(static_cast<uint32_t>(i));
        }
    }

    Handle spawn(const float x, const float y, const float vx, const float vy, const float life_time)
    {
        if (free_list.empty())
        {
            return 0;
        }

        const uint32_t index = free_list.back();
        free_list.pop_back();

        bullet_t& bullet = bullets[index];
        bullet = {
            x,
            y,
            vx,
            vy,
            life_time,
            true,
        };

        const uint32_t generation = generations[index];
        const Handle handle = make_handle(index, generation);
        bullet.handle = handle;

        return handle;
    }

    bullet_t* get(const Handle handle)
    {
        const uint32_t index = index_of(handle);

        if (index >= bullets.size())
        {
            return nullptr;
        }

        if (generations[index] != generation_of(handle))
        {
            return nullptr;
        }

        bullet_t& bullet = bullets[index];

        return bullet.is_active ? &bullet : nullptr;
    }

    void destroy(const Handle handle)
    {
        if (bullet_t* bullet = get(handle))
        {
            kill_at(index_of(handle));
        }
    }

    void update(const float delta_time,
                const float world_min_x, const float world_max_x,
                const float world_min_y, const float world_max_y)
    {
        for (uint32_t i = 0; i < bullets.size(); i++)
        {
            bullet_t& bullet = bullets[i];
            if (!bullet.is_active) continue;

            bullet.x += bullet.vx * delta_time;
            bullet.y += bullet.vy * delta_time;
            bullet.life_time -= delta_time;

            if (bullet.life_time <= 0.0f ||
                bullet.x < world_min_x || bullet.x > world_max_x ||
                bullet.y < world_min_y || bullet.y > world_max_y)
            {
                kill_at(i);
            }
        }
    }

    template <typename T>
    void draw(T&& _draw) const
    {
        for (const bullet_t& bullet : bullets)
        {
            if (!bullet.is_active)
            {
                continue;
            }

            _draw(bullet);
        }
    }

    [[nodiscard]] size_t capacity() const
    {
        return bullets.size();
    }

private:
    static Handle make_handle(const uint32_t index, const uint32_t generation)
    {
        return (generation << K_GENERATION_SHIFT) | (index & K_INDEX_MASK);
    }

    static uint32_t index_of(const Handle handle)
    {
        return handle & K_INDEX_MASK;
    }

    static uint32_t generation_of(const Handle handle)
    {
        return handle >> K_GENERATION_SHIFT;
    }

    void kill_at(const uint32_t index)
    {
        bullet_t& bullet = bullets[index];

        if (!bullet.is_active)
        {
            return;
        }

        bullet.is_active = false;
        uint32_t& generation = generations[index];

        generation = (generation == std::numeric_limits<uint32_t>::max()) ? 1 : (generation + 1);
        free_list.push_back(index);
    }
};

#endif //BULLET_H
