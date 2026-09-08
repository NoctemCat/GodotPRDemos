# LibGodot Core Web Export Example

This example only supports web export templates, but it should be possible to build web editor, there is just no code for it.
Brings web LibGodot on par with currently implemented platforms.

## How to build

Steps:
- Update git submodules.
```
git submodule update --init --recursive
```
- Build shared LibGodot editor. Pick the platform you develop on https://docs.godotengine.org/en/stable/engine_details/development/compiling/index.html and install requirements.
```
cd godot
scons target=editor library_type=shared_library
cd ..
```
- Change `editor_shared_libgodot_name` in root `SConstruct` to the name of the resulted shared library.
- Build editor in root.
```
scons target=editor
```
- Launch `bin/<libgodot_editor>` and open the `project` folder, try to launch the project in editor, it should work.
- Install Emscripten https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended.
- Build shared web export templates, the same as https://docs.godotengine.org/en/stable/engine_details/development/compiling/compiling_for_web.html, but with `library_type=shared_library`.
```
cd godot
scons platform=web target=template_debug library_type=shared_library
scons platform=web target=template_release library_type=shared_library
cd ..
```
- Build web export templates in root.
```
scons platform=web target=template_debug
scons platform=web target=template_release
```
- Open LibGodot editor and export to web platform, pick the web export template from the root `bin` near editor.

### Tested with
Emscripten version: 6.0.2, needed to manually add additional `"-sGROWABLE_ARRAYBUFFERS=0"`, see the [issue](https://github.com/emscripten-core/emscripten/issues/27241)
Godot:
```
scons target=editor library_type=shared_library accesskit=no
scons platform=web target=template_release library_type=shared_library
```
LibGodot:
```
scons target=editor
scons platform=web target=template_release
```