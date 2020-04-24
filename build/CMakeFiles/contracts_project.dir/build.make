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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/basarcancelebci/Work/API-market/eosio.contracts

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/basarcancelebci/Work/API-market/eosio.contracts/build

# Utility rule file for contracts_project.

# Include the progress variables for this target.
include CMakeFiles/contracts_project.dir/progress.make

CMakeFiles/contracts_project: CMakeFiles/contracts_project-complete


CMakeFiles/contracts_project-complete: contracts_project-prefix/src/contracts_project-stamp/contracts_project-install
CMakeFiles/contracts_project-complete: contracts_project-prefix/src/contracts_project-stamp/contracts_project-mkdir
CMakeFiles/contracts_project-complete: contracts_project-prefix/src/contracts_project-stamp/contracts_project-download
CMakeFiles/contracts_project-complete: contracts_project-prefix/src/contracts_project-stamp/contracts_project-update
CMakeFiles/contracts_project-complete: contracts_project-prefix/src/contracts_project-stamp/contracts_project-patch
CMakeFiles/contracts_project-complete: contracts_project-prefix/src/contracts_project-stamp/contracts_project-configure
CMakeFiles/contracts_project-complete: contracts_project-prefix/src/contracts_project-stamp/contracts_project-build
CMakeFiles/contracts_project-complete: contracts_project-prefix/src/contracts_project-stamp/contracts_project-install
CMakeFiles/contracts_project-complete: contracts_project-prefix/src/contracts_project-stamp/contracts_project-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'contracts_project'"
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E make_directory /Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E touch /Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles/contracts_project-complete
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E touch /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp/contracts_project-done

contracts_project-prefix/src/contracts_project-stamp/contracts_project-install: contracts_project-prefix/src/contracts_project-stamp/contracts_project-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No install step for 'contracts_project'"
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -E echo_append
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -E touch /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp/contracts_project-install

contracts_project-prefix/src/contracts_project-stamp/contracts_project-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'contracts_project'"
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E make_directory /Users/basarcancelebci/Work/API-market/eosio.contracts/contracts
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E make_directory /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E make_directory /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E make_directory /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/tmp
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E make_directory /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E make_directory /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E make_directory /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E touch /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp/contracts_project-mkdir

contracts_project-prefix/src/contracts_project-stamp/contracts_project-download: contracts_project-prefix/src/contracts_project-stamp/contracts_project-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "No download step for 'contracts_project'"
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E echo_append
	/usr/local/Cellar/cmake/3.15.5/bin/cmake -E touch /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp/contracts_project-download

contracts_project-prefix/src/contracts_project-stamp/contracts_project-update: contracts_project-prefix/src/contracts_project-stamp/contracts_project-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No update step for 'contracts_project'"
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -E echo_append
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -E touch /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp/contracts_project-update

contracts_project-prefix/src/contracts_project-stamp/contracts_project-patch: contracts_project-prefix/src/contracts_project-stamp/contracts_project-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'contracts_project'"
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -E echo_append
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -E touch /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp/contracts_project-patch

contracts_project-prefix/src/contracts_project-stamp/contracts_project-configure: contracts_project-prefix/tmp/contracts_project-cfgcmd.txt
contracts_project-prefix/src/contracts_project-stamp/contracts_project-configure: contracts_project-prefix/src/contracts_project-stamp/contracts_project-update
contracts_project-prefix/src/contracts_project-stamp/contracts_project-configure: contracts_project-prefix/src/contracts_project-stamp/contracts_project-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'contracts_project'"
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -DCMAKE_TOOLCHAIN_FILE=/usr/local/eosio.cdt/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake "-GUnix Makefiles" /Users/basarcancelebci/Work/API-market/eosio.contracts/contracts
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -E touch /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp/contracts_project-configure

contracts_project-prefix/src/contracts_project-stamp/contracts_project-build: contracts_project-prefix/src/contracts_project-stamp/contracts_project-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'contracts_project'"
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts && $(MAKE)

contracts_project-prefix/src/contracts_project-stamp/contracts_project-test: contracts_project-prefix/src/contracts_project-stamp/contracts_project-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "No test step for 'contracts_project'"
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -E echo_append
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts && /usr/local/Cellar/cmake/3.15.5/bin/cmake -E touch /Users/basarcancelebci/Work/API-market/eosio.contracts/build/contracts_project-prefix/src/contracts_project-stamp/contracts_project-test

contracts_project: CMakeFiles/contracts_project
contracts_project: CMakeFiles/contracts_project-complete
contracts_project: contracts_project-prefix/src/contracts_project-stamp/contracts_project-install
contracts_project: contracts_project-prefix/src/contracts_project-stamp/contracts_project-mkdir
contracts_project: contracts_project-prefix/src/contracts_project-stamp/contracts_project-download
contracts_project: contracts_project-prefix/src/contracts_project-stamp/contracts_project-update
contracts_project: contracts_project-prefix/src/contracts_project-stamp/contracts_project-patch
contracts_project: contracts_project-prefix/src/contracts_project-stamp/contracts_project-configure
contracts_project: contracts_project-prefix/src/contracts_project-stamp/contracts_project-build
contracts_project: contracts_project-prefix/src/contracts_project-stamp/contracts_project-test
contracts_project: CMakeFiles/contracts_project.dir/build.make

.PHONY : contracts_project

# Rule to build all files generated by this target.
CMakeFiles/contracts_project.dir/build: contracts_project

.PHONY : CMakeFiles/contracts_project.dir/build

CMakeFiles/contracts_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/contracts_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/contracts_project.dir/clean

CMakeFiles/contracts_project.dir/depend:
	cd /Users/basarcancelebci/Work/API-market/eosio.contracts/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/basarcancelebci/Work/API-market/eosio.contracts /Users/basarcancelebci/Work/API-market/eosio.contracts /Users/basarcancelebci/Work/API-market/eosio.contracts/build /Users/basarcancelebci/Work/API-market/eosio.contracts/build /Users/basarcancelebci/Work/API-market/eosio.contracts/build/CMakeFiles/contracts_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/contracts_project.dir/depend

