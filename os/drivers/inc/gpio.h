#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "memorymap.h"
#include <stdbool.h>

struct gpio
{
  volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];
};

#define GPIO(bank) ((struct gpio *)(GPIO_BASE + 0x400 * (bank)))

typedef enum
{
  GPIO_MODE_IN = 0,
  GPIO_MODE_OUT = 1,
  GPIO_MODE_AF = 2,
  GPIO_MODE_AN = 3,
} gpio_mode;

// represent pin as 2 byte value
// upper byte is bank, lower byte is pin number
#define PIN(bank, pin) (((bank - 'A') << 8) | (pin))
#define PINNO(pin) (pin & 0xff)   // get lower byte(pin number)
#define PINBANK(pin) ((pin >> 8)) // get upper byte(bank)

void gpio_set_mode(uint16_t pin, gpio_mode mode); // set pin mode
void gpio_set_af(uint16_t pin, uint8_t af);       // set alternate function
void gpio_write(uint16_t pin, bool val);          // set pin to high or low

#endif // GPIO_H