
.PHONY: all
all: build

build:
	avr-gcc -Wall -Wextra -DBENCHMARK -DPOS_IN_A_TURN=360 -DF_CPU=13000000 -mmcu=atmega128 -Os src/*.c -o bin/a.out
	avr-objcopy -O binary bin/a.out bin/a.bin

install:
	avrdude -c jtagmkI -P /dev/ttyS5 -p m128 -U flash:w:bin/a.bin:r

img2mat:
	g++ -Wall -Wextra -Werror -I/opt/opencv/include -Wl,-R/opt/opencv/lib -L/opt/opencv/lib  src/image2matrix.cpp  -lopencv_core -lopencv_imgproc -lopencv_highgui -o bin/img2mat.bin

letters: img2mat
	bin/img2mat.bin ./img src/letters.c

.PHONY: clean, cleanall
clean:
	rm bin/a.out

cleanall :
	rm bin/*
