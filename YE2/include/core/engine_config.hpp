#ifndef YE_ENGINE_SETTINGS_HPP
#define YE_ENGINE_SETTINGS_HPP

#include <string>
#include <vector>

namespace YE {
namespace core {

    struct EngineConfiguration {

        uint32_t app_vmajor = 0;
        uint32_t app_vminor = 0;
        uint32_t app_vpatch = 0;
        
        std::string proj_name        = "<NO PROJECT NAME>";
        std::string proj_author      = "<NO AUTHOR NAME>"; 
        std::string proj_script_path = "<NO SCRIPT PATH>";
        std::string proj_res_path    = "<NO RESOURCE PATH>";

    };

}
}

#endif