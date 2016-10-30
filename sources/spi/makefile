CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
DBG = arm-none-eabi-insight
AR = arm-none-eabi-ar
OBJDUMP = arm-none-eabi-objdump


AFLAGS= -gstabs
CFLAGS= -g -mapcs
LFLAGS= 
LDSCRIPT= -T ../../bsp/ldscript_ram
LIBS = -lLED
SYMBOLS = -D__NEWLIB__


TARGET = spi

OBJS = init.o $(TARGET).o

all: $(TARGET).axf

$(TARGET).axf: $(OBJS)
	$(LD) $(LFLAGS) $(LDSCRIPT) -L../../libs $(OBJS) -o $(TARGET).axf $(LIBS)

$(TARGET).o: $(TARGET).c 
	$(CC) $(CFLAGS) $(SYMBOLS) -I../../includes -c $(TARGET).c -o $(TARGET).o

init.o: ../../bsp/init.S
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

clean:
	rm -f init.o $(TARGET).o $(TARGET).axf 
	
debug:  $(TARGET).axf
	@$(DBG) $(TARGET).axf
	
lib: $(TARGET).o
	$(AR) rcs lib$(TARGET).a $(TARGET).o
	
dump: $(TARGET).axf
	$(OBJDUMP) -d -S $(TARGET).o
	
#$(CC) -shared -Wl,-soname,libdelay.so -o libdelay.so delay.o


