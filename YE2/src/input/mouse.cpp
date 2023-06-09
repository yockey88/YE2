#include "input/mouse.hpp"

#include "SDL.h"

namespace YE {
namespace input {

    int Mouse::mouse_x = 0;
    int Mouse::mouse_y = 0;

    int Mouse::last_mouse_x = 0;
    int Mouse::last_mouse_y = 0;

    bool Mouse::mouse_in_window = false;

    std::map<MouseButton , Mouse::MouseState> Mouse::mouse_buttons{};

    void Mouse::Initialize() {

        for (int b = 0; b < mouse_button_count; b++) {

            mouse_buttons[(MouseButton)b].curr_state = CurrMouseState::UP;
            mouse_buttons[(MouseButton)b].prev_state = CurrMouseState::UP;
            mouse_buttons[(MouseButton)b].frames_held = 0;

        }

    }

    void Mouse::Update() {

        last_mouse_x = mouse_x;
        last_mouse_y = mouse_y;

        SDL_GetMouseState(&mouse_x , &mouse_y);

        SDL_Window* window = SDL_GetMouseFocus();

        mouse_in_window = ((window == nullptr) ? false : true);

        for (int b = 0; b < mouse_button_count; b++) {

            mouse_buttons[(MouseButton)b].prev_state = mouse_buttons[(MouseButton)b].curr_state;

            if (SDL_GetMouseState(nullptr , nullptr) & SDL_BUTTON(b) && mouse_buttons[(MouseButton)b].curr_state > 15) {

                mouse_buttons[(MouseButton)b].curr_state = CurrMouseState::HELD;
                mouse_buttons[(MouseButton)b].frames_held++;

            } else if (SDL_GetMouseState(nullptr , nullptr) & SDL_BUTTON(b) && mouse_buttons[(MouseButton)b].frames_held <= 15) {

                mouse_buttons[(MouseButton)b].curr_state = CurrMouseState::PRESSED;
                mouse_buttons[(MouseButton)b].frames_held++;

            } else if (!(SDL_GetMouseState(nullptr , nullptr) & SDL_BUTTON(b))) {

                mouse_buttons[(MouseButton)b].curr_state = CurrMouseState::UP;
                mouse_buttons[(MouseButton)b].frames_held = 0;

            }

        }

    }

}
}