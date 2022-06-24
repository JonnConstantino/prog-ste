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
    adc0.start();
    sei();
}

void delay1000(void)
{
  volatile unsigned long x = 0x7ffff;
  while(x--);
}

void delay(int s)
{
    Microseconds d = 1000000;
    Microseconds end = timer.micros() + d*s;


 // volatile unsigned long x = 0x7ffff;
 // while(x--);
   while (timer.micros() < end)
   {

   }
}

float f_volts(unsigned int d)
{
    return d * (5.0/1023);
}

void readAdc0()
{
    unsigned int media = 0;
    for (int i = 0; i < 8; i++)
        media += adc0.get(i);
    media /= 8;

    char buffer[32];
    sprintf(buffer, "Digital %d\n", media);
    uart.puts(buffer);
    
    sprintf(buffer, "Milivolts %f\n", f_volts(media));
    uart.puts(buffer);
}

void loop()
{
    readAdc0();
    delay(60);
    uart.put(uart.get());
}

int main() {
    setup();
    while(true)
    {
        loop();
    }
}
