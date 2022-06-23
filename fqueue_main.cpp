/*
 * Arquivo: adc.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

/*
 * Pinagem usada para esta aplicação:
 * LED - PB5 - Arduino 13
 * BTN - PD2 - Arduino 2
 */

#include <avr/interrupt.h>
#include <stdio.h>
#include "lib/gpio_pin.h"
#include "lib/queue.h"
#include "lib/uart.h"

typedef void (*FuncPtr)(void);
typedef Fifo<64,FuncPtr> FifoDeFuncoes_t;
FifoDeFuncoes_t fifo;
Uart uart(57600);

const int led_pin = 5;
const int bot_pin = 2;
volatile int bot = 0;

unsigned char *eicra = (unsigned char *) 0x69;
unsigned char *eimsk = (unsigned char *) 0x3d;

void setup()
{
    uart.puts("Setup\n");

    // configurar INT0 para Rising Edge no eicra
    *eicra = ( (*eicra) & 0xf0 ) | 0x03;
    // ativar INT0 no eimsk
    *eimsk = ( (*eimsk) & 0xfc ) | 0x01;
    sei(); // __asm__ ("sei");
}

void delay1000(void)
{
  volatile unsigned long x = 0x7ffff;
  while(x--);
}

GPIO_Pin led(GPIO_Pin::GPIO_PORTB, led_pin, GPIO_Pin::OUTPUT);
GPIO_Pin button(GPIO_Pin::GPIO_PORTD, bot_pin, GPIO_Pin::INPUT);

void liga_led(void)
{
    led.set();
}

void desliga_led()
{
    led.clear();
}

ISR(INT0_vect)
{
    uart.put('x');
    fifo.enqueue(liga_led);
    fifo.enqueue(delay1000);
    fifo.enqueue(desliga_led);
    fifo.enqueue(delay1000);
    fifo.enqueue(liga_led);
    fifo.enqueue(delay1000);
    fifo.enqueue(desliga_led);
    fifo.enqueue(delay1000);

}
void loop()
{
    static FuncPtr f;
    if (fifo.length() > 0)
    {   
        uart.put('f');
        cli();
        f = fifo.dequeue();
        sei();
        f();
    }
}

bool botao()
{
    return button.get();
}

int main() {
    setup();
    while(true)
    {
        loop();
    }
}
