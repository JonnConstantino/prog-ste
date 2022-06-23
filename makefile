# Arquivo: adc.h
# Autor: Arliones Hoeller
# Organização: IFSC-SJE

APP_NAME := loop_main
DEVICE := -P /dev/ttyACM0
#FLAGS := -Os
FLAGS := -Os -Wl,-u,vfprintf -lprintf_flt

all:
	(cd lib && make all)
	avr-g++ -mmcu=atmega328p  $(FLAGS) $(APP_NAME).cpp lib/libste.a -o main.out
	avr-objcopy -O ihex main.out main.ihex
	avrdude -p atmega328p -c arduino $(DEVICE) -U flash:w:main.ihex

clean:
	(cd lib && make clean)
	rm -f *.out *.ihex
