#include "register_types.hpp"
#include <cstdio>
#include <cstdlib>
#include <emscripten/emscripten.h>
#include <godot_cpp/classes/godot_instance.hpp>

extern "C" void godot_js_os_finish_async(void (*p_callback)());

static godot::GodotInstance *instance = nullptr;
static bool shutdown_complete = false;

void exit_callback() {
    if (!shutdown_complete) {
        return; // Still waiting.
    }
    if (instance != nullptr) {
        LibGodot::destroy_godot_instance(instance);
        instance = nullptr;
    }
    emscripten_force_exit(EXIT_SUCCESS);
}

void cleanup_after_sync() {
    shutdown_complete = true;
}

void main_loop_callback() {
    if (instance->iteration()) {
        emscripten_cancel_main_loop();
        emscripten_set_main_loop(exit_callback, -1, false);
        godot_js_os_finish_async(cleanup_after_sync);
    }
}

int main(int argc, char **argv) {
    instance = LibGodot::create_godot_instance(argc, argv);
    if (instance == nullptr) {
        fprintf(stderr, "Error creating Godot instance\n");
        return EXIT_FAILURE;
    }

    instance->start();
    emscripten_set_main_loop(main_loop_callback, -1, false);
    main_loop_callback();
    return EXIT_SUCCESS;
}