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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build

# Include any dependencies generated for this target.
include CMakeFiles/firmware.elf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/firmware.elf.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/firmware.elf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/firmware.elf.dir/flags.make

CMakeFiles/firmware.elf.dir/kernel/src/main.c.o: CMakeFiles/firmware.elf.dir/flags.make
CMakeFiles/firmware.elf.dir/kernel/src/main.c.o: /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/kernel/src/main.c
CMakeFiles/firmware.elf.dir/kernel/src/main.c.o: CMakeFiles/firmware.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/firmware.elf.dir/kernel/src/main.c.o"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/firmware.elf.dir/kernel/src/main.c.o -MF CMakeFiles/firmware.elf.dir/kernel/src/main.c.o.d -o CMakeFiles/firmware.elf.dir/kernel/src/main.c.o -c /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/kernel/src/main.c

CMakeFiles/firmware.elf.dir/kernel/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/firmware.elf.dir/kernel/src/main.c.i"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/kernel/src/main.c > CMakeFiles/firmware.elf.dir/kernel/src/main.c.i

CMakeFiles/firmware.elf.dir/kernel/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/firmware.elf.dir/kernel/src/main.c.s"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/kernel/src/main.c -o CMakeFiles/firmware.elf.dir/kernel/src/main.c.s

CMakeFiles/firmware.elf.dir/kernel/src/startup.c.o: CMakeFiles/firmware.elf.dir/flags.make
CMakeFiles/firmware.elf.dir/kernel/src/startup.c.o: /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/kernel/src/startup.c
CMakeFiles/firmware.elf.dir/kernel/src/startup.c.o: CMakeFiles/firmware.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/firmware.elf.dir/kernel/src/startup.c.o"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/firmware.elf.dir/kernel/src/startup.c.o -MF CMakeFiles/firmware.elf.dir/kernel/src/startup.c.o.d -o CMakeFiles/firmware.elf.dir/kernel/src/startup.c.o -c /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/kernel/src/startup.c

CMakeFiles/firmware.elf.dir/kernel/src/startup.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/firmware.elf.dir/kernel/src/startup.c.i"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/kernel/src/startup.c > CMakeFiles/firmware.elf.dir/kernel/src/startup.c.i

CMakeFiles/firmware.elf.dir/kernel/src/startup.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/firmware.elf.dir/kernel/src/startup.c.s"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/kernel/src/startup.c -o CMakeFiles/firmware.elf.dir/kernel/src/startup.c.s

CMakeFiles/firmware.elf.dir/drivers/src/systick.c.o: CMakeFiles/firmware.elf.dir/flags.make
CMakeFiles/firmware.elf.dir/drivers/src/systick.c.o: /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/systick.c
CMakeFiles/firmware.elf.dir/drivers/src/systick.c.o: CMakeFiles/firmware.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/firmware.elf.dir/drivers/src/systick.c.o"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/firmware.elf.dir/drivers/src/systick.c.o -MF CMakeFiles/firmware.elf.dir/drivers/src/systick.c.o.d -o CMakeFiles/firmware.elf.dir/drivers/src/systick.c.o -c /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/systick.c

CMakeFiles/firmware.elf.dir/drivers/src/systick.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/firmware.elf.dir/drivers/src/systick.c.i"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/systick.c > CMakeFiles/firmware.elf.dir/drivers/src/systick.c.i

CMakeFiles/firmware.elf.dir/drivers/src/systick.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/firmware.elf.dir/drivers/src/systick.c.s"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/systick.c -o CMakeFiles/firmware.elf.dir/drivers/src/systick.c.s

CMakeFiles/firmware.elf.dir/drivers/src/uart.c.o: CMakeFiles/firmware.elf.dir/flags.make
CMakeFiles/firmware.elf.dir/drivers/src/uart.c.o: /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/uart.c
CMakeFiles/firmware.elf.dir/drivers/src/uart.c.o: CMakeFiles/firmware.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/firmware.elf.dir/drivers/src/uart.c.o"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/firmware.elf.dir/drivers/src/uart.c.o -MF CMakeFiles/firmware.elf.dir/drivers/src/uart.c.o.d -o CMakeFiles/firmware.elf.dir/drivers/src/uart.c.o -c /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/uart.c

CMakeFiles/firmware.elf.dir/drivers/src/uart.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/firmware.elf.dir/drivers/src/uart.c.i"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/uart.c > CMakeFiles/firmware.elf.dir/drivers/src/uart.c.i

CMakeFiles/firmware.elf.dir/drivers/src/uart.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/firmware.elf.dir/drivers/src/uart.c.s"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/uart.c -o CMakeFiles/firmware.elf.dir/drivers/src/uart.c.s

CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.o: CMakeFiles/firmware.elf.dir/flags.make
CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.o: /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/gpio.c
CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.o: CMakeFiles/firmware.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.o"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.o -MF CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.o.d -o CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.o -c /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/gpio.c

CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.i"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/gpio.c > CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.i

CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.s"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/gpio.c -o CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.s

CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.o: CMakeFiles/firmware.elf.dir/flags.make
CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.o: /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/rcc.c
CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.o: CMakeFiles/firmware.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.o"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.o -MF CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.o.d -o CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.o -c /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/rcc.c

CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.i"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/rcc.c > CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.i

CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.s"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/rcc.c -o CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.s

CMakeFiles/firmware.elf.dir/drivers/src/vector.c.o: CMakeFiles/firmware.elf.dir/flags.make
CMakeFiles/firmware.elf.dir/drivers/src/vector.c.o: /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/vector.c
CMakeFiles/firmware.elf.dir/drivers/src/vector.c.o: CMakeFiles/firmware.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/firmware.elf.dir/drivers/src/vector.c.o"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/firmware.elf.dir/drivers/src/vector.c.o -MF CMakeFiles/firmware.elf.dir/drivers/src/vector.c.o.d -o CMakeFiles/firmware.elf.dir/drivers/src/vector.c.o -c /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/vector.c

CMakeFiles/firmware.elf.dir/drivers/src/vector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/firmware.elf.dir/drivers/src/vector.c.i"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/vector.c > CMakeFiles/firmware.elf.dir/drivers/src/vector.c.i

CMakeFiles/firmware.elf.dir/drivers/src/vector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/firmware.elf.dir/drivers/src/vector.c.s"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/vector.c -o CMakeFiles/firmware.elf.dir/drivers/src/vector.c.s

CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.o: CMakeFiles/firmware.elf.dir/flags.make
CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.o: /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/ringbuffer.c
CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.o: CMakeFiles/firmware.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.o"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.o -MF CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.o.d -o CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.o -c /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/ringbuffer.c

CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.i"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/ringbuffer.c > CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.i

CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.s"
	arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/drivers/src/ringbuffer.c -o CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.s

# Object files for target firmware.elf
firmware_elf_OBJECTS = \
"CMakeFiles/firmware.elf.dir/kernel/src/main.c.o" \
"CMakeFiles/firmware.elf.dir/kernel/src/startup.c.o" \
"CMakeFiles/firmware.elf.dir/drivers/src/systick.c.o" \
"CMakeFiles/firmware.elf.dir/drivers/src/uart.c.o" \
"CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.o" \
"CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.o" \
"CMakeFiles/firmware.elf.dir/drivers/src/vector.c.o" \
"CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.o"

# External object files for target firmware.elf
firmware_elf_EXTERNAL_OBJECTS =

firmware.elf: CMakeFiles/firmware.elf.dir/kernel/src/main.c.o
firmware.elf: CMakeFiles/firmware.elf.dir/kernel/src/startup.c.o
firmware.elf: CMakeFiles/firmware.elf.dir/drivers/src/systick.c.o
firmware.elf: CMakeFiles/firmware.elf.dir/drivers/src/uart.c.o
firmware.elf: CMakeFiles/firmware.elf.dir/drivers/src/gpio.c.o
firmware.elf: CMakeFiles/firmware.elf.dir/drivers/src/rcc.c.o
firmware.elf: CMakeFiles/firmware.elf.dir/drivers/src/vector.c.o
firmware.elf: CMakeFiles/firmware.elf.dir/drivers/src/ringbuffer.c.o
firmware.elf: CMakeFiles/firmware.elf.dir/build.make
firmware.elf: CMakeFiles/firmware.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable firmware.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/firmware.elf.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold "Creating firmware.bin"
	arm-none-eabi-objcopy -O binary firmware.elf firmware.bin

# Rule to build all files generated by this target.
CMakeFiles/firmware.elf.dir/build: firmware.elf
.PHONY : CMakeFiles/firmware.elf.dir/build

CMakeFiles/firmware.elf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/firmware.elf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/firmware.elf.dir/clean

CMakeFiles/firmware.elf.dir/depend:
	cd /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build /mnt/c/Users/igors/Desktop/studia/SEM5/OS/PotatOS/os/build/CMakeFiles/firmware.elf.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/firmware.elf.dir/depend

