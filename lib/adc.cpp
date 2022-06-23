/*
 * Arquivo: adc.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

AdcChannel * AdcChannel::_instances[6];

AdcChannel::AdcChannel(int ch)
    : channel(ch)
{
    _instances[ch] = this;

    ADMUX = (1 << REFS0) | (0x0f & channel);
    ADCSRA = (1 << ADEN) | (7 << ADPS0);
    ADCSRB = 0;
}

int AdcChannel::get()
{
    ADMUX = (ADMUX & 0xf0) | (0x0f & channel); 

    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
        ;
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));

    return ADC;
}

void AdcChannel::start()
{
    ADCSRA |= (1 << ADIE) | (1 << ADATE);
    ADCSRB = 0; 
    ADCSRA |= (1 << ADSC);
}
ISR(ADC_vect)
{
    int adc = 0x0f & ADMUX;
    AdcChannel::instance(adc) -> int_handler();
}

void AdcChannel::int_handler()
{
    /* salvar ADC na cfifo */
    cfifo.enqueue(ADC);
}

int AdcChannel::get(int i)
{
    /* retornar i-ésimo item da cfifo */
    return cfifo.dequeue(i);
}