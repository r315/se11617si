CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
DBG = arm-none-eabi-insight
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy

TARGET= ledTest
AFLAGS= -gstabs
CFLAGS= -g -mapcs
LFLAGS=
LDSCRIPT= -T ../../bsp/ldscript_ram
LIBS = -lLED

all: ledTest.axf

ledTest.axf: init.o ledTest.o delay.o 
	$(LD) $(LFLAGS) $(LDSCRIPT) -L../../libs led.o init.o delay.o -o led.axf $(LIBS)

ledTest.o: ledTest.c 
	$(CC) $(CFLAGS) -I../../includes -c ledTest.c -o ledTest.o

delay.o: delay.S
	$(AS) $(AFLAGS) delay.S -o delay.o

init.o: ../../bsp/init.S
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

clean:
	rm -f init.o delay.o led.o led.axf led.map

debug:  ledTest.axf
	@$(DBG) ledTest.axf
	
lib: delay.o
	$(AR) rcs libdelay.a delay.o
	
hex: $(TARGET).axf
	$(OBJCOPY) --set-start 0x40000000 -O ihex $(TARGET).axf $(TARGET).hex

