# c-init

C project template wired for CMake, Ninja, clang-cl, and haikal code generation.

## Dependencies

- Python 3
- Git
- CMake
- Ninja
- LLVM/Clang with `clang-cl` on `PATH`
- Visual Studio Build Tools or another environment that provides the MSVC Windows SDK/linker toolchain

On Windows, run the commands from a shell where the MSVC toolchain is available, such as a Visual Studio Developer Command Prompt, or make sure `clang-cl`, `link`, `cmake`, and `ninja` are all on `PATH`.

## Setup

Initialize submodules:

```powershell
git submodule update --init --recursive
```

## Build

Configure the debug build:

```powershell
python bunyan.py config debug
```

Build debug:

```powershell
python bunyan.py build debug
```

Build and run:

```powershell
python bunyan.py run debug
```

Build and launch under the debugger:

```powershell
python bunyan.py debugexe debug
```

Other configs:

```powershell
python bunyan.py build release
python bunyan.py build reldebug
```

Clean generated build directories:

```powershell
python bunyan.py clean
```

The build wrapper compiles `extern/haikal`, runs `haikal.exe --entry src/main.c --meta extern/haikal/src/meta_arena` from the repository root, then builds `c-init`.
