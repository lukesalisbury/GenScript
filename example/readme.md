
# Using GenScript

## Step 1: Copy genscript.c into directory
Included examples:
- SDL - Has multiple programs, along with static and shared libraries. Also Linux support for pkg-config

## Step 2: Compile genscript.c.
From the command line, Run one of the following commands:

`gcc genscript.c -o gsb.exe` or `clang genscript.c -o gsb.exe`

## Step 3: Run genscript (./gsb.exe)
Run `./gsb.exe` from command line. (Note: It's called gsb.exe on all platform, so we can do a single command for all platform)

## Step 4: Run ninja
Run `ninja` from command line to build project.

Once a platform is set up, Cross compiling can done by pointing ninja to the correct build file
`ninja -f compile/linux-x86_64/build.ninja`

