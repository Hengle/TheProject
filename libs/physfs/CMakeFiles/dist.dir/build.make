# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/serengeor/Coding/ZombieProject/libs/physfs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/serengeor/Coding/ZombieProject/libs/physfs

# Utility rule file for dist.

# Include the progress variables for this target.
include CMakeFiles/dist.dir/progress.make

CMakeFiles/dist:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/serengeor/Coding/ZombieProject/libs/physfs/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Building source tarball '/home/serengeor/Coding/ZombieProject/libs/physfs/../physfs-2.0.3.tar.bz2'..."
	hg archive -t tbz2 /home/serengeor/Coding/ZombieProject/libs/physfs/../physfs-2.0.3.tar.bz2

dist: CMakeFiles/dist
dist: CMakeFiles/dist.dir/build.make
.PHONY : dist

# Rule to build all files generated by this target.
CMakeFiles/dist.dir/build: dist
.PHONY : CMakeFiles/dist.dir/build

CMakeFiles/dist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dist.dir/clean

CMakeFiles/dist.dir/depend:
	cd /home/serengeor/Coding/ZombieProject/libs/physfs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/serengeor/Coding/ZombieProject/libs/physfs /home/serengeor/Coding/ZombieProject/libs/physfs /home/serengeor/Coding/ZombieProject/libs/physfs /home/serengeor/Coding/ZombieProject/libs/physfs /home/serengeor/Coding/ZombieProject/libs/physfs/CMakeFiles/dist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dist.dir/depend

