/*
 * Arquivo: adc.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */
#include "cfifo.h"
#ifndef __ADC_H__
#define __ADC_H__

class AdcChannel
{
public:
    AdcChannel(int ch);
    int get();
    int get(int i);

    void start();
    void stop();

    void int_handler();

    static AdcChannel * instance(int i)
   {
       return _instances[i];
   }
private:
static AdcChannel * _instances[6];
    int channel;
    CircularFifo<8, int> cfifo;
};


#endif /* __ADC_H__ */