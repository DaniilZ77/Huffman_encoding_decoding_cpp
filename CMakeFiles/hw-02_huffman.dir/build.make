# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman

# Include any dependencies generated for this target.
include CMakeFiles/hw-02_huffman.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/hw-02_huffman.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hw-02_huffman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw-02_huffman.dir/flags.make

CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.o: CMakeFiles/hw-02_huffman.dir/flags.make
CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.o: src/huffman_archiver.cpp
CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.o: CMakeFiles/hw-02_huffman.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.o -MF CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.o.d -o CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.o -c /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/huffman_archiver.cpp

CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/huffman_archiver.cpp > CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.i

CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/huffman_archiver.cpp -o CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.s

CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.o: CMakeFiles/hw-02_huffman.dir/flags.make
CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.o: src/huffman_tree_node.cpp
CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.o: CMakeFiles/hw-02_huffman.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.o -MF CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.o.d -o CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.o -c /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/huffman_tree_node.cpp

CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/huffman_tree_node.cpp > CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.i

CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/huffman_tree_node.cpp -o CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.s

CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.o: CMakeFiles/hw-02_huffman.dir/flags.make
CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.o: src/huffman_tree.cpp
CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.o: CMakeFiles/hw-02_huffman.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.o -MF CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.o.d -o CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.o -c /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/huffman_tree.cpp

CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/huffman_tree.cpp > CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.i

CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/huffman_tree.cpp -o CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.s

CMakeFiles/hw-02_huffman.dir/src/main.cpp.o: CMakeFiles/hw-02_huffman.dir/flags.make
CMakeFiles/hw-02_huffman.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/hw-02_huffman.dir/src/main.cpp.o: CMakeFiles/hw-02_huffman.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/hw-02_huffman.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hw-02_huffman.dir/src/main.cpp.o -MF CMakeFiles/hw-02_huffman.dir/src/main.cpp.o.d -o CMakeFiles/hw-02_huffman.dir/src/main.cpp.o -c /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/main.cpp

CMakeFiles/hw-02_huffman.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/hw-02_huffman.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/main.cpp > CMakeFiles/hw-02_huffman.dir/src/main.cpp.i

CMakeFiles/hw-02_huffman.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/hw-02_huffman.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/src/main.cpp -o CMakeFiles/hw-02_huffman.dir/src/main.cpp.s

# Object files for target hw-02_huffman
hw__02_huffman_OBJECTS = \
"CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.o" \
"CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.o" \
"CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.o" \
"CMakeFiles/hw-02_huffman.dir/src/main.cpp.o"

# External object files for target hw-02_huffman
hw__02_huffman_EXTERNAL_OBJECTS =

hw-02_huffman: CMakeFiles/hw-02_huffman.dir/src/huffman_archiver.cpp.o
hw-02_huffman: CMakeFiles/hw-02_huffman.dir/src/huffman_tree_node.cpp.o
hw-02_huffman: CMakeFiles/hw-02_huffman.dir/src/huffman_tree.cpp.o
hw-02_huffman: CMakeFiles/hw-02_huffman.dir/src/main.cpp.o
hw-02_huffman: CMakeFiles/hw-02_huffman.dir/build.make
hw-02_huffman: CMakeFiles/hw-02_huffman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable hw-02_huffman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw-02_huffman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw-02_huffman.dir/build: hw-02_huffman
.PHONY : CMakeFiles/hw-02_huffman.dir/build

CMakeFiles/hw-02_huffman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw-02_huffman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw-02_huffman.dir/clean

CMakeFiles/hw-02_huffman.dir/depend:
	cd /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman /Users/daniilzolin/Desktop/MyRepository/labs-zolin/hw-02_huffman/CMakeFiles/hw-02_huffman.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/hw-02_huffman.dir/depend

