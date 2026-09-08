#include "register_types.hpp"
#include "libgodot.h"
#include "player.hpp"

void initialize_default_module(godot::ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) { return; }

    GDREGISTER_CLASS(sample::Player);
}

void uninitialize_default_module(godot::ModuleInitializationLevel p_level) {
    if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) { return; }
}

GDExtensionBool gdextension_default_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization *r_initialization
) {
    godot::GDExtensionBinding::InitObject init_object(
        p_get_proc_address, p_library, r_initialization
    );

    init_object.register_initializer(initialize_default_module);
    init_object.register_terminator(uninitialize_default_module);
    init_object.set_minimum_library_initialization_level(godot::MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_object.init();
}

godot::GodotInstance *LibGodot::create_godot_instance(
    int p_argc, char *p_argv[], GDExtensionInitializationFunction p_init_func
) {
    GDExtensionObjectPtr instance = libgodot_create_godot_instance(p_argc, p_argv, p_init_func);
    if (instance == nullptr) { return nullptr; }

    return reinterpret_cast<godot::GodotInstance *>(
        godot::internal::get_object_instance_binding(instance)
    );
}

void LibGodot::destroy_godot_instance(godot::GodotInstance *instance) {
    libgodot_destroy_godot_instance(instance->_owner);
}