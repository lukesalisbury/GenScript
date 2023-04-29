# GenScript
Configure Simple Builds system

Reads files from ./config/ to produce configurations for ninja builds

## Stages

### New Project (-new)
This stage create the basic directories and initial config files

Directories Created:
- ./bin/
- ./config/
- ./config/modules/
- ./include/
- ./resources/
- ./src/

File Created:
- ./config/default.txt - See Configuration for details
- ./config/modules/base.txt - See Modules for details

### New Platform (-platform)
Reads system information to create configurations files for the current platform. Platform can be overwrite by setting the environment values PLATFORM, PLATFORM_ARCH, PLATFORM_COMPILER before genscript
example: PLATFORM=Linux genscript.exe

File Created:
- ./config/$platform-$arch.txt
- ./config/$platform-common.txt


### Generate Build Script (-gen)
Creates build scripts base on current platform. It will replace the ./build.ninja file with a link to ./compile/$platform-$arch/build.ninja

## Configuration 
Configuration are stored in INI format files.

Example:
`[defines]
PLATFORM_BITS=64
[options]
compiler=gcc
linker=gcc
static_linker=ar -rc
program_suffix=
shared_suffix=.so
static_suffix=.a
[includes]
./include/
[libs]
stdc++
m
[lib_flags]
-std=c++11
[flags]
-std=c++11
[defines]
PLATFORM_$PLATFORM
[linker_flags]
-Wl,-rpath -Wl,\\$$ORIGIN/lib
[options-windows]
program_suffix=.exe
shared_suffix=.dll
[options-3ds]
finaliser=3dsxtool
program_suffix=.elf
finalise_suffix=.3dsx
[commands]
compile_cpp=${compiler} ${compiler_includes} ${compller_defines} ${compiler_flags} -o $out -c $in
compile_c=${compiler} ${compiler_includes} ${compller_defines}  ${compiler_flags} -o $out -c $in
link_shared=${linker} -shared ${compiler_lib_flags} $in -o ${binary_prefix}$out  ${compiler_lib}
link_static=${static_linker} ${object_dir}$out $in 
link=${linker} ${compiler_lib_flags} $in -o ${binary_prefix}$out ${compiler_lib} 
finalise=${finaliser} ${finalise_flags} $in -o ${binary_prefix}$out
build_resources=echo
clean=rm -rf ${object_dir}
`

## Modules
List of file names to be compiled and linked. By default the base.txt file is used, but other modules can be include by prefix the filename without extension with #.
Modules can also be build as Static or Shared Libraries by having the first line of the file start with $static ot $shared
