CFLAGS  ?= -Iinc -Wall -Wextra -mcpu=cortex-m4 -g $(EXTRA_CFLAGS)
LDFLAGS ?= -T link.ld -nostdlib -Wl,-Map=firmware.map
SOURCES = src/main.c src/startup.c src/systick.c src/uart.c src/gpio.c src/rcc.c src/vector.c

build: firmware.bin

firmware.elf: $(SOURCES)
	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

rung: firmware.bin
	qemu-system-arm -M netduinoplus2 -kernel firmware.bin

#bez okienka graficznego
run: firmware.bin
	qemu-system-arm -M netduinoplus2 -nographic -kernel firmware.bin

#do debugowania
rundbg: firmware.bin
	qemu-system-arm -M netduinoplus2 -s -S -kernel firmware.elf

clean:
	rm -rf firmware.*