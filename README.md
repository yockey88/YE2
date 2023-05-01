# YE2

3D Engine OpenGL/SDL2

## By Chris Y

---

I do all my development on windows right now (unfortunately) so thats what the build system currently works on. I dont have
any other systems to test on, but I am currently porting the code to be cross platform for Linux, and Mac. If you try to build this on those platforms before I am finished, simply submit a pull request and I'll look over it.

Right now the engine is barely a framework for rendering built almost entirely from 3rd party libraries. The future of the project lies in
removing these dependencies from the engine and implementing my own solutions (excepting OpenGL, SDL2, and STB which are beyond my capabilities to implement or I am simply not interested in doing so at the moment). Current dependencies I will eliminate in the future include:

- Box2D Physics
- React Physics 3D
- Entt (undecided, I really love this library)
- glm
- spdlog
- json (replacing any json/xml/... files with custom scripting language)

Premanent dependencies (as of right now when I am writing this):

- OpenGL (maybe exchange for Vulkan when I work up the courage to face Vulkan)
- SDL2
- STB (might implement custom texture loading in the future)
- Imgui and Imguizmo (I don't think I could implement UI better than ImGui its truly incredible)

---

### To Build Engine with Demos

> clone the repo and cd into it

    git clone https://github.com/yockey88/YE2.git
    cd YE2

> Make sure you have Python installed to generate the VS solution (currently porting buildchain to Linux and Mac)

    python3 cli.py gensln 

> Then you can use the toolchain to build and run

    python3 cli.py buildsln -c=<config> -p=<demo-name> (here config = debug | release)
    python3 cli.py run -c=<config> -p=<demo-name> (here config = Debug | Release)

***Note that config defaults to debug and demo-name defaults to TestBed which has no demos other than rendering***

***Note also the capitalization difference between the build configuration setting and the run configuration setting, this is due to how the toolchain works***

> The Build toolchain is built to handle multiple commands at once so you can just ype in

    python3 cli.py gensln buildsln -c=<config> -p=<demo-name> run -c=<config> -p=<demo-name> 

### To Use and Modify Engine

> clone the repo and cd into it

    git clone https://github.com/yockey88/YE2.git
    cd YE2

From here you have two choices:

1- Modify premake file to include your own project linking against the library. The project must be entirely contained within a single folder, but because you have to write your own `premake5.lua` file, you can structure the interior of the folder however you wish. Just do not forget to change the `MAIN_EXE_NAME` variable stored at the top of `tools/globals.py` to your own project folder location.

2- Or you can simply edit the `premake5.lua` to only build the library (delete the demos sections, leaving just the premake block for the static library)

***More Documentation on Engine Usage is currently being written***
