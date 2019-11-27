#include <X11/Xlib.h> 
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <X11/Xutil.h>

int errorHandler(Display *dpy, XErrorEvent *event)
{
	fprintf(stderr, "Error event occured\n");
	return 0;
}

int main(int argc, char *argv[])
{
	int retval = 0;
	Display *display = NULL;
	Window defaultRootWindow;
	volatile int stop = 0;
	struct tm *tm;
	time_t timeval;
	char buffer[64];
	int nprops;
	Atom *alist = NULL;
	int i;

	display = XOpenDisplay(NULL);
	XSetErrorHandler(errorHandler);
	if(display)
	{
		defaultRootWindow = XDefaultRootWindow(display);
		while (!stop && ! retval)
		{
			alist = XListProperties(display, defaultRootWindow, &nprops);
			printf("properties: %d\n", nprops);
			for (i=0; i<nprops; i++)
			{
				printf("%s\n", XGetAtomName(display, alist[i]));
			}


			timeval = time(NULL);		
			tm = localtime(&timeval);
			if (tm == NULL)
			{
				retval = 8;
				snprintf(buffer, sizeof(buffer),"Clock error");
			}
			if (!retval)
			{
				strftime(buffer,
					sizeof(buffer), 
					"%H:%M:%S", 
					tm);
			}
			printf("setting %s\n", buffer);
			XStoreName(display, defaultRootWindow, buffer);
			XFlush(display);
			sleep(10);
		}
		XCloseDisplay(display);
	}
	return retval;	
}
