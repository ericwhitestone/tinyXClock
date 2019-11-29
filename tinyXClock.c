#include <X11/Xlib.h> 
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <X11/Xutil.h>
#include <signal.h>

volatile sig_atomic_t stop = 0;

void terminationHandler(int signum)
{
	stop = 1;	
}

int errorHandler(Display *dpy, XErrorEvent *event)
{
	fprintf(stderr, "Error event occured\n");
	return -1;
}

void setHandler()
{
	struct sigaction ha;
	
        ha.sa_handler = terminationHandler;
	sigemptyset (&ha.sa_mask);
	ha.sa_flags = 0;
	sigaction (SIGINT, &ha, NULL);
	sigaction (SIGTERM, &ha, NULL);
	sigaction (SIGHUP, &ha, NULL);
}

int main(int argc, char *argv[])
{
	Display *display = NULL;
	Window defaultRootWindow;
	struct tm *tm;
	time_t timeval;
	char buffer[64];
	int retval;

	display = XOpenDisplay(NULL);
	XSetErrorHandler(errorHandler);
	setHandler();
	if(display)
	{
		defaultRootWindow = XDefaultRootWindow(display);
		while (!stop && ! retval)
		{
			timeval = time(NULL);		
			tm = localtime(&timeval);
			if (tm == NULL)
			{
				retval = 8;
				snprintf(buffer, sizeof(buffer),"Clock error");
			}
			else
			{
				strftime(buffer,
					sizeof(buffer), 
					"%H:%M %A, %F", 
					tm);
			}
			XStoreName(display, defaultRootWindow, buffer);
			XFlush(display);
			sleep(10);
		}
		XStoreName(display, defaultRootWindow, "--:--");
		XCloseDisplay(display);
		fprintf(stderr, "XClock has closed the connection to "
				"the X server\n");
	}
	return retval;	
}
