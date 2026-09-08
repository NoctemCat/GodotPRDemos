# LibGodot Linux Merge static libraries

Allows to use static LibGodot, both editor and export templates.

## How to build
Steps:
- Pick the platform you develop on https://docs.godotengine.org/en/stable/engine_details/development/compiling/index.html and install the requirements.
- Update git submodules.
```
git submodule update --init --recursive
```
- Build static libraries in the `godot` folder.
```
scons target=editor library_type=static_library
scons target=template_release library_type=static_library
```
- Return to the root of the repo.
- Change `LibGodot names` in the SConstruct.
- Build editor and export template in the root.
```
scons target=editor
scons target=template_release
```
- Launch the editor and export the project using the built export template.

### Personally tested with
Godot:
```
scons target=editor library_type=static_library accesskit=no
scons target=template_release library_type=static_library accesskit=no use_llvm=yes linker=lld lto=thin
```
LibGodot:
```
scons target=editor
scons target=template_release use_llvm=yes lto=thin
```