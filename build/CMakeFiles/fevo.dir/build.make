# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/run/Projects/fastevo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/run/Projects/fastevo/build

# Include any dependencies generated for this target.
include CMakeFiles/fevo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fevo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fevo.dir/flags.make

CMakeFiles/fevo.dir/main.cpp.o: CMakeFiles/fevo.dir/flags.make
CMakeFiles/fevo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/run/Projects/fastevo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fevo.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fevo.dir/main.cpp.o -c /home/run/Projects/fastevo/main.cpp

CMakeFiles/fevo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fevo.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/run/Projects/fastevo/main.cpp > CMakeFiles/fevo.dir/main.cpp.i

CMakeFiles/fevo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fevo.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/run/Projects/fastevo/main.cpp -o CMakeFiles/fevo.dir/main.cpp.s

# Object files for target fevo
fevo_OBJECTS = \
"CMakeFiles/fevo.dir/main.cpp.o"

# External object files for target fevo
fevo_EXTERNAL_OBJECTS =

fevo: CMakeFiles/fevo.dir/main.cpp.o
fevo: CMakeFiles/fevo.dir/build.make
fevo: CMakeFiles/fevo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/run/Projects/fastevo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fevo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fevo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fevo.dir/build: fevo

.PHONY : CMakeFiles/fevo.dir/build

CMakeFiles/fevo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fevo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fevo.dir/clean

CMakeFiles/fevo.dir/depend:
	cd /home/run/Projects/fastevo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/run/Projects/fastevo /home/run/Projects/fastevo /home/run/Projects/fastevo/build /home/run/Projects/fastevo/build /home/run/Projects/fastevo/build/CMakeFiles/fevo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fevo.dir/depend

