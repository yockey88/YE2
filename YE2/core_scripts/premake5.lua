project "YE_CoreScripts"
    kind "SharedLib"
    language "C#"
    dotnetframework "4.7.2"

    --  not sure how to direct these to the correct location, right now TestBed is hardcoded in but I'd like for it to build
    --      directrly to <bin>/<config>/<User-Project>/runtime_scripts 
    targetdir("../../bin/%{cfg.buildcfg}/TestBed/runtime_scripts")
    objdir("../../bin-obj/%{cfg.buildcfg}/TestBed/runtime_scripts")

    files {
        "Properties/**.cs" ,
        "Source/**.cs"
    }

    filter { "system:windows" }
        systemversion "latest"

    filter "configurations:Debug"
        optimize "Off"
        symbols "Default"

    filter "configurations:Release"
        optimize "On"
        symbols "Default"