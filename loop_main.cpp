/*
 * Pinagem usada para esta aplicação:
 * POT - ADC0
 */

#include <stdio.h>
#include "lib/uart.h"
#include "lib/adc.h"
#include "lib/timer.h"
#include "lib/cfifo.h"
#include <avr/interrupt.h>

#define CMAX 8

typedef void (*FuncPtr)(void);
typedef CircularFifo<CMAX, FuncPtr> cFifoDeFuncoes_t;
cFifoDeFuncoes_t cFifoAdc;
cFifoDeFuncoes_t cFifoUartTx;
cFifoDeFuncoes_t cFifoUartRx;

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
    while (x--)
        ;
}

void delay1min(void)
{
    Microseconds d = 6000000;
    Microseconds end = timer.micros() + d;

    while (timer.micros() < end)
        ;
}

void delay1ms(void)
{
    Microseconds d = 1000;
    Microseconds end = timer.micros() + d;

    while (timer.micros() < end)
        ;
}

float f_volts(unsigned int d)
{
    return d * (5.0 / 1023);
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

// void putFifo()
// {
//     cFifoAdc.enqueue(readAdc0);
//     cFifoAdc.enqueue(delay1min);
//     cFifoAdc.enqueue(readAdc0);
//     cFifoAdc.enqueue(delay1min);
//     cFifoAdc.enqueue(readAdc0);
//     cFifoAdc.enqueue(delay1min);
//     cFifoAdc.enqueue(readAdc0);
//     cFifoAdc.enqueue(delay1min);
// }

// void loop()
// {
//     putFifo();
//     static FuncPtr f;
//     int i = 0;
//     while (i < CMAX)
//     {
//         cli();
//         f = cFifoAdc.dequeue(i);
//         sei();
//         f();
//         uart.put(uart.get());
//         i++;
//     }
// }

void loop()
{
    readAdc0();
    delay1min();
    uart.put(uart.get());
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
