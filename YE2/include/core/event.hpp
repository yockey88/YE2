#ifndef YE_EVENT_HPP
#define YE_EVENT_HPP

namespace YE {
namespace core {

    class Event {

        public:

            enum class Type {

                NONE = 0 ,
                WINDOW_CLOSE ,
                WINDOW_RESIZE ,
                WINDOW_FOCUS ,
                WINDOW_LOST_FOCUS ,
                WINDOW_MOVED ,

                APP_TICK ,
                APP_UPDATE ,
                APP_RENDER ,

                KEY_PRESSED ,
                KEY_RELEASED ,
                KEY_TYPED ,

                MOUSE_BUTTON_PRESSED ,
                MOUSE_BUTTON_RELEASED ,
                MOUSE_MOVED ,
                MOUSE_SCROLLED

            };

        private:

            Type type;

        public:

            Event(Type type) : type(type) {}

            inline Type GetType() const { return type; }

    };

}
}

#endif YE_EVENT_HPP