# tinyXClock
Tiny program to set the name of the X root window to the current time. This replaces xsetprop for a specific purpose. Compile and add to your xinitrc and done!
The purpose of this was mostly for fun. For no particular reason, I did not feel like installing xsetprop. So, instead, I created a program
that would set 1 specific property for 1 specific reason - to display the time and will likely add the date. I am 
currently using this with DWM, but it would likely work with many other window managers. 

This is my first adventure with XLib, so any kind of feedback or enhancements are welcome!

To build and install: 
```
make && sudo cp tinyXClock /usr/bin && echo "tinyXClock &" >> ~/.xinitrc
```
