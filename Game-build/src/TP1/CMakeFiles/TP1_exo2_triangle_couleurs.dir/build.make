# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fanny/ImacDream/Game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fanny/ImacDream/Game-build

# Include any dependencies generated for this target.
include src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/depend.make

# Include the progress variables for this target.
include src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/progress.make

# Include the compile flags for this target's objects.
include src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/flags.make

src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o: src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/flags.make
src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o: /home/fanny/ImacDream/Game/src/TP1/exo2_triangle_couleurs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fanny/ImacDream/Game-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o"
	cd /home/fanny/ImacDream/Game-build/src/TP1 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o -c /home/fanny/ImacDream/Game/src/TP1/exo2_triangle_couleurs.cpp

src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.i"
	cd /home/fanny/ImacDream/Game-build/src/TP1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fanny/ImacDream/Game/src/TP1/exo2_triangle_couleurs.cpp > CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.i

src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.s"
	cd /home/fanny/ImacDream/Game-build/src/TP1 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fanny/ImacDream/Game/src/TP1/exo2_triangle_couleurs.cpp -o CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.s

src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o.requires:

.PHONY : src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o.requires

src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o.provides: src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o.requires
	$(MAKE) -f src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/build.make src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o.provides.build
.PHONY : src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o.provides

src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o.provides.build: src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o


# Object files for target TP1_exo2_triangle_couleurs
TP1_exo2_triangle_couleurs_OBJECTS = \
"CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o"

# External object files for target TP1_exo2_triangle_couleurs
TP1_exo2_triangle_couleurs_EXTERNAL_OBJECTS =

src/TP1/TP1_exo2_triangle_couleurs: src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o
src/TP1/TP1_exo2_triangle_couleurs: src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/build.make
src/TP1/TP1_exo2_triangle_couleurs: glimac/libglimac.a
src/TP1/TP1_exo2_triangle_couleurs: /usr/lib/x86_64-linux-gnu/libSDLmain.a
src/TP1/TP1_exo2_triangle_couleurs: /usr/lib/x86_64-linux-gnu/libSDL.so
src/TP1/TP1_exo2_triangle_couleurs: /usr/lib/x86_64-linux-gnu/libGL.so.1
src/TP1/TP1_exo2_triangle_couleurs: /usr/lib/x86_64-linux-gnu/libGLEW.so
src/TP1/TP1_exo2_triangle_couleurs: src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fanny/ImacDream/Game-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP1_exo2_triangle_couleurs"
	cd /home/fanny/ImacDream/Game-build/src/TP1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP1_exo2_triangle_couleurs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/build: src/TP1/TP1_exo2_triangle_couleurs

.PHONY : src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/build

src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/requires: src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/exo2_triangle_couleurs.cpp.o.requires

.PHONY : src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/requires

src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/clean:
	cd /home/fanny/ImacDream/Game-build/src/TP1 && $(CMAKE_COMMAND) -P CMakeFiles/TP1_exo2_triangle_couleurs.dir/cmake_clean.cmake
.PHONY : src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/clean

src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/depend:
	cd /home/fanny/ImacDream/Game-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fanny/ImacDream/Game /home/fanny/ImacDream/Game/src/TP1 /home/fanny/ImacDream/Game-build /home/fanny/ImacDream/Game-build/src/TP1 /home/fanny/ImacDream/Game-build/src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/TP1/CMakeFiles/TP1_exo2_triangle_couleurs.dir/depend

