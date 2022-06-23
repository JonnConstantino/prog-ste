/*
 * Arquivo: adc.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

/*
 * Pinagem usada para esta aplicação:
 * POT - ADC0
 */

#include <stdio.h>
#include "lib/uart.h"
#include "lib/adc.h"
#include "lib/timer.h"
#include <avr/interrupt.h>

AdcChannel adc0(0);
Uart uart(57600);
Timer timer;

void setup()
{
    uart.puts("Setup\n");
    sei();
}

void delay1(void)
{
    Microseconds d = 1000000;
    Microseconds end = timer.micros() + d;


 // volatile unsigned long x = 0x7ffff;
 // while(x--);
   while (timer.micros() < end)
   {

   }
}

void readAdc0()
{
    int val = adc0.get();
    char buffer[10];
    sprintf(buffer, "%d\n", val);
    uart.puts(buffer);
}
int count = 0;
char buffer[32];
void loop()
{
    sprintf(buffer, "%d\n", count ++);
    uart.puts(buffer);
     delay1();
}

int main() {
    setup();
    while(true)
    {
        loop();
    }
}
