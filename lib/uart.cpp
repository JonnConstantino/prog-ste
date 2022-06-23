/*
 * Arquivo: uart.cpp
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

Uart* Uart::_instance = 0;

Uart::Uart(unsigned long baud)
{
    _instance = this;

	unsigned int ubrr = (Freq / (16ul * baud)) - 1;
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;

	UCSR0A = 0; // nothing to do here
    UCSR0B = ((1 << TXEN0) | (1 << RXEN0));
    UCSR0C = (3 << UCSZ00);

    // Ligar interrupção RXC
    UCSR0B |= (1 << RXCIE0);
}

Uart::~Uart()
{
}

void Uart::put(const unsigned char c)
{
    cli();
    tx_fifo.enqueue(c);
    sei();

    // ligar interrupção UDRE
    UCSR0B |= (1 << UDRIE0);
}

ISR(USART_UDRE_vect)
{
    Uart::instance()->udre_handler();
}

void Uart::udre_handler()
{
    if (tx_fifo.length() > 0)
    {
        UDR0 = tx_fifo.dequeue();
    }
    else
    {
        // Desligar interrupção UDRE
        UCSR0B &= ~(1 << UDRIE0);
    }
}

ISR(USART_RX_vect)
{
    Uart::instance()->rxc_handler();
}

void Uart::rxc_handler(){
    cli();
    rx_fifo.enqueue(UDR0);
    sei();
}

void Uart::puts(const char * s)
{
    do
    {
        put(*s);
    }
    while(*(++s));
}

unsigned char Uart::get()
{
    // while (! (UCSR0A & (1 << RXC0)) )  ;

    // return UDR0;    
    //Colocar  tratamento aqui 
   if (rx_fifo.length() > 0){
       return rx_fifo.dequeue();
   }
}
// Vai receber da UART com interrupção
//Ligar interrupção do RX
