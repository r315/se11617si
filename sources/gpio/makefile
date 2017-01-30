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
LIBS =
SYMBOLS =


TARGET = gpioTest
LIBTARGET = gpio

OBJS = init.o $(TARGET).o

all: $(TARGET).axf

$(TARGET).axf: $(OBJS)
	$(LD) $(LFLAGS) $(LDSCRIPT) -L../../libs $(OBJS) -o $(TARGET).axf $(LIBS)

$(TARGET).o: $(TARGET).c 
	$(CC) $(CFLAGS) $(SYMBOLS) -I../../includes -c $(TARGET).c -o $(TARGET).o

init.o: ../../bsp/init.S
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o


clean:
	rm -f *.o $(TARGET).axf 
	
debug:  $(TARGET).axf
	@$(DBG) $(TARGET).axf
	
lib:
	$(CC) -mapcs $(SYMBOLS) -I../../includes -c $(LIBTARGET).c -o $(LIBTARGET).o
#$(AS) $(AFLAGS) $(LIBTARGET).S -o $(LIBTARGET).o
	$(AR) rcs ../../libs/lib$(LIBTARGET).a $(LIBTARGET).o
	
dump: $(TARGET).axf
	$(OBJDUMP) -d -S $(TARGET).o
	
hex: $(TARGET).axf
	$(OBJCOPY) --set-start 0x40001000 -O ihex $(TARGET).axf $(TARGET).hex
	
#$(CC) -shared -Wl,-soname,libdelay.so -o libdelay.so delay.o


