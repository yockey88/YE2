#include "compiler.hpp"

int main(int argc , char* argv[]) {

    try {
        ylang::Compiler compiler;

        if (!compiler.Compile("test_files/testing_program")) {
            std::cerr << "<Error | Compiler failed to compile>" << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "<Error | " << e.what() << ">" << std::endl;
        return 1;
    }

    return 0;
}