# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /home/zxc/app/cmake/cmake-3.28.0-rc4-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/zxc/app/cmake/cmake-3.28.0-rc4-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zxc/MProj/se_rpc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zxc/MProj/se_rpc/build

# Include any dependencies generated for this target.
include threadpool/CMakeFiles/threadpool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include threadpool/CMakeFiles/threadpool.dir/compiler_depend.make

# Include the progress variables for this target.
include threadpool/CMakeFiles/threadpool.dir/progress.make

# Include the compile flags for this target's objects.
include threadpool/CMakeFiles/threadpool.dir/flags.make

threadpool/CMakeFiles/threadpool.dir/Thread.cpp.o: threadpool/CMakeFiles/threadpool.dir/flags.make
threadpool/CMakeFiles/threadpool.dir/Thread.cpp.o: /home/zxc/MProj/se_rpc/threadpool/Thread.cpp
threadpool/CMakeFiles/threadpool.dir/Thread.cpp.o: threadpool/CMakeFiles/threadpool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/zxc/MProj/se_rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object threadpool/CMakeFiles/threadpool.dir/Thread.cpp.o"
	cd /home/zxc/MProj/se_rpc/build/threadpool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT threadpool/CMakeFiles/threadpool.dir/Thread.cpp.o -MF CMakeFiles/threadpool.dir/Thread.cpp.o.d -o CMakeFiles/threadpool.dir/Thread.cpp.o -c /home/zxc/MProj/se_rpc/threadpool/Thread.cpp

threadpool/CMakeFiles/threadpool.dir/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/threadpool.dir/Thread.cpp.i"
	cd /home/zxc/MProj/se_rpc/build/threadpool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zxc/MProj/se_rpc/threadpool/Thread.cpp > CMakeFiles/threadpool.dir/Thread.cpp.i

threadpool/CMakeFiles/threadpool.dir/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/threadpool.dir/Thread.cpp.s"
	cd /home/zxc/MProj/se_rpc/build/threadpool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zxc/MProj/se_rpc/threadpool/Thread.cpp -o CMakeFiles/threadpool.dir/Thread.cpp.s

threadpool/CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.o: threadpool/CMakeFiles/threadpool.dir/flags.make
threadpool/CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.o: /home/zxc/MProj/se_rpc/threadpool/ThreadLoadConfig.cpp
threadpool/CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.o: threadpool/CMakeFiles/threadpool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/zxc/MProj/se_rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object threadpool/CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.o"
	cd /home/zxc/MProj/se_rpc/build/threadpool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT threadpool/CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.o -MF CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.o.d -o CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.o -c /home/zxc/MProj/se_rpc/threadpool/ThreadLoadConfig.cpp

threadpool/CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.i"
	cd /home/zxc/MProj/se_rpc/build/threadpool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zxc/MProj/se_rpc/threadpool/ThreadLoadConfig.cpp > CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.i

threadpool/CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.s"
	cd /home/zxc/MProj/se_rpc/build/threadpool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zxc/MProj/se_rpc/threadpool/ThreadLoadConfig.cpp -o CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.s

threadpool/CMakeFiles/threadpool.dir/ThreadPool.cpp.o: threadpool/CMakeFiles/threadpool.dir/flags.make
threadpool/CMakeFiles/threadpool.dir/ThreadPool.cpp.o: /home/zxc/MProj/se_rpc/threadpool/ThreadPool.cpp
threadpool/CMakeFiles/threadpool.dir/ThreadPool.cpp.o: threadpool/CMakeFiles/threadpool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/zxc/MProj/se_rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object threadpool/CMakeFiles/threadpool.dir/ThreadPool.cpp.o"
	cd /home/zxc/MProj/se_rpc/build/threadpool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT threadpool/CMakeFiles/threadpool.dir/ThreadPool.cpp.o -MF CMakeFiles/threadpool.dir/ThreadPool.cpp.o.d -o CMakeFiles/threadpool.dir/ThreadPool.cpp.o -c /home/zxc/MProj/se_rpc/threadpool/ThreadPool.cpp

threadpool/CMakeFiles/threadpool.dir/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/threadpool.dir/ThreadPool.cpp.i"
	cd /home/zxc/MProj/se_rpc/build/threadpool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zxc/MProj/se_rpc/threadpool/ThreadPool.cpp > CMakeFiles/threadpool.dir/ThreadPool.cpp.i

threadpool/CMakeFiles/threadpool.dir/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/threadpool.dir/ThreadPool.cpp.s"
	cd /home/zxc/MProj/se_rpc/build/threadpool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zxc/MProj/se_rpc/threadpool/ThreadPool.cpp -o CMakeFiles/threadpool.dir/ThreadPool.cpp.s

# Object files for target threadpool
threadpool_OBJECTS = \
"CMakeFiles/threadpool.dir/Thread.cpp.o" \
"CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.o" \
"CMakeFiles/threadpool.dir/ThreadPool.cpp.o"

# External object files for target threadpool
threadpool_EXTERNAL_OBJECTS =

/home/zxc/MProj/se_rpc/lib/libthreadpool.so: threadpool/CMakeFiles/threadpool.dir/Thread.cpp.o
/home/zxc/MProj/se_rpc/lib/libthreadpool.so: threadpool/CMakeFiles/threadpool.dir/ThreadLoadConfig.cpp.o
/home/zxc/MProj/se_rpc/lib/libthreadpool.so: threadpool/CMakeFiles/threadpool.dir/ThreadPool.cpp.o
/home/zxc/MProj/se_rpc/lib/libthreadpool.so: threadpool/CMakeFiles/threadpool.dir/build.make
/home/zxc/MProj/se_rpc/lib/libthreadpool.so: /home/zxc/MProj/se_rpc/lib/liblogger.so
/home/zxc/MProj/se_rpc/lib/libthreadpool.so: threadpool/CMakeFiles/threadpool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/zxc/MProj/se_rpc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library /home/zxc/MProj/se_rpc/lib/libthreadpool.so"
	cd /home/zxc/MProj/se_rpc/build/threadpool && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threadpool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
threadpool/CMakeFiles/threadpool.dir/build: /home/zxc/MProj/se_rpc/lib/libthreadpool.so
.PHONY : threadpool/CMakeFiles/threadpool.dir/build

threadpool/CMakeFiles/threadpool.dir/clean:
	cd /home/zxc/MProj/se_rpc/build/threadpool && $(CMAKE_COMMAND) -P CMakeFiles/threadpool.dir/cmake_clean.cmake
.PHONY : threadpool/CMakeFiles/threadpool.dir/clean

threadpool/CMakeFiles/threadpool.dir/depend:
	cd /home/zxc/MProj/se_rpc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zxc/MProj/se_rpc /home/zxc/MProj/se_rpc/threadpool /home/zxc/MProj/se_rpc/build /home/zxc/MProj/se_rpc/build/threadpool /home/zxc/MProj/se_rpc/build/threadpool/CMakeFiles/threadpool.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : threadpool/CMakeFiles/threadpool.dir/depend

