cmake_minimum_required(VERSION 3.10)

project(c-init VERSION 1.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_C_STANDARD 99)
# set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(extern/haikal/src/meta_arena/gen)
include_directories(extern/haikal/src/runtime)

add_subdirectory(extern/haikal)

add_executable(${PROJECT_NAME}
    src/main.c
    # src/string8.c
)
target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
add_dependencies(${PROJECT_NAME} haikal)
# add_subdirectory(extern) # in case of modules...
