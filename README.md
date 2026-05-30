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
python build.py config debug
```

Build debug:

```powershell
python build.py build debug
```

Build and run:

```powershell
python build.py run debug
```

Build and launch under the debugger:

```powershell
python build.py debugexe debug
```

Other configs:

```powershell
python build.py build release
python build.py build reldebug
```

Clean generated build directories:

```powershell
python build.py clean
```

The build wrapper compiles `extern/haikal`, runs `haikal.exe` from the repository root to generate code from `haikal.toml`, then builds `c-init`.
