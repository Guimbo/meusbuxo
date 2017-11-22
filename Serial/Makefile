# MPLAB IDE generated this makefile for use with GNU make.
# Project: serial.mcp
# Date: Thu Oct 02 18:18:59 2014

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

serial.cof : serial.o
	$(LD) /p18F4550 /l"C:\Program Files\Microchip\mplabc18\v3.46\lib" "serial.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"serial.cof" /M"serial.map" /W

serial.o : serial.c C:/Program\ Files/Microchip/mplabc18/v3.46/h/p18f4550.h
	$(CC) -p=18F4550 "serial.c" -fo="serial.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "serial.o" "serial.cof" "serial.hex"

