
CFLAGS= -lX11 -Wall

default: setrootprop 

.PHONY:
clean: setrootprop
	rm -f setrootprop
