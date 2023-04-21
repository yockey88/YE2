#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "parsing/parser.hpp"

namespace ylang {

    class Compiler {
        bool m_Valid;
        ErrorHandler m_ErrorHandler;
        SpaceInfo m_SpaceInfo;
        Validator m_Validator;

        StmntList LexFile(const std::string& filepath);

        bool BuildProjectspace();
        bool BuildBuildspace();
        bool BuildWorkspace();
        
        bool Build();
        
        public:
            Compiler() {}
            ~Compiler() {}

            bool Compile(const std::string& folderpath);
    };

}

#endif