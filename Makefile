
CFLAGS= -lX11

default: setrootprop 

.PHONY:
clean: setrootprop
	rm -f setrootprop
