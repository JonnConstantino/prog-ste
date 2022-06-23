# Arquivo: adc.h
# Autor: Arliones Hoeller
# Organização: IFSC-SJE

COMPONENTS := gpio_pin.o uart.o adc.o timer.o

all: $(COMPONENTS)
	

clean:
	rm -f *.o *.a

%.o: %.cpp
	avr-g++ -mmcu=atmega328p -c $< -o $@
	avr-ar rvs libste.a $@
