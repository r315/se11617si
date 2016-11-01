CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
DBG = arm-none-eabi-insight
AR = arm-none-eabi-ar
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy


AFLAGS= -g
CFLAGS= -g -mapcs
LFLAGS= -g
LDSCRIPT= -T ../../bsp/ldscript_ram
LIBS = -lgpio
SYMBOLS = -D__NEWLIB__


TARGET = blink
LIBTARGET =

OBJS = init.o $(TARGET).o delay.o

all: $(TARGET).axf

$(TARGET).axf: $(OBJS)
	$(LD) $(LFLAGS) $(LDSCRIPT) -L../../libs $(OBJS) -o $(TARGET).axf $(LIBS)

$(TARGET).o: $(TARGET).c 
	$(CC) $(CFLAGS) $(SYMBOLS) -I../../includes -c $(TARGET).c -o $(TARGET).o

init.o: ../../bsp/init.S
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

delay.o: delay.S
	$(AS) $(AFLAGS) delay.S -o delay.o



clean:
	rm -f *.o $(TARGET).axf 
	
debug:  $(TARGET).axf
	@$(DBG) $(TARGET).axf
		
dump: $(TARGET).axf
	$(OBJDUMP) -d -S $(TARGET).o
	
hex: $(TARGET).axf
	$(OBJCOPY) --set-start 0x40001000 -O ihex $(TARGET).axf $(TARGET).hex
	


