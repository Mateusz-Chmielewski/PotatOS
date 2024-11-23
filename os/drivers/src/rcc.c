#include "rcc.h"
#include "common.h"

/*RCC AHB1 */
void rcc_gpioa_enable(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOA;
}

void rcc_gpioa_disable(void)
{
  RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOA;
}

/*RCC APB1 */
void rcc_usart2_enable(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_USART2;
}

void rcc_usart3_enable(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_USART3;
}

void rcc_usart2_disable(void)
{
  RCC->APB1ENR &= ~RCC_APB1ENR_USART2;
}

void rcc_usart3_disable(void)
{
  RCC->APB1ENR &= ~RCC_APB1ENR_USART3;
}

/* RCC APB2 */
void rcc_usart1_enable(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_USART1;
}

void rcc_syscfg_enable(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFG;
}

void rcc_syscfg_disable(void)
{
  RCC->APB2ENR &= ~RCC_APB2ENR_SYSCFG;
}

void rcc_usart1_disable(void)
{
  RCC->APB2ENR &= ~RCC_APB2ENR_USART1;
}