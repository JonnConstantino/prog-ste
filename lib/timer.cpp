/*
 * Arquivo: timer.cpp
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

Timer * Timer::_singleton = 0;

Timer::Timer(/* args */)
{
    if (_singleton != 0)
    {
        /*erro!! */
    }
    _singleton = this;

    microseconds = 0;
    //Configurar Timero para 10KHz (Fint)
    //prescaler = 8 (div)
    //OCR = 99 (CMP)

    // Configurar prescaler


    // Configuara Timer
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS01);
    OCR0A = 199; // 199 - 8MHz / 99 - 16MHz;
    TIMSK0 = (1 << OCIE0A);
}

Timer::~Timer()
{
    TCCR0A = 0;
    TCCR0B = 0;
}
Microseconds Timer::micros() 

{
 return microseconds;

}
   void Timer::handleIsr()
{
    microseconds += 100;
}

ISR(TIMER0_COMPA_vect)
{
    Timer::singleton() -> handleIsr();
}