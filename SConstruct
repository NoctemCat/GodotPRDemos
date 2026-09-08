#!/usr/bin/env python
import os
import sys

from methods import print_error

# LibGodot names:
# ----------------------------------------------------------------------
editor_static_name = "libgodot.linuxbsd.editor.x86_64.a"
template_release_static_name = "libgodot.linuxbsd.template_release.x86_64.llvm.a"
template_debug_static_name = "libgodot.linuxbsd.template_debug.x86_64.llvm.a"
# ----------------------------------------------------------------------

localEnv = Environment(tools=["default"], PLATFORM="")

opts = Variables([], ARGUMENTS)
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
    "src/main.cpp"
]

libgodot_name = editor_static_name
if env["target"] == "template_release":
    libgodot_name = template_release_static_name
elif env["target"] == "template_debug":
    libgodot_name = template_debug_static_name

env.Append(LIBS=[libgodot_name])

program = env.Program(f"bin/{env["platform"]}/libgodot_{env["target"]}", source=sources)

Default(program)
