#include "temp_testing/TestMeshes.hpp"

extern "C" {

    void asm_func(void);

}

int main() {

    YE::rendering::SDL2_Config config = YE::ConfigParser::ParseConfigFile("config/config.yobj");

    if (config.valid) {
        std::cout << "config valid" << std::endl;
    }

    /**
     * Search for configuration file
     * Parse Config file
     *  -> Thing I need to know for config file:
     *      -> Window size
     *      -> Window position
     *      -> Window title
     *      -> Window color
     *      -> Window resizable
     *      -> Window render to screen
     * 
    */

    return 0;
}