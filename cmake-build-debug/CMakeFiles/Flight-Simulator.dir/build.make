# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/clion/98/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/98/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shani/CLionProjects/Flight-Simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shani/CLionProjects/Flight-Simulator/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Flight-Simulator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Flight-Simulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Flight-Simulator.dir/flags.make

CMakeFiles/Flight-Simulator.dir/main.cpp.o: CMakeFiles/Flight-Simulator.dir/flags.make
CMakeFiles/Flight-Simulator.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shani/CLionProjects/Flight-Simulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Flight-Simulator.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Flight-Simulator.dir/main.cpp.o -c /home/shani/CLionProjects/Flight-Simulator/main.cpp

CMakeFiles/Flight-Simulator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Flight-Simulator.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shani/CLionProjects/Flight-Simulator/main.cpp > CMakeFiles/Flight-Simulator.dir/main.cpp.i

CMakeFiles/Flight-Simulator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Flight-Simulator.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shani/CLionProjects/Flight-Simulator/main.cpp -o CMakeFiles/Flight-Simulator.dir/main.cpp.s

# Object files for target Flight-Simulator
Flight__Simulator_OBJECTS = \
"CMakeFiles/Flight-Simulator.dir/main.cpp.o"

# External object files for target Flight-Simulator
Flight__Simulator_EXTERNAL_OBJECTS =

Flight-Simulator: CMakeFiles/Flight-Simulator.dir/main.cpp.o
Flight-Simulator: CMakeFiles/Flight-Simulator.dir/build.make
Flight-Simulator: CMakeFiles/Flight-Simulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shani/CLionProjects/Flight-Simulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Flight-Simulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Flight-Simulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Flight-Simulator.dir/build: Flight-Simulator

.PHONY : CMakeFiles/Flight-Simulator.dir/build

CMakeFiles/Flight-Simulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Flight-Simulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Flight-Simulator.dir/clean

CMakeFiles/Flight-Simulator.dir/depend:
	cd /home/shani/CLionProjects/Flight-Simulator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shani/CLionProjects/Flight-Simulator /home/shani/CLionProjects/Flight-Simulator /home/shani/CLionProjects/Flight-Simulator/cmake-build-debug /home/shani/CLionProjects/Flight-Simulator/cmake-build-debug /home/shani/CLionProjects/Flight-Simulator/cmake-build-debug/CMakeFiles/Flight-Simulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Flight-Simulator.dir/depend

