#ifndef YE_MATERIAL_HPP
#define YE_MATERIAL_HPP

namespace YE {
namespace rendering {

    class Material {
        Material(const Material&) = delete;
        Material(Material&&) = delete;
        Material& operator=(const Material&) = delete;
        public:
            

            Material() {}
            ~Material() {}
    };

}
}

#endif