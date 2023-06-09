#ifndef YE_MOUSE_HPP
#define YE_MOUSE_HPP

#include <map>

namespace YE {
namespace input {

    enum class MouseButton : uint16_t;

    class Mouse {

        public:

            enum class CurrMouseState {

                PRESSED = 0 ,
                HELD    = 1 ,
                UP      = 2     

            };

            struct MouseState {

                CurrMouseState curr_state = CurrMouseState::UP;
                CurrMouseState prev_state = CurrMouseState::UP;

                uint32_t frames_held = 0;

            };

        private:

            constexpr static const uint32_t mouse_button_count = 5;

            static int mouse_x , last_mouse_x;
            static int mouse_y , last_mouse_y;

            static bool mouse_in_window;

            static std::map<MouseButton , MouseState> mouse_buttons;

        public:

            static void Initialize();
            static void Update();   

            inline static int X() { return mouse_x; }
            inline static int Y() { return mouse_y; }

            inline static int DX() { return (mouse_x - last_mouse_x); }
            inline static int DY() { return (mouse_y - last_mouse_y); }

            inline static bool InWindow() { return mouse_in_window; }
            
            inline static bool IsButtonPressed(MouseButton button) { return (mouse_buttons[button].curr_state == CurrMouseState::PRESSED); }
            inline static bool IsButtonHeld(MouseButton button) { return (mouse_buttons[button].curr_state == CurrMouseState::HELD); }
            inline static bool IsButtonReleased(MouseButton button) { return (mouse_buttons[button].curr_state == CurrMouseState::UP); }

    };

    enum class MouseButton : uint16_t {

        YE_MOUSE_FIRST = 1 ,
        YE_MOUSE_LEFT = YE_MOUSE_FIRST ,
        YE_MOUSE_MIDDLE = 2 ,
        YE_MOUSE_RIGHT = 3 ,
        YE_MOUSE_X1 = 4 ,
        YE_MOUSE_X2 = 5 ,
        YE_MOUSE_LAST = 5


    };

}
}

#endif