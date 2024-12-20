#ifndef RCC_H
#define RCC_H

#include "common.h"
#include "memorymap.h"
#include <stdint.h>

/*
Reset and Clock Control (RCC)

https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#page=152

*/
struct rcc {
  volatile uint32_t CR, PLLCFGR, CFGR, CIR, AHB1RSTR, AHB2RSTR, AHB3RSTR,
      RESERVED0, APB1RSTR, APB2RSTR, RESERVED1[2], AHB1ENR, AHB2ENR, AHB3ENR,
      RESERVED2, APB1ENR, APB2ENR, RESERVED3[2], AHB1LPENR, AHB2LPENR,
      AHB3LPENR, RESERVED4, APB1LPENR, APB2LPENR, RESERVED5[2], BDCR, CSR,
      RESERVED6[2], SSCGR, PLLI2SCFGR;
};
#define RCC ((struct rcc *)RCC_BASE)

/*
periphal clocks need to be enable, after reset the clock is disabled
*/

// enable functions
/*RCC AHB1 */
void rcc_gpioa_enable(void);

void rcc_gpioa_disable(void);

/*RCC APB1 */
void rcc_usart2_enable(void);
void rcc_usart3_enable(void);

void rcc_usart2_disable(void);
void rcc_usart3_disable(void);

/*RCC APB2 */
void rcc_usart1_enable(void);
void rcc_syscfg_enable(void);

void rcc_usart1_disable(void);
void rcc_syscfg_disable(void);

/*
defines name for the bits positions in registers
*/

/*RCC AHB1 */
#define RCC_AHB1ENR_GPIOA BIT(0)

/*RCC APB1 */
#define RCC_APB1ENR_USART2 BIT(17)
#define RCC_APB1ENR_USART3 BIT(18)

/*RCC APB2 */
#define RCC_APB2ENR_USART1 BIT(4)
#define RCC_APB2ENR_SYSCFG BIT(14)

#endif // RCC_H