#include "gpio.h"
#include "rcc.h"
#include <sys/types.h>

void gpio_set_mode(uint16_t pin, gpio_mode mode) {
  struct gpio *gpio = GPIO(PINBANK(pin));
  uint8_t pinno = PINNO(pin);
  RCC->AHB1ENR |= BIT(PINBANK(pin)); // Enable GPIO clock
  gpio->MODER &= ~(3U << (pinno * 2));
  gpio->MODER |= (mode & 3) << (pinno * 2);
}

// usart2 alternate function maping pa2 = tx pa3 = rx
// usart2 is on af7
void gpio_set_af(uint16_t pin, uint8_t af) {
  struct gpio *gpio = GPIO(PINBANK(pin));
  uint8_t pinno = PINNO(pin);
  gpio->AFR[pinno >> 3] &= ~(15UL << ((pinno & 7) * 4));
  gpio->AFR[pinno >> 3] |= ((uint32_t)af) << ((pinno & 7) * 4);
}

void gpio_write(uint16_t pin, bool val) {
  struct gpio *gpio = GPIO(PINBANK(pin));
  gpio->BSRR = (1U << PINNO(pin)) << (val ? 0 : 16);
}

uint8_t gpio_read(uint16_t pin) {
  struct gpio *gpio = GPIO(PINBANK(pin));
  return (gpio->IDR >> PINNO(pin)) & 1;
}