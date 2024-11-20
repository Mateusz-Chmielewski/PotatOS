
## ARMv7
http://fiona.dmcs.p.lodz.pl/arm/slajdy/slajdy2.pdf

### Rejestry

ARMv7 ma zestaw **16 podstawowych rejestrów widocznych dla programu**, oznaczonych jako **R0–R15**, oraz kilka specjalnych rejestrów do zarządzania stanem procesora. Podstawowy zestaw rejestrów jest podzielony na następujące kategorie:

r0-r12 Rejestry ogólnego przeznaczenia
r11 fp 
r13 sp  - stack pointer, Wskazuje na bieżącą pozycję na stosie.
r14 lr  - link register, Przechowuje adres powrotu do funkcji wywołującej po zakończeniu wykonywania funkcji.
r15 pc  - program counter. Przechowuje adres bieżącej instrukcji lub instrukcji, która ma być wykonana jako następna.
## specjalne
cpsr -  current program status register. Przechowuje bieżący stan procesora.
   Kluczowe pola:
	- **N** (Negative): Wynik operacji arytmetycznej jest ujemny.
	- **Z** (Zero): Wynik operacji wynosi zero.
	- **C** (Carry): Wynik operacji generuje przeniesienie.
	- **V** (Overflow): Wynik operacji powoduje przepełnienie.
	- **M** (Mode): Określa tryb procesora (np. użytkownika, FIQ, IRQ, supervisor).
	- **T** (Thumb): Określa, czy procesor pracuje w trybie Thumb.


Procesor ARM posiada łącznie 37 rejestrów (wszystkie są 32 bitowe) 
Nie wszystkie rejestry są dostępne w różnych trybach uprzywilejowania procesora
W procesorach ARM zastosowano mechanizm bankowania rejestrów. Zmiana trybu pracy procesora powoduje podmienienie części rejestrów. Pozwala to na implementację oddzielnego stosu dla każdego trybu pracy, co znacząco podnosi stabilność systemu. Zmiana trybu pracy odbywa się automatycznie lub przez modyfikację rejestru CPSR (pole Mode)

![[Pasted image 20241119234019.png]]


![[Pasted image 20241119234033.png]]

### **instrukcje ARM i Thumb**
- ARMv7 wspiera dwa zestawy instrukcji:
    - **ARM** – pełny zestaw 32-bitowych instrukcji.
    - **Thumb** – zestaw 16-bitowych instrukcji, które są bardziej skondensowane, co pozwala zaoszczędzić pamięć, kosztem nieco mniejszej wydajności.


# Wyjątki

- Wyjątki dzielimy na:
	 - przerwania (ang. interrupts), 
	 - niepowodzenia (ang. fault),
	 -  błędy nienaprawialne (ang. abort),
	 - pułapki (ang. trap).
	 - 
- Procesory ARM obsługują dwa rodzaje przerwań:
	- FIQ (Fast interrupt) – przerwania z szybką obsługą,
	- IRQ (Interrupt) – przerwania normalne

 - **Przerwanie** (ang. interrupt) lub żądanie przerwania (IRQ – Interrupt ReQuest) – sygnał powodujący zmianę przepływu sterowania, niezależnie od aktualnie wykonywanego programu. Pojawienie się przerwania powoduje wstrzymanie aktualnie wykonywanego programu i wykonanie przez procesor kodu procedury obsługi przerwania, uchwytu przerwania (ang. interrupt handler)

- W procesorach ARM wystąpienie przerwania powoduje ustawienie flagi w rejestrze statusowym sygnalizującej żądanie obsługi przerwania. Jeżeli system przerwań jest aktywny (rdzeń procesora) oraz dane przerwanie nie jest zamaskowane (sterownik przerwań) następuje przyjęcie przerwania przez procesor - skok do programu obsługującego przerwanie

- Wykonanie niedozwolonej operacji przez procesor w danym stanie uprzywilejowania powoduje wygenerowanie wyjątku.

## Model programowy – dostępne tryby pracy procesora

**Tryb pracy procesora (operating mode), tryb ochrony** - określa jakie zasoby procesora są dostępne, np. dostępne rejestry, obszary pamięci, urządzenia peryferyjne.

### Procesory ARM mogą pracować w jednym z siedmiu trybów pracy: 

**User** – tryb użytkownika (nieuprzywilejowany) przeznaczony do wykonywania programów użytkownika, brak dostępu blokowania przerwań
**FIQ** – tryb obsługujący przerwania i wyjątki o wysokich priorytetach (szybki) – wykorzystywany do obsługi czasowo krytycznych przerwań (operacje czasu rzeczywistego)
**IRQ** – obsługa przerwań z niskim prirytetem (low/normal priority)
**Supervisor** – tryb pracy superużytkownika, dostęp do wszystkich zasobów procesora (dostępny po resecie lub przerwanie programowe), przerwania programowe (instrukcja SWI)
**Abort** – obsługa wyjątków związanych z pamięcią (memory access violations)
**Undef** (undifined mode)– obsługa nieznanych/błędnych rozkazów
**System** – tryb pracy superużytkownika, dostęp do rejestrów takich jak w trybie User jednak możliwy dostęp do różnych obszarów pamięci – wykorzystywany przez system operacyjny


# ARMv7 vs ARMv8
 - **ARMv8** wprowadza wsparcie dla **64-bitowego trybu pracy** AArch64 (64-bit) 
	-   Został wprowadzony tryb **AArch64**, który umożliwia przetwarzanie 64-bitowych instrukcji i adresów pamięci.
	- ARMv8 pozostaje kompatybilne z trybem 32-bitowym **AArch32**, który działa tak samo, jak w **ARMv7**.
 - **ARMv8** oferuje **wbudowane wsparcie dla wirtualizacji**
 - Nowy model uprzywilejowania (Exception Levels - EL)
	-  **Poziom EL0** – Aplikacje użytkownika działają w tym trybie (tak jak tryb **User** w ARMv7).
	- **Poziom EL1** – System operacyjny (jądro) działa w tym trybie, z pełnym dostępem do zasobów sprzętowych.
	- **Poziom EL2** – Hyperwizor do zarządzania wirtualizacją. ARMv8 wprowadza wsparcie dla **wirtualizacji**, umożliwiając uruchamianie maszyn wirtualnych.
	- **Poziom EL3** – Monitor bezpieczeństwa (np. ARM **TrustZone**), zarządzający przełączaniem między światem zaufanym i niezaufanym.
 - Nowe instrukcje i rozszerzenia
	 - **Advanced SIMD** i **NEON** (optymalizowane do obliczeń wektorowych i multimedialnych)
	 - **AES (Advanced Encryption Standard)**, **SHA-1/2** oraz inne **instrukcje kryptograficzne** zostały dodane w celu przyspieszenia operacji szyfrowania i haszowania.
- Zwiększenie liczby rejestrów
	- **ARMv8** wprowadza **32 64-bitowe rejestry ogólnego przeznaczenia**


## cross-kompilator
sudo apt install gcc-arm-none-eabi

arm-none-eabi-gcc -mcpu=cortex-m4 main.c -c 
arm-none-eabi-gcc -T link.ld -nostdlib main.o -o firmware.elf
arm-none-eabi-objcopy -O binary firmware.elf firmware.bin

wyświetlenie segmentów pliku elf:
arm-none-eabi-objdump -h firmware.elf


# Przestrzeń adresowa
32-bitowa przestrzeń adresowa, podzielona jest na regiony. Przy bootowaniu pamięć flash mapowana jest na adres 0x0000 0000  (dla opcji bootowania wybranej na Main flash memory).
#### mapowanie adresów w zależności od trybu bootowania
![[Pasted image 20241117160010.png]]

### opcje bootowania
![[Pasted image 20241117160427.png]]

### pamięć ram (str.68 Ref man.)
pamięć ram zaczyna się od 0x20000000 i ma rozmiar 192 kb (64 zarezerwowanie, niedostepne)

0x2001 C000 - 0x2001 FFFF SRAM2 (16 KB)
0x2000 0000 - 0x2001 BFFF SRAM1 (112 KB) 

### pamięć flash
pamięć flash znajduje się pod adresem 0x08000000 i ma rozmiar 1mb
0x0800 0000 - 0x080F FFFF - Flash memory
0x0000 0000 - 0x000F FFFF - Flash (1 MB) Aliased - mapowana przy uruchamiu


### Inne regiony pamięci: (Rozdział 2.3 Memory map)
https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#page=64

Można odczytać z tabelki region np GPIOA 0x4002 0000 - 0x4002 03FF

obszar pamięci wskazuje na paryferium w mcu, obszar pamięci składa się z 32bit restrów, każdy rejestr mapuje do konkretnej funkcji preryferium. Wpisując do odpowiendnich rejestrów peryferiów (32-bit wartości pod danym adressem) możemy wpływać, jak dane peryferium powinno się zachowywać. Odczytujący rejestry peryferiów możemy odczytać od nich dane lub konfiguracje. czyli pisanie pod jakiś obszar pamięći wpływa na peryferium mcu. np można zmienić stan pinów przez gpio 



# skrypt linkera

## segmenty

- .text - segment z kodem. Zawiera wykonywalny kod programu. jest read only. przechowywany jest w pamięci flash. Gdy program jest uruchomiony procesor bezpośrednio pobiera instrukcje z pamięci flash

- .data zawiera zmienne globalne i statyczne które są zainicjalizowane.  Zawiera dane które program może modyfikować w trakcie działania

- .rodata (czasami połączony z .text), zawiera dane które nie mogą być modyfikowane w trakcie działania programu, czyli poprosu const'y.

- .bss  segment z danymi nie zainicjalizowanymi. Zmienne globalne które nie są zainicjalizowane trafiają tu. Trafia do ramu

W arm oprogramowanie musi skopiować segment .data do ramu i wyczyścić segment .bss
funcja startu kopiuje segment .data do ramu, inicjalizuje segment .bss zerami


![[Pasted image 20241118230606.png]]

## MCU boot and vector table
- kiedy arm mcu bootuje się czyta vector table z początku pamięci flash
- vector table:
  - to tablica składająca się z 32-bitowych adresów podprogramów(funkcji) obsługi przerwań
  - 16 pierwszych pozycji jest zarezerwowane dla arm, są takie same dla wszystkich arm mcu, pozostałe są zależne od danego mcu, są to interrupt handlers peryferiów. prostrze mcu mające miej peryferiów mają miej funkcji przerwań
  - pierwsze dwa, wpisy są ważne dla procesu bootowania
    - początkowy stack pointer
    - adress funkcji bootujące do wykonania 

więc trzeba wpisać do 2 wpisu vector table address naszej funkcji bootującej. Kiedy mcu bootuje się odczyta adress z pamięci flash i skoczy do naszej funkcji bootującej.





## tablica wektorów dla STM32F405RGT6 znajduje się w Table 62. 
https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#page=375

### z datasheetu
82 maskable interrupt channels for STM32F405xx/07xx and STM32F415xx/17xx, and
up to 91 maskable interrupt channels for STM32F42xxx and STM32F43xxx (not
including the 16 interrupt lines of Cortex®-M4 with FPU)

tablica ma 82 wpisy na przerwania peryferiów i 16 zarezerwowanych (czyli 98 razem adresów 32b)




# jakies kody
-czyszczenie bitów 6-7 (ustawienie na 0) 
  * (volatile uint32_t *) (0x40020000 + 0) &= ~(3 << 6);  // CLear bit range 6-7
  ~(3 << 6) - tworzy maske, 
  3 - 000000000011
  3 << 6 000011000000
  ~(3<<6) 111100111111


-ustawienie bitu 6 na 1
  * (volatile uint32_t *) (0x40020000 + 0) |= 1 << 6;     // Set bit range 6-7 to 1



# uart
https://github.com/varun-venkatesh/bare-metal-arm/blob/master/src/chapter2/uart_drv.c#L102

https://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming

https://github.com/jserv/mini-arm-os/blob/master/01-HelloWorld/hello.c


#### opis usart manual
https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#page=969

!ważne
USART bidirectional communication requires a minimum of two pins: Receive Data In (RX)
and Transmit Data Out (TX)

RX: Receive Data Input is the serial data input. Oversampling techniques are used for data
recovery by discriminating between valid incoming data and noise.
TX: Transmit Data Output. When the transmitter is disabled, the output pin returns to its I/O
port configuration. When the transmitter is enabled and nothing is to be transmitted, the TX
pin is at high level. In single-wire and smartcard modes, this I/O is used to transmit and
receive the data (at USART level, data are then received on SW_RX)

##### manual opis rejestrów usart
https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#page=1010

1. Status register (USART_SR) Address offset: 0x00
	Bit 7 TXE: Transmit data register empty

	USART TXE Flag
	 * This flag is cleared when data is written to USARTx_DR and
	 * set when that data is transferred to the TDR
 
1. Data register (USART_DR) Address offset: 0x04. manual strona 1013 wpisujemy tu bajty do wysłania, jak i odbieramy
2. Baud rate register (USART_BRR) ustawiamy prędkość przepływu bitów na sekundę
3. Control register 1 (USART_CR1)
	*(USART2_CR1) = 0x0000000C; ustawia bity Bit 3 TE: Transmitter enable i Bit 2 RE: Receiver enable na 1


# zegar kofiguracja i opis
https://elektronika327.blogspot.com/2016/05/2-stm32f4-rejestry-konfiguracja-zegarow.html

### Rodzaje zegarów

- HSE - (_ang. High Speed External_) - zewnętrzne źródło sygnału. W STM32F4 - Discovery jest to kwarc o częstotliwości 8 MHz.
- HSI - (_ang. High Speed Internal_) - wewnętrzny generator częstotliwości. Częstotliwość wynosi 16 MHz.
- PLL - (_ang. Phase Locked Loop_) - zewnętrzna pętla powielacza częstotliwości. pozwalający na zwiększanie częstotliwości zegara na podstawie wejściowego sygnału HSI lub HSE.
- LSE - (_ang. Low Speed External_) - kwarc zegarowy. jego częstotliwość wynosi 32.768kHz
- LSI - (_ang. Low Speed Internal_) - częstotliwość wynosi od 17 do 37 kHz.

Oprócz źródeł sygnałów występują następujące rodzaje sygnałów zegarowych:
- SYSCLK jest to zegar systemowy, którego maksymalna częstotliwość taktowania wynosi 168 MHz, bez podkręcania, 
- AHB działa z częstotliwością 168MHz, 
- APB2 działa z maksymalną częstotliwością 84 MHz, sterowana z AHB
- APB1 działa z maksymalną częstotliwością 42 MHz, sterowana z AHB

**RCC** (**Reset and Clock Control**)  moduł odpowiedzialny za zarządzanie zegarami i sygnałami resetu dla różnych peryferiów oraz całego systemu. Jest to kluczowy element mikrokontrolera, ponieważ wpływa na jego wydajność, zużycie energii i funkcjonalność.

**Kontrola zasilania peryferiów**:
- RCC pozwala na włączanie i wyłączanie zegarów dla poszczególnych modułów peryferyjnych, co oszczędza energię i minimalizuje zakłócenia elektromagnetyczne.
- Każdy moduł ma dedykowany bit w rejestrach `APBxENR` (lub podobnych), który umożliwia włączenie/wyłączenie jego zegara.


### Typowy przepływ sygnałów zegarowych w STM32:
1. **Źródło zegara (np. HSI, HSE)**: Wybierane jako źródło bazowe.
2. **PLL** (opcjonalnie): Używane do zwiększania częstotliwości zegara.
3. **SYSCLK**: Główny zegar systemowy, który napędza rdzeń i magistrale.
4. **Podział zegara**: SYSCLK jest dzielony na:
    - AHB (rdzeń i pamięć),
    - APB1/APB2 (peryferia),
    - inne sygnały zegarowe (np. dla ADC czy zegara RTC).


### Kluczowe rejestry RCC:
- **CR** (Clock Control Register): Sterowanie włączaniem oscylatorów i PLL.
- **CFGR** (Clock Configuration Register): Konfiguracja źródła zegara systemowego i preskalerów.
- **APB1ENR/APB2ENR/AHBENR**: Włączanie zegarów dla peryferiów.
- **BDCR** (Backup Domain Control Register): Konfiguracja zegara dla RTC.
- **CIR** (Clock Interrupt Register): Zarządzanie przerwaniami związanymi z zegarami.



### Przykład konfiguracji RCC w STM32:

1. **Włączenie zewnętrznego zegara HSE**:
``` c
RCC->CR |= RCC_CR_HSEON; // Włączenie HSE
while (!(RCC->CR & RCC_CR_HSERDY)); // Oczekiwanie na gotowość HSE
```    

2. **Konfiguracja PLL dla uzyskania częstotliwości 72 MHz**:
``` c
RCC->CFGR |= RCC_CFGR_PLLSRC_HSE; // Źródło PLL: HSE
RCC->CFGR |= RCC_CFGR_PLLMUL9;   // Mnożnik PLL: 9 (HSE x 9 = 72 MHz)
RCC->CR |= RCC_CR_PLLON;         // Włączenie PLL
while (!(RCC->CR & RCC_CR_PLLRDY)); // Oczekiwanie na gotowość PLL
```
    
3. **Ustawienie SYSCLK na PLL**:
``` c
RCC->CFGR |= RCC_CFGR_SW_PLL; // Przełączenie zegara systemowego na PLL
while ((RCC->CFGR & RCC_CFGR_SWS)!= RCC_CFGR_SWS_PLL); // Potwierdzenie
```

# SysTick timer (STK)
https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page246

Timer – urządzenie peryferyjne procesora przeznaczone do odmierzania określonych przedziałów czasu (zliczania elementarnych cykli zegarowych). Po odmierzeniu wymaganego okresu czasu timer zwykle generuje przerwanie. Timery wykorzystywane są do odmierzania czasu systemowego, przełączania wątków, generacji opóźnień.

- sprzętowy timer wbudowany w rdzeń procesora
- służy do generowania okresowych przerwań
- często używany do odmierzania czasu, opóźnień

### Źródło zegara
SysTick może działać w oparciu o zegar systemowy (System Clock, np. HCLK) lub podzieloną wersję zegara (HCLK/8). Wybór źródła zegara jest konfigurowalny.
### Konfiguracja 
**Reload Value**: Rejestr `LOAD` określa wartość, do której SysTick będzie odliczał. Kiedy licznik osiągnie zero, generowane jest przerwanie.
**Enable/Disable**: SysTick można włączyć lub wyłączyć za pomocą rejestru `CTRL`.
**Aktualna wartość licznika**: Rejestr `VAL` pozwala sprawdzić bieżący stan licznika.

### Przykład działania:
Jeśli zegar systemowy wynosi 48 MHz, a SysTick jest ustawiony na HCLK/8 (czyli 6 MHz), to wartość `LOAD = 5999` spowoduje generowanie przerwań co 1 ms (6 MHz / 6000 = 1 kHz, czyli 1 ms).

![[Pasted image 20241118230703.png]]


# NVIC

nested vectored interrupt controller. 

włączanie obsługi przerwań od peryferiów, trzeba ustawić odpowiedni bit, przy starcie wszystko jest wyłączone, więc jak chcemy np obsłużyć interrupt uart1 trzeba w rejestrze NVIC_ISER1 ustawić bit 5.  nvic pozwala na ustawienie priorytetów przerwań

informacje o tym znajdują się w programing manualu do m4
https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf


### NVIC Registers Overview

- **NVIC_ISER**X (Interrupt Set-Enable Register): Enables specific interrupts.
    - Each bit in this register corresponds to an IRQ number.
- **NVIC_IPR**X (Interrupt Priority Registers): allow you to set the priority of interrupts. STM32 supports 16 priority levels (though some versions may support fewer)

For **USART1**, the IRQ number (e.g., `USART1_IRQn`) is typically **37** for the STM32F4 series.


http://fiona.dmcs.p.lodz.pl/arm/slajdy/slajdy3.pdf

![[Pasted image 20241119235546.png]]



