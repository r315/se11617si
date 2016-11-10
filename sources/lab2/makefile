CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
DBG = arm-none-eabi-insight
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy

TARGET= lab2Test
AFLAGS= -gstabs
CFLAGS= -g -mapcs
LFLAGS=
LDSCRIPT= -T ../../bsp/ldscript_ram
LIBS = -lled

all: lab2Test.axf

lab2Test.axf: init.o lab2Test.o delay.o 
	$(LD) $(LFLAGS) $(LDSCRIPT) -L../../libs lab2Test.o init.o delay.o -o lab2Test.axf $(LIBS)

lab2Test.o: lab2Test.c 
	$(CC) $(CFLAGS) -I../../includes -c lab2Test.c -o lab2Test.o

delay.o: delay.S
	$(AS) $(AFLAGS) delay.S -o delay.o

init.o: ../../bsp/init.S
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

clean:
	rm -f init.o delay.o lab2Test.o lab2Test.axf

debug:  lab2Test.axf
	@$(DBG) lab2Test.axf
	
lib: delay.o
	$(AR) rcs libdelay.a delay.o 
	
hex: $(TARGET).axf
	$(OBJCOPY) --set-start 0x40000000 -O ihex $(TARGET).axf $(TARGET).hex

