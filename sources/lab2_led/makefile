CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
DBG = arm-none-eabi-insight

AFLAGS= -gstabs
CFLAGS= -g -mapcs
LFLAGS=
LDSCRIPT= -T ../../bsp/ldscript_ram
LIBS = -lLED

all: led.axf

led.axf: init.o led.o delay.o 
	$(LD) $(LFLAGS) $(LDSCRIPT) -L../../libs led.o init.o delay.o -o led.axf $(LIBS)

led.o: led.c 
	$(CC) $(CFLAGS) -I../../includes -c led.c -o led.o

delay.o: delay.S
	$(AS) $(AFLAGS) delay.S -o delay.o

init.o: ../../bsp/init.S
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

clean:
	rm -f init.o delay.o led.o led.axf led.map

debug:  led.axf
	@$(DBG) led.axf


