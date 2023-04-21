#include "compiler.hpp"

namespace ylang {
    
    StmntList Compiler::LexFile(const std::string& filepath) {
        Lexer lexer(filepath , &m_ErrorHandler);
        TokenFilter tokenFilter;

        if (!lexer.Lex()) {
            if (!m_ErrorHandler.FlushErrors()) {
                std::cerr << "< Fatal Error >" << std::endl;
            }
            return StmntList{};
        }
        if (!tokenFilter.FilterSrcFile(lexer.GetTokenizationData() , &m_ErrorHandler)) {
            if (!m_ErrorHandler.FlushErrors()) {
                std::cerr << "< Fatal Error >" << std::endl;
            }
            return StmntList{};
        }
        auto [check , final_state] = m_Validator.ValidateSrcFile(tokenFilter , &m_ErrorHandler); 
        if (!check) {
            if (!m_ErrorHandler.FlushErrors()) {
                std::cerr << "< Fatal Error >" << std::endl;
            }
            return StmntList{};
        }

        return tokenFilter.GetStmntList();
    }

    bool Compiler::BuildProjectspace() {
        StmntList stmnts{};

        {
            Lexer lexer(m_SpaceInfo.main_build_obj_path , &m_ErrorHandler);
            TokenFilter tokenFilter;

            if (!lexer.Lex()) {
                if (!m_ErrorHandler.FlushErrors()) {
                    std::cerr << "< Fatal Error >" << std::endl;
                }
                return false;
            }
            if (!tokenFilter.FilterObjFile(lexer.GetTokenizationData() , &m_ErrorHandler)) {
                if (!m_ErrorHandler.FlushErrors()) {
                    std::cerr << "< Fatal Error >" << std::endl;
                }
                return false;
            }

            stmnts = tokenFilter.GetStmntList();
            stmnts.index = 0;

            if (stmnts.statements[0].type != StmntType::sof) {
                std::cerr << "< Fatal Error | Invalid Build Object >" << std::endl;
                return false;
            }
        }

        std::vector<ylang::Token> build_tkns{};

        stmnts.NextStmnt(m_ErrorHandler);
        if (stmnts.GetCurrStmntType() != ylang::StmntType::proj_stmnt) {
            std::cerr << "< Fatal Error | Invalid Build Object >" << std::endl;
            return false;
        } else {
            build_tkns = stmnts.GetCurrStmnt().tokens;
        }

        Project project;
        BuildInfo buildInfo;
        std::vector<std::string> file_names;

        project.root_dir = m_SpaceInfo.directory;

        int tkn_index = 0;
        while (tkn_index < build_tkns.size()) {
            switch (build_tkns[tkn_index].type) {
                case TknType::l_bracket: tkn_index++; break;
                case TknType::comma: tkn_index++; break;
                case TknType::quote: tkn_index++; break;
                case TknType::gt_op: tkn_index++; break;
                case TknType::lt_op: tkn_index++; break;
                case TknType::proj_kw: tkn_index++; break;
                case TknType::arrow_op: tkn_index++; break;
                case TknType::l_brace: tkn_index++; break;
                case TknType::r_brace: tkn_index++; break;
                case TknType::r_bracket: tkn_index++; break;
                case TknType::name_kw:
                    while (build_tkns[tkn_index].type != ylang::TknType::string_literal)
                        tkn_index++;
                    project.name = build_tkns[tkn_index].value;
                    tkn_index++;
                break;
                case TknType::author_kw:
                    while (build_tkns[tkn_index].type != ylang::TknType::string_literal)
                        tkn_index++;
                    project.author = build_tkns[tkn_index].value;
                    tkn_index++;
                break;
                case TknType::description_kw:
                    while (build_tkns[tkn_index].type != ylang::TknType::string_literal)
                        tkn_index++;
                    project.description = build_tkns[tkn_index].value;
                    tkn_index++;
                break;
                case TknType::version_kw:
                    while (build_tkns[tkn_index].type != ylang::TknType::int_literal)
                        tkn_index++;
                    project.v_major = std::stoi(build_tkns[tkn_index].value);
                    tkn_index++; tkn_index++;
                    project.v_minor = std::stoi(build_tkns[tkn_index].value);
                    tkn_index++; tkn_index++;
                    project.v_patch = std::stoi(build_tkns[tkn_index].value);
                    tkn_index++;
                break;
                case TknType::root_kw:
                    while (build_tkns[tkn_index].type != ylang::TknType::string_literal)
                        tkn_index++;
                    project.src_dir = m_SpaceInfo.directory + "/" + build_tkns[tkn_index].value;
                    tkn_index++;
                break;
                case TknType::target_kw:
                    while (build_tkns[tkn_index].type != ylang::TknType::other_id &&
                           build_tkns[tkn_index].type != ylang::TknType::build_kw)
                        tkn_index++;
                    project.build_dir = m_SpaceInfo.directory + "/" + build_tkns[tkn_index].value;
                    tkn_index++;
                break;
                case TknType::config_kw:
                    while (build_tkns[tkn_index].type != ylang::TknType::debug_kw &&
                           build_tkns[tkn_index].type != ylang::TknType::release_kw)
                        tkn_index++;
                    if (build_tkns[tkn_index].type == ylang::TknType::debug_kw) {
                        project.config = ProjectConfig::debug;
                    } else {
                        project.config = ProjectConfig::release;
                    }
                    tkn_index++;
                break;
                case TknType::files_kw:
                    while (build_tkns[tkn_index].type != ylang::TknType::l_brace)
                        tkn_index++;
                    tkn_index++;
                    while (build_tkns[tkn_index].type != ylang::TknType::r_brace) {
                        if (build_tkns[tkn_index].type == ylang::TknType::string_literal) {
                            file_names.push_back(build_tkns[tkn_index].value);
                        }
                        tkn_index++;
                    }
                    tkn_index++;
                break;
                case TknType::type_kw:
                    while (build_tkns[tkn_index].type != ylang::TknType::executable_kw &&
                           build_tkns[tkn_index].type != ylang::TknType::library_kw)
                        tkn_index++;
                    if (build_tkns[tkn_index].type == ylang::TknType::executable_kw) {
                        project.type = ProjectType::executable;
                    } else {
                        project.type = ProjectType::library;
                    }
                    tkn_index++;
                break;
                default:
                    std::cerr << "< Fatal Error | Invalid Build Object >" << std::endl;
                    return false;
            }
        }
        
        for (const auto& file_name : file_names) {
            project.filepaths.push_back(project.src_dir + "/" + file_name);
        }

        buildInfo.name = project.name;
        buildInfo.author = project.author;
        buildInfo.description = project.description;
        buildInfo.v_major = project.v_major;
        buildInfo.v_minor = project.v_minor;
        buildInfo.v_patch = project.v_patch;
        buildInfo.directory = project.root_dir;
        buildInfo.projects.push_back(project);

        m_SpaceInfo.name = project.name;
        m_SpaceInfo.author = project.author;
        m_SpaceInfo.description = project.description;
        m_SpaceInfo.v_major = project.v_major;
        m_SpaceInfo.v_minor = project.v_minor;
        m_SpaceInfo.v_patch = project.v_patch;
        m_SpaceInfo.directory = project.root_dir;
        m_SpaceInfo.builds.push_back(buildInfo);

        return true;
    }

    bool Compiler::BuildBuildspace() {
        UNIMPLIMENTED
        return true;
    }

    bool Compiler::BuildWorkspace() {
        UNIMPLIMENTED
        return true;
    }

    bool Compiler::Build() {

        for (const auto& build_obj : m_SpaceInfo.builds) {
            for (const auto& p : build_obj.projects) {
                std::cout << "[Building] [< " << p.name << " >]" << std::endl;
                for (const auto& file : p.filepaths) {
                    std::cout << "\n -> [< " << file << " >]" << std::endl;
                    auto s = LexFile(file);
                    if (s.statements.size() == 0) {
                        std::cerr << "< Lex or Filter Failure >" << std::endl;
                        return false;
                    } else {
                        m_SpaceInfo.final_compile_info.statements.insert(m_SpaceInfo.final_compile_info.statements.end(), s.statements.begin(), s.statements.end());
                    }
                }
            }
        }

        std::cout << "\n[Final Compile Info]" << std::endl;
        std::cout << "[Project Name] " << m_SpaceInfo.name << std::endl;
        std::cout << "[Project Version] " << m_SpaceInfo.v_major << "." << m_SpaceInfo.v_minor << "." << m_SpaceInfo.v_patch << std::endl;
        std::cout << "[Project Directory] " << m_SpaceInfo.directory << "\n";
        std::cout << "[Project Source Directory] " << m_SpaceInfo.builds[0].projects[0].src_dir << "\n";
        std::cout << "[Project Build Directory] " << m_SpaceInfo.builds[0].projects[0].build_dir << "\n";
        std::cout << "\n";
        std::cout << "[Project Author] " << m_SpaceInfo.author << std::endl;
        std::cout << "[Project Description] " << m_SpaceInfo.description << std::endl;
        std::cout << "\n";
        for (const auto& fp : m_SpaceInfo.builds[0].projects[0].filepaths) {
            std::cout << "\t[Project File] " << fp << std::endl;
        }
        std::cout << std::endl;

        return true;
    }

    bool Compiler::Compile(const std::string& folderpath) {

        std::vector<std::filesystem::path> paths;
        std::string build_obj_path;

        TokenFilter tokenFilter;
        for (const auto& entry : std::filesystem::directory_iterator(folderpath))
            paths.push_back(entry.path());

        for (auto& p : paths) {
            build_obj_path = p.string();

            for (auto& c : build_obj_path)
                if (c == '\\') c = '/';
            
            if (p.extension() == ".yproj") {
                std::cout << "[Building Y Project] [< " << build_obj_path << " >]" << std::endl;
                m_SpaceInfo.type = SpaceType::projectspace;
                break;
            } else if (p.extension() == ".ybuild") {
                std::cout << "[Building Y Objects] [< " << build_obj_path << " >]" << std::endl;
                m_SpaceInfo.type = SpaceType::buildspace;
                break;
            } else if (p.extension() == ".yspace") {
                std::cout << "[Building Space] [< " << build_obj_path << " >]" << std::endl;
                m_SpaceInfo.type = SpaceType::workspace;
                break;
            } else {
                std::cout << "[Can not find Y Object file to build]\n";
                std::cout << "[Please create a build.yproj, build.ybuild, or build.yspace file to direct build process] " << std::endl;
                return false;
            }
        } 

        m_SpaceInfo.directory = folderpath;
        m_SpaceInfo.main_build_obj_path = build_obj_path;

        switch (m_SpaceInfo.type) {
            case SpaceType::projectspace: {
                if (!BuildProjectspace()) return false;
                break;
            }
            case SpaceType::buildspace: {
                if (!BuildBuildspace()) return false;
                break;
            }
            case SpaceType::workspace: {
                if (!BuildWorkspace()) return false;
                break;
            }
            default: {
                std::cout << "[Can not find Y Object file to build]\n";
                std::cout << "[Please create a build.yproj, build.ybuild, or build.yspace file to direct build process] " << std::endl;
                return false;
            }
        }

        if (!Build()) return false;

        return true;
    }

}