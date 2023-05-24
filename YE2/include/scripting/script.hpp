#ifndef YE_SCRIPT_HPP
#define YE_SCRIPT_HPP

#include "mono/metadata/assembly.h"
#include "mono/metadata/threads.h"

namespace YE {
namespace scripting {
    
    /** Script Class 
     *   -> Holds all data related to a single script object
    */
    class Script {

        MonoClass* klass = nullptr;
        MonoObject* obj = nullptr;

        public:
            Script() {}
            ~Script() {}

            

    };

}
}

#endif