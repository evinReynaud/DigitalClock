
.PHONY: all
all: build

build:
	avr-gcc -DF_CPU=13000000 -mmcu=atmega128 -Os src/*.c -o bin/a.out
	avr-objcopy -O binary bin/a.out bin/a.bin

install:
	avrdude -c jtagmkI -P /dev/ttyS5 -p m128 -U flash:w:bin/a.bin:r

.PHONY: clean, cleanall
clean:
	rm bin/a.out

cleanall : clean
	rm bin/*
