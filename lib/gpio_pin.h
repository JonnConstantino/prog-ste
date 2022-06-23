/*
 * Arquivo: adc.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

#ifndef __GPIO_PIN_H__
#define __GPIO_PIN_H__

class GPIO_Pin
{
private:
    struct GPIO_Registers_t
    {
        unsigned char pin;
        unsigned char ddr;
        unsigned char port;
    };
    static GPIO_Registers_t *PortB;
    static GPIO_Registers_t *PortC;
    static GPIO_Registers_t *PortD;
public:
    enum GPIO_Port_t
    {
        GPIO_PORTB = 0,
        GPIO_PORTC = 1,
        GPIO_PORTD = 2
    };
    enum GPIO_Mode_t
    {
        INPUT = 0,
        OUTPUT = 1,
        INTERRUPT = 2 // TODO
    };

    GPIO_Pin(GPIO_Port_t port, char pin, GPIO_Mode_t dir)
      : _pin(pin)
    {
        switch (port)
        {
        case GPIO_PORTB: _port = PortB; break;
        case GPIO_PORTC: _port = PortC; break;
        case GPIO_PORTD: _port = PortD; break;
        }

        // DDR
        if (dir == INPUT)
            _port->ddr = ( _port->ddr & ~( 1 << _pin ));
        else
            _port->ddr = ( _port->ddr |  ( 1 << _pin ));
    }

    void set()
    {
        _port->port |= (1 << _pin);
    }
    void clear()
    {
        _port->port &= ~(1 << _pin);
    }
    bool get()
    {
        return (_port->pin & (1 << _pin)) > 0;
    }

private:
    GPIO_Registers_t *_port;
    char _pin;
};

#endif /* __GPIO_PIN_H__ */