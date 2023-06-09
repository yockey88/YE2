#include "input/keyboard.hpp"

#include "SDL.h"

namespace YE {
namespace input {

    std::map<Key , Keyboard::KeyState> Keyboard::keys{};

    void Keyboard::Initialize() {

        for (int k = 0; k < key_count; k++) {

            keys[(Key)k].curr_state = CurrKeyState::UP;
            keys[(Key)k].prev_state = CurrKeyState::UP;
            keys[(Key)k].frames_held = 0;

        }

    }

    void Keyboard::Update() {

        const Uint8* state = SDL_GetKeyboardState(nullptr);

        for (int k = 0; k < key_count; k++) {

            keys[(Key)k].prev_state = keys[(Key)k].curr_state;

            if (state[k] && keys[(Key)k].frames_held > 15) {

                keys[(Key)k].curr_state = CurrKeyState::HELD;
                keys[(Key)k].frames_held++;

            } else if (state[k] && keys[(Key)k].frames_held <= 15) {

                keys[(Key)k].curr_state = CurrKeyState::PRESSED;
                keys[(Key)k].frames_held++;

            } else if (!state[k]) {

                keys[(Key)k].curr_state = CurrKeyState::UP;
                keys[(Key)k].frames_held = 0;

            }

        }

    }



}
}