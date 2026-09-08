#include "register_types.hpp"
#include <cstdio>
#include <cstdlib>
#include <godot_cpp/classes/godot_instance.hpp>

int main(int argc, char **argv) {
    godot::GodotInstance *instance = LibGodot::create_godot_instance(argc, argv);
    if (instance == nullptr) {
        fprintf(stderr, "Error creating Godot instance\n");
        return EXIT_FAILURE;
    }
    instance->start();

    while (!instance->iteration()) {}
    LibGodot::destroy_godot_instance(instance);

    return EXIT_SUCCESS;
}