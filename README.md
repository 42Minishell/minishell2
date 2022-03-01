# minishell

Minishell 42 project; second iteration

## Documentation

Doxygen is used to generate documentation

The config for this is contained in the Doxyfile at the root of the repo

To generate HTML documentation just execute `doxygen` at the root of the repo, the output will be in `doc/`

## Compiling

Currently using CMake, 
biggest difference is that CMake compiles out-of-tree.

Basically this means that the build directory is not the same
as the source directory.

_Quick start to compiling:_

```
# In project root
mkdir build && cd build
cmake ..
make
```

`cmake ..` only generates the makefiles, this needs to be done after editing CMakeLists.txt

Changing the source without adding new files only need a recompile using `make` like you're used to.