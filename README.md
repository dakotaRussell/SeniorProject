# SeniorProject

How to build:

gcc -Wall -Izlib -lpng -I/usr/include/python2.7 -lpython2.7 -lwiringPi -lpthread -o "%e" "%f"

In lib png folder:

    cp scripts/pnglibconf.h.prebuilt pnglibconf.h
    cp scripts/makefile.std makefile
    make test
    make install
    
-Use of this code requires that the zip library is already installed.
-Must include <png.h>
 
 In wiringPi folder: 
     
     ./build 
 
-Must include <softPwm.h>

