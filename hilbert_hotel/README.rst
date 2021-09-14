
# Project struct
```
- godot_modules
- godot
```

# For building:
```
# from  godot folder
# First full godot
scons custom_modules=../godot_modules summator_shared=yes platform=x11

# Only lib then
scons custom_modules=../godot_modules summator_shared=yes platform=x11 bin/libsummator.x11.tools.64.so
```

# For running:

```
# from  godot folder
export LD_LIBRARY_PATH="$PWD/bin/"  ./bin/godot*
```

# Building doc
```
LD_LIBRARY_PATH="./bin" ./bin/godot.x11.tools.64 --doctool ../godot_modules/
```
