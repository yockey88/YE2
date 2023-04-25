workspace "YE2"
    startproject "TestBed"
    architecture "x64"

    configurations {
        "Debug" ,
        "Release"
    }

    tdir = "bin/%{cfg.buildcfg}/%{prj.name}"
    odir = "bin-obj/%{cfg.buildcfg}/%{prj.name}"

    -- External Dependencies
    externals = {}
    externals["sdl2"] = "external/SDL2-2.24.2"
    externals["imgui"] = "external/imgui-docking"
    externals["imguizmo"] = "external/Imguizmo"
    externals["entt"] = "external/entt"
    externals["spdlog"] = "external/spdlog-1.11.0"
    externals["glad"] = "external/glad"
    externals["glm"] = "external/glm-master"
    externals["stb"] = "external/stb"
    externals["json"] = "external/json"
    externals["box2d"] = "external/box2d"
    externals["reactphysics3d"] = "external/ReactPhysics3d"

    -- Glad before all
    include "external/glad"
    include "external/box2d"
    include "external/ReactPhysics3d"

    --------------------
    -- Engine Library --
    --------------------
    project "YE2"
        location "YE2"
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir(tdir)
        objdir(odir)

        files {
            "%{prj.name}/include/**.hpp" ,
            "%{prj.name}/src/**.cpp" ,
            "%{externals.imgui}/*.h" ,
            "%{externals.imgui}/*.cpp" ,
            "%{externals.imguizmo}/*.hpp" ,
            "%{externals.imguizmo}/*.cpp" ,
            "%{externals.entt}/*.hpp" ,
            "%{externals.glad}**.c" ,
            "%{externals.glad}**.h" ,
            "%{externals.glm}/**.hpp" ,
            "%{externals.stb}/*.h" ,
            "%{externals.json}/**.hpp" ,
            "%{externals.box2d}/src/**.cpp" ,
            "%{externals.box2d}/include/**.h" ,
            "%{externals.reactphysics3d}/include/reactphysics3d**.h" ,
            "%{externals.reactphysics3d}/src/**.cpp"
        }

        externalincludedirs {
            "%{prj.name}/include" ,
            "%{externals.sdl2}/include" ,
            "%{externals.imgui}" ,
            "%{externals.imguizmo}" ,
            "%{externals.entt}" ,
            "%{externals.spdlog}/include" ,
            "%{externals.glad}/include" ,
            "%{externals.glm}" ,
            "%{externals.stb}" ,
            "%{externals.json}/include" ,
            "%{externals.box2d}/include" ,
            "%{externals.reactphysics3d}/include"
        }

        -- flags { "FatalWarnings" }

        defines {
            "GLFW_INCLUDE_NONE" -- Ensures glad doesnt include glfw
        }

        filter { "system:windows" , "configurations:*" }
            systemversion "latest"
            defines {
                "YE_PLATFORM_WINDOWS"
            }

            libdirs {
                "%{externals.sdl2}/lib/x64" , 
                "%{externals.box2d}/bin/Debug/box2d"
            }

            links {
                "SDL2" ,
                "glad" ,
                "box2d" ,
                "reactphysics3d"
            }

        filter "configurations:Debug"
            defines {
                "YE_DEBUG"
            }
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines {
                "YE_RELEASE"
            }
            runtime "Release"
            symbols "off"
            optimize "on"

    -------------
    -- TestBed --
    -------------
    project "TestBed"
        location "TestBed"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"
        links "YE2"

        targetdir(tdir)
        objdir(odir)

        files {
            "%{prj.name}/**.cpp" ,
            "%{prj.name}/**.hpp" 
        }

        externalincludedirs {
            "%{prj.name}" ,
            "%{prj.name}/include" ,
            "YE2/include" ,
            "%{externals.sdl2}/include" ,
            "%{externals.glad}/include" ,
            "%{externals.spdlog}/include" ,
            "%{externals.entt}" ,
            "%{externals.imgui}" ,
            "%{externals.imguizmo}" ,
            "%{externals.glm}" ,
            "%{externals.stb}" ,
            "%{externals.json}/include" ,
            "%{externals.box2d}/include" ,
            "%{externals.reactphysics3d}/include"
        }

        resincludedirs {
            "res/**"
        }

        filter { "system:windows" , "configurations:*" }
            systemversion "latest"
            defines {
                "YE_PLATFORM_WINDOWS"
            }

            libdirs {
                "%{externals.sdl2}/lib/x64" , 
                "%{externals.box2d}/bin/Debug/box2d"
            }

            links {
                "YE2" ,
                "SDL2" ,
                "glad" ,
                "box2d" ,
                "reactphysics3d"
            }

        filter "configurations:Debug"
            defines {
                "YE_DEBUG"
            }
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines {
                "YE_RELEASE"
            }
            runtime "Release"
            symbols "off"
            optimize "on"
        
    ------------------
    -- Physics Demo --
    ------------------
    project "PhysicsDemo_1"
        location "demos/PhysicsDemo_1"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"
        links "YE2"

        targetdir(tdir)
        objdir(odir)

        files {
            "demos/%{prj.name}/**.cpp" ,
            "demos/%{prj.name}/**.hpp" 
        }

        externalincludedirs {
            "demos/%{prj.name}" ,
            "demos/%{prj.name}/include" ,
            "YE2/include" ,
            "%{externals.sdl2}/include" ,
            "%{externals.glad}/include" ,
            "%{externals.spdlog}/include" ,
            "%{externals.entt}" ,
            "%{externals.imgui}" ,
            "%{externals.imguizmo}" ,
            "%{externals.glm}" ,
            "%{externals.stb}" ,
            "%{externals.json}/include" ,
            "%{externals.box2d}/include" ,
            "%{externals.reactphysics3d}/include"
        }

        resincludedirs {
            "res/**"
        }

        filter { "system:windows" , "configurations:*" }
            systemversion "latest"
            defines {
                "YE_PLATFORM_WINDOWS"
            }

            libdirs {
                "%{externals.sdl2}/lib/x64" , 
                "%{externals.box2d}/bin/Debug/box2d"
            }

            links {
                "YE2" ,
                "SDL2" ,
                "glad" ,
                "box2d" ,
                "reactphysics3d"
            }

        filter "configurations:Debug"
            defines {
                "YE_DEBUG"
            }
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines {
                "YE_RELEASE"
            }
            runtime "Release"
            symbols "off"
            optimize "on"