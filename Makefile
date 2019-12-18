
.PHONY: all
all: build install	

build:
	avr-gcc -Wall -Wextra -DF_CPU=13000000 -mmcu=atmega128 -Os src/*.c -o bin/a.out
	avr-objcopy -O binary bin/a.out bin/a.bin

benchmark:
	avr-gcc -Wall -Wextra -DBENCHMARK -DF_CPU=13000000 -mmcu=atmega128 -Os src/*.c -o bin/a.out
	avr-objcopy -O binary bin/a.out bin/a.bin

install:
	avrdude -c jtagmkI -P /dev/ttyUSB0 -p m128 -U flash:w:bin/a.bin:r

img2mat:
	g++ -Wall -Wextra -Werror -I/opt/opencv/include -Wl,-R/opt/opencv/lib -L/opt/opencv/lib  src/image2matrix.cpp  -lopencv_core -lopencv_imgproc -lopencv_highgui -o bin/img2mat.bin

letters: img2mat
	bin/img2mat.bin ./img src/letters.c

.PHONY: help
help:
	echo "Usage:"
	echo " - build: builds the source code"
	echo " - benchmark: builds the source code for benchmark use"
	echo " - install: installs the code on the connected device"
	echo " - img2mat: builds the img2mat program"
	echo " - letters: recreate the letters.c file from images in the img/ folder"

.PHONY: clean, cleanall
clean:
	rm bin/a.out

cleanall :
	rm bin/*
