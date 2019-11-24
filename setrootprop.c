#include <X11/Xlib.h> 
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int retval = 9;
	Display *display = NULL;
	Window defaultRootWindow;
	volatile int stop = 0;
	struct tm *tm;
	time_t timeval;
	int status = 0;
	char buffer[64];
	char *error = "Cock Error" ;
	int clock_error = 0;

	display = XOpenDisplay(NULL);
	if(display)
	{
		defaultRootWindow = XDefaultRootWindow(display);
		while (!stop)
		{
			timeval = time(NULL);		
			tm = localtime(&timeval);
			if (tm == NULL)
			{
				clock_error = 1;	
			}
			if (!clock_error)
			{
				strftime(buffer,
					sizeof(buffer), 
					"%H:%M:%S", 
					tm);
			}
			XStoreName(display, defaultRootWindow, "Hello World");
			/*
			XStoreName(display, 
				defaultRootWindow, 
				!clock_error ? buffer : "Clock Error");
			*/
			sleep(10);
		}
		XCloseDisplay(display);
		retval = !clock_error;
	}
	return retval;	
}
