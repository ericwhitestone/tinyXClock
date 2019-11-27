
CFLAGS= -lX11 -Wall

default: tinyXClock

.PHONY:
clean: tinyXClock
	rm -f tinyXClock
