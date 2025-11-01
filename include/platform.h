//
// Created by Lazar on 11/1/2025.
//

#ifndef PLATFORM_H
#define PLATFORM_H

namespace platform
{
    namespace window
    {
        constexpr int WIDTH = 1280;
        constexpr int HEIGHT = 720;
    }

    namespace audio
    {
        constexpr int FREQUENCY = 44100;
        constexpr int BITS = 16;
        constexpr int CHANNELS = 2;
    }

    namespace graphics
    {
        constexpr int FPS = 60;
    }

    namespace input
    {
        enum
        {
            UP = 0,
            DOWN,
            LEFT,
            RIGHT,
        };
    }

    namespace sprite
    {
        constexpr int SIZE = 16;

        namespace ship
        {
            const auto PATH{"assets/sprites/ships/starter/Starter_Ship.png"};
        }
    }
}

#endif //PLATFORM_H
