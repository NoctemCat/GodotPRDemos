#pragma once

#include "gdextension_interface.h"
#include <godot_cpp/classes/godot_instance.hpp>
#include <godot_cpp/godot.hpp>

extern "C" {
void initialize_default_module(godot::ModuleInitializationLevel p_level);
void uninitialize_default_module(godot::ModuleInitializationLevel p_level);

GDExtensionBool gdextension_default_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization *r_initialization
);
}
class LibGodot {
public:
    static godot::GodotInstance *create_godot_instance(
        int p_argc, char *p_argv[],
        GDExtensionInitializationFunction p_init_func = gdextension_default_init
    );
    static void destroy_godot_instance(godot::GodotInstance *instance);
};