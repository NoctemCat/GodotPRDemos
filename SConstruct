#!/usr/bin/env python
import os
import sys

from methods import print_error, build_web_template

# ----------------------------------------------------------------------
editor_shared_libgodot_name = "libgodot.linuxbsd.editor.x86_64.so"
# ----------------------------------------------------------------------

localEnv = Environment(tools=["default"], PLATFORM="")

customs = ["custom.py"]
customs = [os.path.abspath(path) for path in customs]

opts = Variables(customs, ARGUMENTS)
opts.Update(localEnv)

Help(opts.GenerateHelpText(localEnv))

env = localEnv.Clone()

if (not (os.path.isdir("godot-cpp") and os.listdir("godot-cpp"))) or (not (os.path.isdir("godot") and os.listdir("godot"))):
    print_error("""godot-cpp or godot is not available within this folder, as Git submodules haven't been initialized.
Run the following command to download godot-cpp:

    git submodule update --init --recursive""")
    sys.exit(1)

env = SConscript("godot-cpp/SConstruct", {"env": env, "api_version": "4.7"})

env.Append(LIBPATH=["godot/bin"])
env.Append(CPPPATH=["src/"])
sources = [
    "src/player.cpp",
    "src/register_types.cpp",
]

if env["platform"] != "web":
    sources += ["src/main.cpp"]

    env.Append(LIBS=[editor_shared_libgodot_name])

    program = env.Program(f"bin/{env["platform"]}/libgodot_{env["target"]}", source=sources)
    libgodot = env.Install("bin/", [program, f"godot/bin/{editor_shared_libgodot_name}"])

    Default(program, libgodot)
else:
    sources += ["src/main_web.cpp"]

    env["CFLAGS"] = []
    env["CXXFLAGS"] = []
    env["CCFLAGS"] = []
    env["LINKFLAGS"] = []

    for js_lib in [
        # modules
        "godot/modules/webxr/native/library_godot_webxr.js",
        "godot/modules/websocket/library_godot_websocket.js",
        "godot/modules/webrtc/library_godot_webrtc.js",
        # Platform
        "godot/platform/web/js/libs/library_godot_audio.js",
        "godot/platform/web/js/libs/library_godot_display.js",
        "godot/platform/web/js/libs/library_godot_emscripten.js",
        "godot/platform/web/js/libs/library_godot_fetch.js",
        "godot/platform/web/js/libs/library_godot_webmidi.js",
        "godot/platform/web/js/libs/library_godot_os.js",
        "godot/platform/web/js/libs/library_godot_runtime.js",
        "godot/platform/web/js/libs/library_godot_input.js",
        "godot/platform/web/js/libs/library_godot_webgl2.js",
        # js singleton
        "godot/platform/web/js/libs/library_godot_javascript_singleton.js",
    ]:
        env.Append(LINKFLAGS=["--js-library", env.File(js_lib).abspath])
    for post in ["godot/platform/web/js/patches/patch_em_gl.js"]:
        env.Append(LINKFLAGS=["--post-js", env.File(post).abspath])

    # This needs -sAUTOLOAD_DYLIBS=0, allows to use -sMAIN_MODULE=2
    env.Append(LINKFLAGS=[f"godot/bin/godot.side.web.{env["target"]}.wasm32.wasm"])
    env.Append(LIBS=["idbfs.js"])

    env.Append(CFLAGS=["-std=gnu17"])
    env.Append(CXXFLAGS=["-std=gnu++17", "-fno-exceptions"])
    env.Append(CCFLAGS=[
        # "-sMAIN_MODULE=1",
        "-sMAIN_MODULE=2",

        "-flto=thin",
        "-msimd128",
        "-pthread",
        "-sSUPPORT_LONGJMP='wasm'",
        "-fcolor-diagnostics",
        "-Wall",
        "-Wshadow-field-in-constructor",
        "-Wshadow-uncaptured-local",
        "-Wno-ordered-compare-function-pointers",
        "-Wenum-conversion",
    ])
    if env.debug_features:
        env.Append(LINKFLAGS=["-sASSERTIONS=1"])
    env.Append(LINKFLAGS=[
        # "-sMAIN_MODULE=1",
        # "-EXPORT_ALL=1",
        "-sMAIN_MODULE=2",
        "-sAUTOLOAD_DYLIBS=0",
        "-sGROWABLE_ARRAYBUFFERS=0",

        "-flto=thin",
        "-sINITIAL_MEMORY=32MB",
        "-sMAX_WEBGL_VERSION=2",
        "-sOFFSCREEN_FRAMEBUFFER=1",
        "-sGL_ENABLE_GET_PROC_ADDRESS=0",
        "-sSTACK_SIZE=5120KB",
        "-pthread",
        "-sDEFAULT_PTHREAD_STACK_SIZE=2048KB",
        "-sPTHREAD_POOL_SIZE=\"Module['emscriptenPoolSize']||8\"",
        "-sMAXIMUM_MEMORY=2048MB",
        "-Wl,-u,_emscripten_run_callback_on_thread",
        "-sWASM_BIGINT",
        "-sENVIRONMENT=web,worker",
        "-sMODULARIZE=1",
        "-sEXPORT_NAME='Godot'",
        "-sSUPPORT_LONGJMP='wasm'",
        "-sALLOW_MEMORY_GROWTH=1",
        "-sINVOKE_RUN=0",
        "-sEXIT_RUNTIME=1",
        "-sGL_WORKAROUND_SAFARI_GETCONTEXT_BUG=0",
        # "-sEXPORTED_FUNCTIONS=__emscripten_thread_crashed,_free,_main,_malloc,_libgodot_create_godot_instance,_libgodot_destroy_godot_instance",
        "-sEXPORTED_FUNCTIONS=__emscripten_thread_crashed,_free,_main,_malloc",
        "-sEXPORTED_RUNTIME_METHODS=HEAP16,HEAP32,HEAP64,HEAP8,HEAPF32,HEAPF64,HEAPU16,HEAPU32,HEAPU64,HEAPU8,callMain,cwrap",
    ])

    if env["target"] == "template_release":
        env.Append(CCFLAGS=["-O2"])
        env.Append(LINKFLAGS=["-O2"])
    else:
        env.Append(CCFLAGS=["-O0"])
        env.Append(LINKFLAGS=["-O0"])

    output = env.Program(["bin/web/libgodot_example.js", "bin/web/libgodot_example.wasm"], source=sources)
    zname = f"godot.web.{env["target"]}.wasm32.zip"
    web_template = env.NoCache(env.Command(f"bin/{zname}", [f"godot/bin/{zname}"] + output, env.Action(build_web_template)))

    Default(output, web_template)