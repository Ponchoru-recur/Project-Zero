# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Sam\Desktop\PlayThrough

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Sam\Desktop\PlayThrough\build

# Include any dependencies generated for this target.
include CMakeFiles/game.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/game.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game.dir/flags.make

CMakeFiles/game.dir/codegen:
.PHONY : CMakeFiles/game.dir/codegen

CMakeFiles/game.dir/src/app.cpp.obj: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/app.cpp.obj: CMakeFiles/game.dir/includes_CXX.rsp
CMakeFiles/game.dir/src/app.cpp.obj: C:/Users/Sam/Desktop/PlayThrough/src/app.cpp
CMakeFiles/game.dir/src/app.cpp.obj: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/game.dir/src/app.cpp.obj"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/app.cpp.obj -MF CMakeFiles\game.dir\src\app.cpp.obj.d -o CMakeFiles\game.dir\src\app.cpp.obj -c C:\Users\Sam\Desktop\PlayThrough\src\app.cpp

CMakeFiles/game.dir/src/app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/game.dir/src/app.cpp.i"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sam\Desktop\PlayThrough\src\app.cpp > CMakeFiles\game.dir\src\app.cpp.i

CMakeFiles/game.dir/src/app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/app.cpp.s"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Sam\Desktop\PlayThrough\src\app.cpp -o CMakeFiles\game.dir\src\app.cpp.s

CMakeFiles/game.dir/src/camera.cpp.obj: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/camera.cpp.obj: CMakeFiles/game.dir/includes_CXX.rsp
CMakeFiles/game.dir/src/camera.cpp.obj: C:/Users/Sam/Desktop/PlayThrough/src/camera.cpp
CMakeFiles/game.dir/src/camera.cpp.obj: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/game.dir/src/camera.cpp.obj"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/camera.cpp.obj -MF CMakeFiles\game.dir\src\camera.cpp.obj.d -o CMakeFiles\game.dir\src\camera.cpp.obj -c C:\Users\Sam\Desktop\PlayThrough\src\camera.cpp

CMakeFiles/game.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/game.dir/src/camera.cpp.i"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sam\Desktop\PlayThrough\src\camera.cpp > CMakeFiles\game.dir\src\camera.cpp.i

CMakeFiles/game.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/camera.cpp.s"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Sam\Desktop\PlayThrough\src\camera.cpp -o CMakeFiles\game.dir\src\camera.cpp.s

CMakeFiles/game.dir/src/gl.c.obj: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/gl.c.obj: CMakeFiles/game.dir/includes_C.rsp
CMakeFiles/game.dir/src/gl.c.obj: C:/Users/Sam/Desktop/PlayThrough/src/gl.c
CMakeFiles/game.dir/src/gl.c.obj: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/game.dir/src/gl.c.obj"
	C:\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/game.dir/src/gl.c.obj -MF CMakeFiles\game.dir\src\gl.c.obj.d -o CMakeFiles\game.dir\src\gl.c.obj -c C:\Users\Sam\Desktop\PlayThrough\src\gl.c

CMakeFiles/game.dir/src/gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/game.dir/src/gl.c.i"
	C:\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Sam\Desktop\PlayThrough\src\gl.c > CMakeFiles\game.dir\src\gl.c.i

CMakeFiles/game.dir/src/gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/game.dir/src/gl.c.s"
	C:\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Sam\Desktop\PlayThrough\src\gl.c -o CMakeFiles\game.dir\src\gl.c.s

CMakeFiles/game.dir/src/main.cpp.obj: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/main.cpp.obj: CMakeFiles/game.dir/includes_CXX.rsp
CMakeFiles/game.dir/src/main.cpp.obj: C:/Users/Sam/Desktop/PlayThrough/src/main.cpp
CMakeFiles/game.dir/src/main.cpp.obj: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/game.dir/src/main.cpp.obj"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/main.cpp.obj -MF CMakeFiles\game.dir\src\main.cpp.obj.d -o CMakeFiles\game.dir\src\main.cpp.obj -c C:\Users\Sam\Desktop\PlayThrough\src\main.cpp

CMakeFiles/game.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/game.dir/src/main.cpp.i"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sam\Desktop\PlayThrough\src\main.cpp > CMakeFiles\game.dir\src\main.cpp.i

CMakeFiles/game.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/main.cpp.s"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Sam\Desktop\PlayThrough\src\main.cpp -o CMakeFiles\game.dir\src\main.cpp.s

CMakeFiles/game.dir/src/objectGenerator.cpp.obj: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/objectGenerator.cpp.obj: CMakeFiles/game.dir/includes_CXX.rsp
CMakeFiles/game.dir/src/objectGenerator.cpp.obj: C:/Users/Sam/Desktop/PlayThrough/src/objectGenerator.cpp
CMakeFiles/game.dir/src/objectGenerator.cpp.obj: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/game.dir/src/objectGenerator.cpp.obj"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/objectGenerator.cpp.obj -MF CMakeFiles\game.dir\src\objectGenerator.cpp.obj.d -o CMakeFiles\game.dir\src\objectGenerator.cpp.obj -c C:\Users\Sam\Desktop\PlayThrough\src\objectGenerator.cpp

CMakeFiles/game.dir/src/objectGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/game.dir/src/objectGenerator.cpp.i"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sam\Desktop\PlayThrough\src\objectGenerator.cpp > CMakeFiles\game.dir\src\objectGenerator.cpp.i

CMakeFiles/game.dir/src/objectGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/objectGenerator.cpp.s"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Sam\Desktop\PlayThrough\src\objectGenerator.cpp -o CMakeFiles\game.dir\src\objectGenerator.cpp.s

CMakeFiles/game.dir/src/shaders.cpp.obj: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/shaders.cpp.obj: CMakeFiles/game.dir/includes_CXX.rsp
CMakeFiles/game.dir/src/shaders.cpp.obj: C:/Users/Sam/Desktop/PlayThrough/src/shaders.cpp
CMakeFiles/game.dir/src/shaders.cpp.obj: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/game.dir/src/shaders.cpp.obj"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/shaders.cpp.obj -MF CMakeFiles\game.dir\src\shaders.cpp.obj.d -o CMakeFiles\game.dir\src\shaders.cpp.obj -c C:\Users\Sam\Desktop\PlayThrough\src\shaders.cpp

CMakeFiles/game.dir/src/shaders.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/game.dir/src/shaders.cpp.i"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sam\Desktop\PlayThrough\src\shaders.cpp > CMakeFiles\game.dir\src\shaders.cpp.i

CMakeFiles/game.dir/src/shaders.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/shaders.cpp.s"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Sam\Desktop\PlayThrough\src\shaders.cpp -o CMakeFiles\game.dir\src\shaders.cpp.s

CMakeFiles/game.dir/src/shapeData.cpp.obj: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/shapeData.cpp.obj: CMakeFiles/game.dir/includes_CXX.rsp
CMakeFiles/game.dir/src/shapeData.cpp.obj: C:/Users/Sam/Desktop/PlayThrough/src/shapeData.cpp
CMakeFiles/game.dir/src/shapeData.cpp.obj: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/game.dir/src/shapeData.cpp.obj"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/shapeData.cpp.obj -MF CMakeFiles\game.dir\src\shapeData.cpp.obj.d -o CMakeFiles\game.dir\src\shapeData.cpp.obj -c C:\Users\Sam\Desktop\PlayThrough\src\shapeData.cpp

CMakeFiles/game.dir/src/shapeData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/game.dir/src/shapeData.cpp.i"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sam\Desktop\PlayThrough\src\shapeData.cpp > CMakeFiles\game.dir\src\shapeData.cpp.i

CMakeFiles/game.dir/src/shapeData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/shapeData.cpp.s"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Sam\Desktop\PlayThrough\src\shapeData.cpp -o CMakeFiles\game.dir\src\shapeData.cpp.s

CMakeFiles/game.dir/src/shapeGenerator.cpp.obj: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/shapeGenerator.cpp.obj: CMakeFiles/game.dir/includes_CXX.rsp
CMakeFiles/game.dir/src/shapeGenerator.cpp.obj: C:/Users/Sam/Desktop/PlayThrough/src/shapeGenerator.cpp
CMakeFiles/game.dir/src/shapeGenerator.cpp.obj: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/game.dir/src/shapeGenerator.cpp.obj"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/shapeGenerator.cpp.obj -MF CMakeFiles\game.dir\src\shapeGenerator.cpp.obj.d -o CMakeFiles\game.dir\src\shapeGenerator.cpp.obj -c C:\Users\Sam\Desktop\PlayThrough\src\shapeGenerator.cpp

CMakeFiles/game.dir/src/shapeGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/game.dir/src/shapeGenerator.cpp.i"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sam\Desktop\PlayThrough\src\shapeGenerator.cpp > CMakeFiles\game.dir\src\shapeGenerator.cpp.i

CMakeFiles/game.dir/src/shapeGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/shapeGenerator.cpp.s"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Sam\Desktop\PlayThrough\src\shapeGenerator.cpp -o CMakeFiles\game.dir\src\shapeGenerator.cpp.s

CMakeFiles/game.dir/src/window.cpp.obj: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/window.cpp.obj: CMakeFiles/game.dir/includes_CXX.rsp
CMakeFiles/game.dir/src/window.cpp.obj: C:/Users/Sam/Desktop/PlayThrough/src/window.cpp
CMakeFiles/game.dir/src/window.cpp.obj: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/game.dir/src/window.cpp.obj"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/window.cpp.obj -MF CMakeFiles\game.dir\src\window.cpp.obj.d -o CMakeFiles\game.dir\src\window.cpp.obj -c C:\Users\Sam\Desktop\PlayThrough\src\window.cpp

CMakeFiles/game.dir/src/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/game.dir/src/window.cpp.i"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sam\Desktop\PlayThrough\src\window.cpp > CMakeFiles\game.dir\src\window.cpp.i

CMakeFiles/game.dir/src/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/window.cpp.s"
	C:\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Sam\Desktop\PlayThrough\src\window.cpp -o CMakeFiles\game.dir\src\window.cpp.s

# Object files for target game
game_OBJECTS = \
"CMakeFiles/game.dir/src/app.cpp.obj" \
"CMakeFiles/game.dir/src/camera.cpp.obj" \
"CMakeFiles/game.dir/src/gl.c.obj" \
"CMakeFiles/game.dir/src/main.cpp.obj" \
"CMakeFiles/game.dir/src/objectGenerator.cpp.obj" \
"CMakeFiles/game.dir/src/shaders.cpp.obj" \
"CMakeFiles/game.dir/src/shapeData.cpp.obj" \
"CMakeFiles/game.dir/src/shapeGenerator.cpp.obj" \
"CMakeFiles/game.dir/src/window.cpp.obj"

# External object files for target game
game_EXTERNAL_OBJECTS =

C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/src/app.cpp.obj
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/src/camera.cpp.obj
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/src/gl.c.obj
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/src/main.cpp.obj
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/src/objectGenerator.cpp.obj
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/src/shaders.cpp.obj
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/src/shapeData.cpp.obj
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/src/shapeGenerator.cpp.obj
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/src/window.cpp.obj
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/build.make
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: C:/Users/Sam/Desktop/PlayThrough/lib/libassimp.dll.a
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: C:/Users/Sam/Desktop/PlayThrough/lib/libSDL3.dll.a
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: C:/Users/Sam/Desktop/PlayThrough/lib/libSDL3_image.dll.a
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: C:/Users/Sam/Desktop/PlayThrough/lib/libSDL2_mixer.dll.a
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: C:/Users/Sam/Desktop/PlayThrough/lib/libSDL3_ttf.dll.a
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/linkLibs.rsp
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/objects1.rsp
C:/Users/Sam/Desktop/PlayThrough/bin/game.exe: CMakeFiles/game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable C:\Users\Sam\Desktop\PlayThrough\bin\game.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\game.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game.dir/build: C:/Users/Sam/Desktop/PlayThrough/bin/game.exe
.PHONY : CMakeFiles/game.dir/build

CMakeFiles/game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\game.dir\cmake_clean.cmake
.PHONY : CMakeFiles/game.dir/clean

CMakeFiles/game.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Sam\Desktop\PlayThrough C:\Users\Sam\Desktop\PlayThrough C:\Users\Sam\Desktop\PlayThrough\build C:\Users\Sam\Desktop\PlayThrough\build C:\Users\Sam\Desktop\PlayThrough\build\CMakeFiles\game.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/game.dir/depend

