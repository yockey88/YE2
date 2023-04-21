#include "parsers/config_parser.hpp"

#include "rendering/SDL2.hpp"
#include "rendering/vertex.hpp"
#include "rendering/shader.hpp"
#include "rendering/frame_buffer.hpp"

using json = nlohmann::json;

namespace YE {

    rendering::SDL2_Config ConfigParser::ParseConfigFile(const std::string& path) {
        
        rendering::SDL2_Config sdl2{};

        std::ifstream file(path);
        json config_json = json::parse(file);

        std::string title = config_json["window"]["title"].get<std::string>();

        float r , g , b , a;
        r = config_json["window"]["color"]["r"].get<float>();
        g = config_json["window"]["color"]["g"].get<float>();
        b = config_json["window"]["color"]["b"].get<float>();
        a = config_json["window"]["color"]["a"].get<float>();
        
        glm::vec4 cc{ r , g , b , a };

        int width = config_json["window"]["size"]["width"].get<int>();
        int height = config_json["window"]["size"]["height"].get<int>();

        int pos_x = config_json["window"]["position"]["x"].get<int>();
        int pos_y = config_json["window"]["position"]["y"].get<int>();

        if (pos_x == 0) pos_x = SDL_WINDOWPOS_CENTERED;
        if (pos_y == 0) pos_y = SDL_WINDOWPOS_CENTERED;

        bool resizable = config_json["window"]["resizable"].get<bool>();
        bool render_to_screen = config_json["window"]["render_to_screen"].get<bool>();
        bool vsync = config_json["window"]["vsync"].get<bool>();

        sdl2.title = title;
        sdl2.config_path = path;
        sdl2.cc = cc;
        sdl2.w = width;
        sdl2.h = height;
        sdl2.x = pos_x;
        sdl2.y = pos_y;
        sdl2.vsync = vsync;
        sdl2.render_to_screen = render_to_screen;

        if (resizable) {
            sdl2.flags |= SDL_WINDOW_RESIZABLE;
        }

        sdl2.valid = true;

        return sdl2;
    }

}