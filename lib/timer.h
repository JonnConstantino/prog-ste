/*
 * Arquivo: timer.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

#ifndef __TIMER_H__
#define __TIMER_H__

typedef unsigned long long Microseconds;

class Timer
{
    public:

        Timer(/* args */);
        ~Timer();

        Microseconds micros();

        void handleIsr();

    static Timer * singleton()
    {
        return _singleton;
    }

    private:
    static Timer * _singleton;
        Microseconds microseconds;
};

#endif /* __TIMER_H__ */    
