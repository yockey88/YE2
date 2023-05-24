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
    externals["mono"] = "external/mono"
    externals["llvm"] = "C:/Program Files (X86)/LLVM"

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    -- Glad before all
    include "external/glad"

    -- physics and such
    include "external/box2d"
    include "external/ReactPhysics3d"
    
    -- Scripting
    include "./YE2/core_scripts"

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
            "%{externals.imgui}/*.cpp" 
        }

        includedirs {
            "%{prj.name}/include" 
        }

        externalincludedirs {
            "%{externals.sdl2}/include" ,
            "%{externals.imgui}" ,
            "%{externals.entt}" ,
            "%{externals.spdlog}/include" ,
            "%{externals.glad}/include" ,
            "%{externals.glm}" ,
            "%{externals.stb}" ,
            "%{externals.json}/include" ,
            "%{externals.box2d}/include" ,
            "%{externals.reactphysics3d}/include" ,
            "%{externals.mono}/include"
        }

        -- flags { "FatalWarnings" }

        defines {
            "GLFW_INCLUDE_NONE" -- Ensures glad doesnt include glfw
        }

        filter { "system:windows" , "configurations:*" }
            systemversion "latest"
            defines {
                "YE_PLATFORM_WINDOWS" ,
                "_CRT_SECURE_NO_WARNINGS"
            }

            libdirs {
                "%{externals.sdl2}/lib/x64" , 
                "%{externals.box2d}/bin/Debug/box2d" ,
                "%{externals.mono}/lib" ,
                "%{externals.mono}/lib/4.8-api"
            }

            links {
                "SDL2" ,
                "glad" ,
                "box2d" ,
                "reactphysics3d" ,
                "mono-2.0-sgen" 
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
    
    -- I want a single DLL for all core libs instead of having 
    --      to deal with loading DLLs and managing who and what gets them 
    --      and when they get them and when I can unload them and all that
    --      But that will be a future thing I guess.
    -- project "YE2_CoreScripts"
    --     location "YE2_CoreScripts"
    --     kind "SharedLib"
    --     language "C#"
    --     dotnetframework "4.7.2"

    --     targetdir(tdir .. "/runtime_scripts")
    --     objdir(odir .. "/runtime_scripts")

    --     files {
    --         "%{prj.name}/Source/**.cs" ,
    --         "%{prj.name}/Properties/**.cs" , 
    --     }

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
            "%{prj.name}/**.hpp" ,
            "%{prj.name}/assemblies/**.asm" 
        }

        includedirs {
            "%{prj.name}" ,
            "%{prj.name}/include" ,
            "%{prj.name}/other"
        }

        externalincludedirs {
            "YE2/include" ,
            "%{externals.sdl2}/include" ,
            "%{externals.glad}/include" ,
            "%{externals.spdlog}/include" ,
            "%{externals.entt}" ,
            "%{externals.imgui}" ,
            "%{externals.glm}" ,
            "%{externals.stb}" ,
            "%{externals.json}/include" ,
            "%{externals.box2d}/include" ,
            "%{externals.reactphysics3d}/include" ,
            "%{externals.llvm}/include" ,
            "%{externals.mono}/include"
        }
        
        filter { "system:windows" , "configurations:*" }
            systemversion "latest"
            
            defines {
                "YE_PLATFORM_WINDOWS" ,
                "_CRT_SECURE_NO_WARNINGS"
            }

            libdirs {
                "%{externals.sdl2}/lib/x64" , 
                "%{externals.box2d}/bin/Debug/box2d" ,
                "%{externals.mono}/lib" ,
                "%{externals.mono}/lib/4.8-api"
            }

            links {
                "YE2" ,
                "SDL2" ,
                "glad" ,
                "box2d" ,
                "reactphysics3d" ,
                "mono-2.0-sgen" 
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

        includedirs {
            "demos/%{prj.name}" ,
            "demos/%{prj.name}/include" 
        }

        externalincludedirs {
            "YE2/include" ,
            "%{externals.sdl2}/include" ,
            "%{externals.glad}/include" ,
            "%{externals.spdlog}/include" ,
            "%{externals.entt}" ,
            "%{externals.imgui}" ,
            "%{externals.glm}" ,
            "%{externals.stb}" ,
            "%{externals.json}/include" ,
            "%{externals.box2d}/include" ,
            "%{externals.reactphysics3d}/include" ,
            "%{externals.llvm}/include" ,
            "%{externals.mono}/include"
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
                "%{externals.box2d}/bin/Debug/box2d" ,
                "%{externals.mono}/lib" ,
                "%{externals.mono}/lib/4.8-api"
            }

            links {
                "YE2" ,
                "SDL2" ,
                "glad" ,
                "box2d" ,
                "reactphysics3d" ,
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