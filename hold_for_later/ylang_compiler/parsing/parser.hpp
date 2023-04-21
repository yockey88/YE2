#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST.hpp"

namespace ylang {

    enum class ProjectType {
        executable , library ,

        error
    };

    enum class ProjectConfig {
        debug , release , 

        error
    };

    enum class SpaceType {
        projectspace , buildspace , workspace ,

        error
    };

    struct Project {
        ProjectType type = ProjectType::error;
        ProjectConfig config = ProjectConfig::error;
        
        int v_major = 0;
        int v_minor = 0;
        int v_patch = 0;
        std::string name = "[< BLANK >]";
        std::string description = "[< BLANK >]";
        std::string author = "[< BLANK >]";
        std::string root_dir = "[< BLANK >]";
        std::string src_dir = "[< BLANK >]";
        std::string build_dir = "[< BLANK >]";

        std::vector<std::string> filepaths;
        std::vector<std::string> link_names;
        /*TODO :==> Add more project info here
            - license
            - etc...
        */
    };

    struct BuildInfo {
        int v_major = 0;
        int v_minor = 0;
        int v_patch = 0;
        std::string name = "[< BLANK >]";
        std::string description = "[< BLANK >]";
        std::string author = "[< BLANK >]";
        std::string directory = "[< BLANK >]";
        std::vector<Project> projects;
    };

    struct SpaceInfo {
        SpaceType type = SpaceType::error;

        int v_major = 0;
        int v_minor = 0;
        int v_patch = 0;
        std::string name = "[< BLANK >]";
        std::string description = "[< BLANK >]";
        std::string author = "[< BLANK >]";
        std::string directory = "[< BLANK >]";
        std::string main_build_obj_path = "[< BLANK >]";

        std::vector<BuildInfo> builds{};
        StmntList final_compile_info{};
    };

    struct ParserStateData;

    struct ASTConstructionData {
        SpaceInfo build_data{};
        /* TODO :==>
            - curr tree node
            - curr tree node parent
            - curr tree node child
            - curr tree node sibling <?>
            - curr tree node depth <?>
            - curr tree node index <?>
            - curr tree node type <?>
        */ 
    };

}

namespace ylang {

    class Parser {
        public:
            Parser();
            ~Parser() {}
    };

}

#endif