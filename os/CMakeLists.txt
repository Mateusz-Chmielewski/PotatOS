cmake_minimum_required(VERSION 3.16)

project(PotatOS VERSION 1.0.0 LANGUAGES ASM C CXX)

# Use arm-none-eabi toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_LINKER arm-none-eabi-ld)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_NM arm-none-eabi-nm)
set(CMAKE_STRIP arm-none-eabi-strip)
set(CMAKE_RANLIB arm-none-eabi-ranlib)

# Set the target MCU and architecture
set(MCU_ARCH  cortex-m4)
set(STM32_MCU "STM32F405xx")

# Linker directory
set(LINKER      "${CMAKE_CURRENT_SOURCE_DIR}/kernel/link.ld")

# Source files
set(SOURCES
    kernel/src/main.c
    kernel/src/startup.c
    drivers/src/systick.c
    drivers/src/uart.c
    drivers/src/gpio.c
    drivers/src/rcc.c
    drivers/src/vector.c
    drivers/src/ringbuffer.c
)

# Include directories
include_directories(
  ${CMAKE_SOURCE_DIR}/kernel/inc
  ${CMAKE_SOURCE_DIR}/drivers/inc
)

# Compiler flags
set(CMAKE_C_FLAGS "-Wall -Wextra -mcpu=${MCU_ARCH} -D${STM32_MCU} -g -nostdlib")
set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER} -Wl,-Map=firmware.map")

# Output the firmware.elf binary
add_executable(firmware.elf ${SOURCES})

# Post-build step to create firmware.bin
add_custom_command(
    TARGET firmware.elf POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
    COMMENT "Creating firmware.bin"
)

# QEMU run target (with graphics)
add_custom_target(rung
    COMMAND qemu-system-arm -M netduinoplus2 -kernel firmware.bin
    DEPENDS firmware.bin
    COMMENT "Running firmware.bin in QEMU with graphics"
)

# QEMU run target (no graphics)
add_custom_target(run
    COMMAND qemu-system-arm -M netduinoplus2 -nographic -kernel firmware.bin
    DEPENDS firmware.bin
    COMMENT "Running firmware.bin in QEMU without graphics"
)

# QEMU run target (debugging)
add_custom_target(rundbg
    COMMAND qemu-system-arm -M netduinoplus2 -s -S -kernel firmware.elf
    DEPENDS firmware.elf
    COMMENT "Running firmware.elf in QEMU with debugging enabled"
)

# Clean target
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "firmware.bin;firmware.elf;firmware.map")
