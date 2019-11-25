#include <X11/Xlib.h> 
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <X11/Xutil.h>

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
	char *error = "Clock Error" ;
	int clock_error = 0;
	XTextProperty prop;

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
				retval = 8;
				stop = 1;
			}
			if (!clock_error)
			{
				strftime(buffer,
					sizeof(buffer), 
					"%H:%M:%S", 
					tm);
			}
			printf("setting %s\n", buffer);
			status = XGetWMName(display, defaultRootWindow, &prop);
			if (status)
			{
				prop.value = buffer;	
				XSetWMName(display, defaultRootWindow, &prop);
			}
			else
			{
				fprintf(stderr, "Failed to get the WM name property\n");
				stop = 1;	
				retval = 9;
			}
			/*
			XStoreName(display, 
				defaultRootWindow, 
				!clock_error ? buffer : "Clock Error");
			*/
			sleep(10);
		}
		XCloseDisplay(display);
	}
	return retval;	
}
