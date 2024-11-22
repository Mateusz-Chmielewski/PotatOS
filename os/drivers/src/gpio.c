#include "gpio.h"

void gpio_set_mode(uint16_t pin, gpio_mode mode)
{
  struct gpio *gpio = GPIO(PINBANK(pin));
  uint8_t pinno = PINNO(pin);
  gpio->MODER &= ~(3 << (pinno * 2));
  gpio->MODER |= (mode & 3) << (pinno * 2);
}

// usart2 alternate function maping pa2 = tx pa3 = rx
// usart2 is on af7
void gpio_set_af(uint16_t pin, uint8_t af)
{
  struct gpio *gpio = GPIO(PINBANK(pin));
  uint8_t pinno = PINNO(pin);
  gpio->AFR[pinno / 8] &= ~(0xf << ((pinno & 7) * 4));
  gpio->AFR[pinno / 8] |= ((uint32_t)af) << ((pinno & 7) * 4);
}