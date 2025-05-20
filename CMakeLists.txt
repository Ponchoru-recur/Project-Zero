cmake_minimum_required(VERSION 3.20)
project(MySDL3Game)

set(CMAKE_CXX_STANDARD 17)

# Direct the game.exe to project/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Include SDL3 headers
include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/headers")

# Linker directory for SDL3 static lib
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Your source files
set(SOURCES
    src/main.cpp
    src/character.cpp
)

add_executable(game ${SOURCES})

# Link SDL3 static library (change filename if needed)

# Optional: on Windows, link some system libs SDL3 might need
if(WIN32)
    target_link_libraries(game
        "${PROJECT_SOURCE_DIR}/lib/libSDL3.dll.a"
        "${PROJECT_SOURCE_DIR}/lib/libSDL3_image.dll.a"
        "${PROJECT_SOURCE_DIR}/lib/libSDL2_mixer.dll.a"
        "${PROJECT_SOURCE_DIR}/lib/libSDL3_ttf.dll.a"
        -lwinmm
        -limm32
        -lole32
        -loleaut32
        -luuid
        -lversion
        -lsetupapi
        -ldinput8
        -ldxguid
    )
endif()
