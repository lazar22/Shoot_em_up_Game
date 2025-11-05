//
// Created by Lazar on 11/1/2025.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#define READ_KEY(button, key) case(key):{\
input.buttons[button].changed = is_down != input.buttons[button].is_down;\
input.buttons[button].is_down = is_down;\
} break;

#define IS_DOWN(button) input.buttons[button].is_down
#define IS_PRESSED(button) (input.buttons[button].is_down && input.buttons[button].changed)
#define IS_RELEASED(button) (!input.buttons[button].is_down && input.buttons[button].changed)

namespace platform
{
    namespace window
    {
        constexpr int WIDTH = 1280;
        constexpr int HEIGHT = 720;

        constexpr auto TITLE{"Chicken"};
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
        typedef struct BUTTON_STATE
        {
            bool is_down;
            bool changed;
        } btn_state_t;


        enum BUTTONS
        {
            UP = 0,
            DOWN,
            LEFT,
            RIGHT,

            W,
            S,
            A,
            D,

            SPACE,

            COUNT,
        };

        typedef struct INPUT
        {
            BUTTON_STATE buttons[COUNT];
        } input_t;
    }

    namespace sprite
    {
        constexpr int SIZE = 16;

        namespace ship
        {
            const auto PATH{"assets/sprites/ships/starter/Starter_Ship.png"};
        }
    }

    namespace player_spec
    {
        constexpr float SPEED = 300.0f;
    }

    namespace bullet
    {
        constexpr int MAX_AMOUNT = 4096;

        constexpr float HEIGHT = 10.0f;
        constexpr float WIDTH = 5.0f;

        constexpr SDL_Color COLOR = {157, 250, 245};

        constexpr float SPEED = 1000.0f;
        constexpr float LIFE_TIME = 1.0f;
    }
}

#endif //PLATFORM_H
