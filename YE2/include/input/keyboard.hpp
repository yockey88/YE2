#ifndef YE_KEYBOARD_HPP
#define YE_KEYBOARD_HPP

#include <map>

namespace YE {
namespace input {

    enum class Key : uint16_t;

    class Keyboard {

        public:

            enum class CurrKeyState {

                PRESSED = 0 ,
                HELD    = 1 ,
                UP      = 2     

            };

            struct KeyState {

                CurrKeyState curr_state = CurrKeyState::UP;
                CurrKeyState prev_state = CurrKeyState::UP;

                uint32_t frames_held = 0;

            };

        private:

            constexpr static const uint32_t key_count = 287;

            static std::map<Key , KeyState> keys;

        public:

            static void Initialize();
            static void Update();   
            
            inline static bool IsKeyPressed(Key key) { return (keys[key].curr_state == CurrKeyState::PRESSED); }
            inline static bool IsKeyHeld(Key key) { return (keys[key].curr_state == CurrKeyState::HELD); }
            inline static bool IsKeyReleased(Key key) { return (keys[key].curr_state == CurrKeyState::UP); }

    };

    enum class Key : uint16_t {

        INVALID_1 = 0 ,
        INVALID_2 = 1 ,
        INVALID_3 = 2 ,
        INVALID_4 = 3 ,

        YE_KEY_A = 4 ,
	    YE_KEY_FIRST = YE_KEY_A ,
        YE_KEY_B = 5 ,
        YE_KEY_C = 6 ,
        YE_KEY_D = 7 ,
        YE_KEY_E = 8 ,
        YE_KEY_F = 9 ,
        YE_KEY_G = 10 ,
        YE_KEY_H = 11 ,
        YE_KEY_I = 12 ,
        YE_KEY_J = 13 ,
        YE_KEY_K = 14 ,
        YE_KEY_L = 15 ,
        YE_KEY_M = 16 ,
        YE_KEY_N = 17 ,
        YE_KEY_O = 18 ,
        YE_KEY_P = 19 ,
        YE_KEY_Q = 20 ,
        YE_KEY_R = 21 ,
        YE_KEY_S = 22 ,
        YE_KEY_T = 23 ,
        YE_KEY_U = 24 ,
        YE_KEY_V = 25 ,
        YE_KEY_W = 26 ,
        YE_KEY_X = 27 ,
        YE_KEY_Y = 28 ,
        YE_KEY_Z = 29 ,
	    YE_KEY_1 = 30 ,
        YE_KEY_2 = 31 ,
        YE_KEY_3 = 32 ,
        YE_KEY_4 = 33 ,
        YE_KEY_5 = 34 ,
        YE_KEY_6 = 35 ,
        YE_KEY_7 = 36 ,
        YE_KEY_8 = 37 ,
        YE_KEY_9 = 38 ,
        YE_KEY_0 = 39 ,
	    YE_KEY_RETURN = 40 ,
        YE_KEY_ESCAPE = 41 ,
        YE_KEY_BACKSPACE = 42 ,
        YE_KEY_TAB = 43 ,
        YE_KEY_SPACE = 44 ,
        YE_KEY_MINUS = 45 ,
        YE_KEY_EQUALS = 46 ,
        YE_KEY_LEFTBRACKET = 47 ,
        YE_KEY_RIGHTBRACKET = 48 ,
        YE_KEY_BACKSLASH = 49 ,
	    YE_KEY_NONUSHASH = 50 ,
	    YE_KEY_SEMICOLON = 51 ,
        YE_KEY_APOSTROPHE = 52 ,
        YE_KEY_GRAVE = 53 ,
	    YE_KEY_COMMA = 54 ,
        YE_KEY_PERIOD = 55 ,
        YE_KEY_SLASH = 56 ,
        YE_KEY_CAPSLOCK = 57 ,
	    YE_KEY_F1 = 58 ,
        YE_KEY_F2 = 59 ,
        YE_KEY_F3 = 60 ,
        YE_KEY_F4 = 61 ,
        YE_KEY_F5 = 62 ,
        YE_KEY_F6 = 63 ,
        YE_KEY_F7 = 64 ,
        YE_KEY_F8 = 65 ,
        YE_KEY_F9 = 66 ,
        YE_KEY_F10 = 67 ,
        YE_KEY_F11 = 68 ,
        YE_KEY_F12 = 69 ,
        YE_KEY_PRINTSCREEN = 70 ,
        YE_KEY_SCROLLLOCK = 71 ,
        YE_KEY_PAUSE = 72 ,
        YE_KEY_INSERT = 73 ,
	    YE_KEY_HOME = 74 ,
        YE_KEY_PAGEUP = 75 ,
        YE_KEY_DELETE = 76 ,
        YE_KEY_END = 77 ,
        YE_KEY_PAGEDOWN = 78 ,
        YE_KEY_RIGHT = 79 ,
        YE_KEY_LEFT = 80 ,
        YE_KEY_DOWN = 81 ,
        YE_KEY_UP = 82 ,
        YE_KEY_NUMLOCKCLEAR = 83 ,
	    YE_KEY_KP_DIVIDE = 84 ,
        YE_KEY_KP_MULTIPLY = 85 ,
        YE_KEY_KP_MINUS = 86 ,
        YE_KEY_KP_PLUS = 87 ,
        YE_KEY_KP_ENTER = 88 ,
        YE_KEY_KP_1 = 89 ,
        YE_KEY_KP_2 = 90 ,
        YE_KEY_KP_3 = 91 ,
        YE_KEY_KP_4 = 92 ,
        YE_KEY_KP_5 = 93 ,
        YE_KEY_KP_6 = 94 ,
        YE_KEY_KP_7 = 95 ,
        YE_KEY_KP_8 = 96 ,
        YE_KEY_KP_9 = 97 ,
        YE_KEY_KP_0 = 98 ,
        YE_KEY_KP_PERIOD = 99 ,
        YE_KEY_NONUSBACKSLASH = 100 ,
	    YE_KEY_APPLICATION = 101 ,
	    YE_KEY_POWER = 102 ,
	    YE_KEY_KP_EQUALS = 103 ,
        YE_KEY_F13 = 104 ,
        YE_KEY_F14 = 105 ,
        YE_KEY_F15 = 106 ,
        YE_KEY_F16 = 107 ,
        YE_KEY_F17 = 108 ,
        YE_KEY_F18 = 109 ,
        YE_KEY_F19 = 110 ,
        YE_KEY_F20 = 111 ,
        YE_KEY_F21 = 112 ,
        YE_KEY_F22 = 113 ,
        YE_KEY_F23 = 114 ,
        YE_KEY_F24 = 115 ,
        YE_KEY_EXECUTE = 116 ,
        YE_KEY_HELP = 117 ,
        YE_KEY_MENU = 118 ,
        YE_KEY_SELECT = 119 ,
        YE_KEY_STOP = 120 ,
        YE_KEY_AGAIN = 121 ,   /**< redo */
        YE_KEY_UNDO = 122 ,
        YE_KEY_CUT = 123 ,
        YE_KEY_COPY = 124 ,
        YE_KEY_PASTE = 125 ,
        YE_KEY_FIND = 126 ,
        YE_KEY_MUTE = 127 ,
        YE_KEY_VOLUMEUP = 128 ,
        YE_KEY_VOLUMEDOWN = 129 ,
	    YE_KEY_KP_COMMA = 133 ,
        YE_KEY_KP_EQUALSAS400 = 134 ,
	    YE_KEY_INTERNATIONAL1 = 135 ,
	    YE_KEY_INTERNATIONAL2 = 136 ,
        YE_KEY_INTERNATIONAL3 = 137 ,
	    YE_KEY_INTERNATIONAL4 = 138 ,
        YE_KEY_INTERNATIONAL5 = 139 ,
        YE_KEY_INTERNATIONAL6 = 140 ,
        YE_KEY_INTERNATIONAL7 = 141 ,
        YE_KEY_INTERNATIONAL8 = 142 ,
        YE_KEY_INTERNATIONAL9 = 143 ,
        YE_KEY_LANG1 = 144 ,
	    YE_KEY_LANG2 = 145 ,
	    YE_KEY_LANG3 = 146 ,
        YE_KEY_LANG4 = 147 ,
        YE_KEY_LANG5 = 148 ,
        YE_KEY_LANG6 = 149 ,
        YE_KEY_LANG7 = 150 ,
        YE_KEY_LANG8 = 151 ,
        YE_KEY_LANG9 = 152 ,
	    YE_KEY_ALTERASE = 153 , /**< Erase-Eaze */
        YE_KEY_SYSREQ = 154 ,
        YE_KEY_CANCEL = 155 ,
        YE_KEY_CLEAR = 156 ,
        YE_KEY_PRIOR = 157 ,
        YE_KEY_RETURN2 = 158 ,
        YE_KEY_SEPARATOR = 159 ,
        YE_KEY_OUT = 160 ,
        YE_KEY_OPER = 161 ,
        YE_KEY_CLEARAGAIN = 162 ,
        YE_KEY_CRSEL = 163 ,
	    YE_KEY_EXSEL = 164 ,
        YE_KEY_KP_00 = 176 ,
        YE_KEY_KP_000 = 177 ,
        YE_KEY_THOUSANDSSEPARATOR = 178 ,
        YE_KEY_DECIMALSEPARATOR = 179 ,
        YE_KEY_CURRENCYUNIT = 180 ,
        YE_KEY_CURRENCYSUBUNIT = 181 ,
        YE_KEY_KP_LEFTPAREN = 182 ,
        YE_KEY_KP_RIGHTPAREN = 183 ,
        YE_KEY_KP_LEFTBRACE = 184 ,
        YE_KEY_KP_RIGHTBRACE = 185 ,
        YE_KEY_KP_TAB = 186 ,
        YE_KEY_KP_BACKSPACE = 187 ,
        YE_KEY_KP_A = 188 ,
        YE_KEY_KP_B = 189 ,
        YE_KEY_KP_C = 190 ,
        YE_KEY_KP_D = 191 ,
        YE_KEY_KP_E = 192 ,
        YE_KEY_KP_F = 193 ,
        YE_KEY_KP_XOR = 194 ,
        YE_KEY_KP_POWER = 195 ,
        YE_KEY_KP_PERCENT = 196 ,
        YE_KEY_KP_LESS = 197 ,
        YE_KEY_KP_GREATER = 198 ,
        YE_KEY_KP_AMPERSAND = 199 ,
        YE_KEY_KP_DBLAMPERSAND = 200 ,
        YE_KEY_KP_VERTICALBAR = 201 ,
        YE_KEY_KP_DBLVERTICALBAR = 202 ,
        YE_KEY_KP_COLON = 203 ,
        YE_KEY_KP_HASH = 204 ,
        YE_KEY_KP_SPACE = 205 ,
        YE_KEY_KP_AT = 206 ,
        YE_KEY_KP_EXCLAM = 207 ,
        YE_KEY_KP_MEMSTORE = 208 ,
        YE_KEY_KP_MEMRECALL = 209 ,
        YE_KEY_KP_MEMCLEAR = 210 ,
        YE_KEY_KP_MEMADD = 211 ,
        YE_KEY_KP_MEMSUBTRACT = 212 ,
        YE_KEY_KP_MEMMULTIPLY = 213 ,
        YE_KEY_KP_MEMDIVIDE = 214 ,
        YE_KEY_KP_PLUSMINUS = 215 ,
        YE_KEY_KP_CLEAR = 216 ,
        YE_KEY_KP_CLEARENTRY = 217 ,
        YE_KEY_KP_BINARY = 218 ,
        YE_KEY_KP_OCTAL = 219 ,
        YE_KEY_KP_DECIMAL = 220 ,
        YE_KEY_KP_HEXADECIMAL = 221 ,
        YE_KEY_LCTRL = 224 ,
        YE_KEY_LSHIFT = 225 ,
        YE_KEY_LALT = 226 , /**< alt, option */
        YE_KEY_LGUI = 227 , /**< windows, command (apple), meta */
        YE_KEY_RCTRL = 228 ,
        YE_KEY_RSHIFT = 229 ,
        YE_KEY_RALT = 230 , /**< alt gr, option */
        YE_KEY_RGUI = 231 , /**< windows, command (apple), meta */
        YE_KEY_MODE = 257 ,
	    YE_KEY_AUDIONEXT = 258 ,
        YE_KEY_AUDIOPREV = 259 ,
        YE_KEY_AUDIOSTOP = 260 ,
        YE_KEY_AUDIOPLAY = 261 ,
        YE_KEY_AUDIOMUTE = 262 ,
        YE_KEY_MEDIASELECT = 263 ,
        YE_KEY_WWW = 264 ,
        YE_KEY_MAIL = 265 ,
        YE_KEY_CALCULATOR = 266 ,
        YE_KEY_COMPUTER = 267 ,
        YE_KEY_AC_SEARCH = 268 ,
        YE_KEY_AC_HOME = 269 ,
        YE_KEY_AC_BACK = 270 ,
        YE_KEY_AC_FORWARD = 271 ,
        YE_KEY_AC_STOP = 272 ,
        YE_KEY_AC_REFRESH = 273 ,
        YE_KEY_AC_BOOKMARKS = 274 ,
	    YE_KEY_BRIGHTNESSDOWN = 275 ,
        YE_KEY_BRIGHTNESSUP = 276 ,
        YE_KEY_DISPLAYSWITCH = 277,  
        YE_KEY_KBDILLUMTOGGLE = 278 ,
        YE_KEY_KBDILLUMDOWN = 279,
        YE_KEY_KBDILLUMUP = 280 ,
        YE_KEY_EJECT = 281 ,
        YE_KEY_SLEEP = 282 ,
        YE_KEY_APP1 = 283 ,
        YE_KEY_APP2 = 284 ,
	    YE_KEY_AUDIOREWIND = 285 ,
        YE_KEY_AUDIOFASTFORWARD = 286

    };

}
}

#endif