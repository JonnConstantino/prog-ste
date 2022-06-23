/*
 * Arquivo: uart.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

#include "queue.h"

#ifndef __UART_H__
#define __UART_H__

class Uart
{
public:
    Uart(unsigned long baud);
    ~Uart();

    void put(const unsigned char c);
    void puts(const char * s);
    unsigned char get();

    static Uart * instance()
       { return _instance; }

    void udre_handler();
    void rxc_handler();

private:
    static const unsigned long Freq = 16e6;
    Fifo<64, unsigned char> tx_fifo;
    Fifo<64, unsigned char> rx_fifo;
    static Uart * _instance;
};

#endif /* __UART_H__ */