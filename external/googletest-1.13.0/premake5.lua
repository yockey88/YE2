project "gtest"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    targetdir(tdir)
    objdir(odir)

    files {
        "googletest/googletest/include/**.h" ,
        "googletest/googletest/src/**.h" ,
        "googletest/googletest/src/**.cc"
    }

    includedirs {
        "googletest/googletest/include" ,
        "googletest/googletest"
    }

    filter { "system:windows" }
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        symbols "off"
        optimize "on"