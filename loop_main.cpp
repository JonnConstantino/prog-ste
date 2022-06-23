/*
 * Pinagem usada para esta aplicação:
 * POT - ADC0
 */

/*
 * Arquivo: uart_loopback.cpp
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

#include <stdio.h>
#include "lib/uart.h"
#include <avr/interrupt.h>

Uart uart(57600);

void setup()
{
    sei();
    uart.puts("Setup\n");
}

void loop()
{
    uart.put(uart.get());
}

int main() {
    setup();
    while(true)
    {
        loop();
    }
}




/*
 * Arquivo: adc.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

// #include <stdio.h>
// #include "lib/uart.h"
// #include "lib/adc.h"
// #include <avr/interrupt.h> 

// AdcChannel adc0(0);
// Uart uart(57600);

// void setup()
// {

//     uart.puts("Setup\n");
//     adc0.start();
//     sei();
// }

// void delay1000(void)
// {
//   volatile unsigned long x = 0x7ffff;
//   while(x--);
// }

// float f_volts(unsigned int d)
// {
//     return d * (5.0/1023);
// }

// void readAdc0()
// {
//     unsigned int media = 0;
//     for (int i = 0; i < 8; i++)
//         media += adc0.get(i);
//     media /= 8;

//     char buffer[32];
//     sprintf(buffer, "Digital %d\n", media);
//     uart.puts(buffer);
    
//     sprintf(buffer, "Milivolts %f\n", f_volts(media));
//     uart.puts(buffer);
// }

// void loop()
// {
//     // readAdc0();
//     // delay1000();
//     uart.put(uart.get());
// }

// int main() {
//     setup();
//     while(true)
//     {
//         loop();
//     }
// }
