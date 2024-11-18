
https://www.qemu.org/docs/master/system/arm/stm32.html
netduinoplus2 Netduino Plus 2 board with **STM32F405RGT6** microcontroller 
- używamy **STM32F405RGT6 ARM Cortex-M4F**

### jakieś komendy do odpalania
qemu-system-arm -M netduinoplus2 -nographic -serial mon:stdio -kernel firmware.bin
qemu-system-arm -M netduinoplus2 -nographic -serial /dev/pts/11 -kernel firmware.bin
qemu-system-arm -M netduinoplus2 -kernel firmware.bin
qemu-system-arm -M netduinoplus2 -kernel firmware.elf -serial mon:stdio -serial file:usart2_output.log

ctrl+alt+1/2 -w trybie graficznym przełącza tryby

# tryb monitora

- info registers :wyświetla rejestry (https://rip.hibariya.org/post/show-register-values-of-qemu-emulator/)

## skróty klawiszowe
wyjście: ctrl-A, X
monitor: ctrl-A, C 

# Użycie debugera
- instalacja debugerna na różne architektóry
	sudo apt install gdb-multiarch

-s pozwól na połączenia tcp na porcie 1234
-S freeze mcu

