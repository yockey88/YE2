#include "log.hpp"

#include "parsers/config_parser.hpp"

#include "rendering/SDL2.hpp"
#include "rendering/vertex.hpp"
#include "rendering/shader.hpp"
#include "rendering/frame_buffer.hpp"

using json = nlohmann::json;

namespace YE {
namespace parsing {

	void ConfigParser::PrintToken(Token token) {
		std::string str1 = "Token: " + token.value + " ";
		size_t len1 = str1.size();

		std::string str2 = "| Type: ";
		switch (token.type) {
			case Token::Type::none: str2            += "none";            break;
			case Token::Type::identifier: str2      += "identifier";      break;
			case Token::Type::number: str2          += "number";          break;
			case Token::Type::string: str2          += "string";          break;
			case Token::Type::keyword: str2         += "keyword";         break;
			case Token::Type::op: str2              += "op";              break;
			case Token::Type::func: str2            += "func";            break;
			case Token::Type::obj_param: str2       += "obj_param";       break;
			case Token::Type::obj_param_value: str2 += "obj_param_value"; break;
		}

		std::string str3 = " | Line: " + std::to_string(token.line);
		if (token.line - 10 >= 0) str3 = str3 + " ";
		str3 = str3 + " | Column: " + std::to_string(token.column);

		size_t len2 = str2.size();
		size_t len3 = str3.size();

		int padding  = 39 - static_cast<uint32_t>(len1);
		int padding2 = 25 - static_cast<uint32_t>(len2);

		std::cout << str1;
		for (int i = 0; i < padding; i++) { std::cout << " "; }
		std::cout << str2;
		for (int i = 0; i < padding2; i++) { std::cout << " "; }
		std::cout << str3 << "\n";
	}

	std::vector<Token> ConfigParser::LexTokens(const std::string& source) {
		
		LexerState state{};
		ErrorHandler error_handler{};
		state.stack.push(YE_LexSOF);

		while (!state.stack.empty()) {
			state.stack.top()(source , state , &error_handler);
		}

		return state.tokens;
	}
	
	rendering::SDL2_Config ConfigParser::ParseJsonConfigFile(const std::string& path) {
		rendering::SDL2_Config sdl2{};

		std::ifstream file(path);
		json config_json = json::parse(file);

		std::string title = config_json["window"]["title"].get<std::string>();

		float r , g , b , a;
		r = config_json["window"]["color"]["r"].get<float>();
		g = config_json["window"]["color"]["g"].get<float>();
		b = config_json["window"]["color"]["b"].get<float>();
		a = config_json["window"]["color"]["a"].get<float>();

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
		sdl2.r = r;
		sdl2.g = g;
		sdl2.b = b;
		sdl2.a = a;
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

	rendering::SDL2_Config ConfigParser::ParseYConfigFile(const std::string& path) {

		std::stringstream ss;
		std::string file_str;

		std::ifstream file(path);

		{
			YE_ASSERT(file.is_open() , "Could not open file : {}" , path);
			if (!file.is_open()) return rendering::SDL2_Config{};

			ss << file.rdbuf();
			ss << '\0';
			file_str = ss.str();
		}

		YE_ASSERT(file_str.size() > 0 , "File is empty : {}" , path);
		if (file_str.size() < 2) return rendering::SDL2_Config{};

		rendering::SDL2_Config config{};
		ParseState state{};
		ErrorHandler error_handler{};
		state.tokens = LexTokens(file_str);

		YE_ASSERT(state.tokens.size() > 0 , "Lex Failed");
		if (state.tokens.empty()) return rendering::SDL2_Config{};

		for (const auto& t : state.tokens) {
		    PrintToken(t);
		}

		/**
		 * -> Pass Tokens to Parser/Compiler
		 * -> Pass AST tree or Nodes to Interpreter/Compiler
		 * -> Retrieve Assembly?? Not sure how to do this yet or if this is even correct
		 * -> Somehow store assembly as funcs to call later
		 * -> Call funcs
		*/

		// while (!state.stack.empty()) {



		// }

		config.valid = true;

		return config;
	}

	rendering::SDL2_Config ConfigParser::ParseConfigFile(const std::string& path) {
		std::string extension = path.substr(path.find_last_of(".") + 1);

		if (extension == "json") {
			return ParseJsonConfigFile(path);
		} else if (extension == "yobj") {
			return ParseYConfigFile(path);
		} else {
			YE_ERROR("Invalid config file extension : {}" , extension);
			return rendering::SDL2_Config{};
		}
		
	}

}
}