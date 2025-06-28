cmake_minimum_required(VERSION 3.20)
project(MySDL3Game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Direct the game.exe to project/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Set to Debug mode so you i wont go insane finding things
set(CMAKE_CXX_FLAGS_DEBUG "$ {CMAKE_CXX_FLAGS_DEBUG} -g")

# Include SDL3 + my headers
include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/headers"
)

# Linker directory for SDL3 static lib
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Grab all .cpp/.c files
file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/headers/*.h" "${PROJECT_SOURCE_DIR}/headers/*.hpp" "${PROJECT_SOURCE_DIR}/components/*.hpp" "${PROJECT_SOURCE_DIR}/components/*.h")
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.[cC]*")

add_executable(game ${SOURCES} ${HEADERS})

# OpenGL
find_package(OpenGL REQUIRED)

# Core linking
target_link_libraries(game PRIVATE OpenGL::GL)

# SDL3 libs
target_link_libraries(game PRIVATE
    "${PROJECT_SOURCE_DIR}/lib/libassimp.dll.a"
    "${PROJECT_SOURCE_DIR}/lib/libSDL3.dll.a"
    "${PROJECT_SOURCE_DIR}/lib/libSDL3_image.dll.a"
    "${PROJECT_SOURCE_DIR}/lib/libSDL2_mixer.dll.a"
    "${PROJECT_SOURCE_DIR}/lib/libSDL3_ttf.dll.a"
)

# Optional: Windows-only system libs
if(WIN32)
    target_link_libraries(game PRIVATE
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
