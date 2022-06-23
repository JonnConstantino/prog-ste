/*
 * Arquivo: adc.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

#include "gpio_pin.h"

GPIO_Pin::GPIO_Registers_t *GPIO_Pin::PortB = (GPIO_Pin::GPIO_Registers_t *) 0x23;
GPIO_Pin::GPIO_Registers_t *GPIO_Pin::PortC = (GPIO_Pin::GPIO_Registers_t *) 0x26;
GPIO_Pin::GPIO_Registers_t *GPIO_Pin::PortD = (GPIO_Pin::GPIO_Registers_t *) 0x29;
