
https://developer.arm.com/documentation/ddi0403/d/System-Level-Architecture/System-Level-Programmers--Model/Registers/The-ARM-core-registers

opis czemu są w stosy
https://electronics.stackexchange.com/questions/403967/main-stack-pointermsp-vs-process-stack-pointerpsp

https://bitbucket.org/csowter/redkernel/src/master/


## tryby pracy procesoar i poziomy uprzywilejowania

![[Pasted image 20241123115937.png]]

### rejestr sp (stack pointer)

armv7 posiada 2 stosy
- **Main stack**, MSP (SP_main)
- **Process stack**, PSP (SP_process)

Aktualny stos zależy od trybu;
 - w trybie thread, rejestr CONTROL kontroluje czy procesor używa **main stack** lub **process stack** (1 bit rejestru CONTROL, 0: MSP, 1: PSP)
 - w trybie handler processor zawsze używa **main stack**

istnieją 2 stosy aby system operacyjny łatwo implementował multi tasking. kernel używa MSP, PSP używany jest przez procesy. 

Jak występuje wyjątek, ramka stosu(rejestry które powinny byc zachowane) wrzucana jest na stos, następnie przełącza sie na MSP.
W systemach wielotaskowych jeśli scheduler wywołał wyjątek

**the MSP points to the stack used for _interrupts_, and the PSP points to the stack used by the regular program code.**


![[Pasted image 20241123120427.png]]



![[Pasted image 20241123122336.png]]

kernel: thread mode, privileged mode and msp
aplikacja: thread mode, unprivileged mode and psp
wyjątki: handler mode, privileged mode, msp


![[Pasted image 20241123130739.png]]

![[Pasted image 20241123130942.png]]
https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf#page=206&zoom=100,165,556
rejestry mpu



Wyjątek PendSV
https://developer.arm.com/documentation/107706/0100/System-exceptions/Pended-SVC---PendSV

![[Pasted image 20241123031714.png]]

![[Pasted image 20241123031639.png]]


przykład 
https://github.com/ARM-software/m-profile-user-guide-examples/tree/main/Memory_model/rtos_context_switch



# instrukcja svc

SVC 1

wartość która podawana jest do instrukcji svc jest kodowana w samej instruckji. Nie jest ona zapisaywana na stosie czy w rejestrze. Adress instrukcji zapisywany jest na stosie w Polu PC, 

https://www.eng.auburn.edu/~nelson/courses/elec5260_6260/slides/ARM%20STM32F476%20Interrupts.pdf

![[Pasted image 20241124133703.png]]

![[Pasted image 20241130193757.png]]

![[Pasted image 20241130193808.png]]

![[Pasted image 20241201143346.png]]

# Context switching

https://interrupt.memfault.com/blog/arm-cortex-m-exceptions-and-nvic#built-in-exceptions
https://interrupt.memfault.com/blog/cortex-m-rtos-context-switching
the **context switch** occurs when the current task is paused and the processor switches to a different task

A context switch involves saving the processor's state (registers, program counter, and stack pointer) and loading the state of another task. This can be done in the **PendSV exception** (which is designed for context switching in ARM Cortex-M microcontrollers) or through a manual interrupt mechanism.

#### **Context Switch Steps**:

1. **Save the Current Task's Context**:
    - This includes saving the **register values** (R4 to R11, LR, PC, and xPSR) and the **stack pointer (PSP)** to memory.


![[Pasted image 20241124133857.png]]![[Pasted image 20241124133937.png]]

pendSV musi miec najmniejszy priorytet aby nie było problemów z innymi przerwaniami. po systicku (z najwiekszym priorytetem) wykonywane są poprzednie przerwania, a na końcu wykonywane jest przerwanie pendsv z context switchem

![[Pasted image 20241124170628.png]]


systick zapisuje r0-r3 r12 lr pc xpsr, pendsv musi zapisac r4-r11. aby zapisać cały konetks tasku. 