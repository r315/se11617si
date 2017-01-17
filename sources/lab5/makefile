CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
DBG = arm-none-eabi-insight
GDB = arm-none-eabi-gdb
AR = arm-none-eabi-ar
OBJDUMP = arm-none-eabi-objdump


TARGET = lcdTest
LIBTARGET = spi

OBJS = init.o $(TARGET).o 

AFLAGS= -gstabs
CFLAGS= -g -mapcs
LFLAGS= 
LDSCRIPT= -T ../../bsp/ldscript_ram

LIBS = -lled -ltimer -lbutton -lrtc -lclock -lspi -llcd -lgcc
LIBSPATH = -L../../libs -L/usr/local/arm-tools/arm-2009q1/lib/gcc/arm-none-eabi/4.3.3

SYMBOLS =

INCSPATH = -I../../includes

all: $(TARGET).axf

$(TARGET).axf: $(OBJS)
	$(LD) $(LFLAGS) $(LDSCRIPT) $(LIBSPATH) $(OBJS) -o $(TARGET).axf $(LIBS)

init.o:
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

clean:
	rm -f *.o $(TARGET).axf 
	
debug:  $(TARGET).axf
	@$(DBG) $(TARGET).axf

lib: libspi liblcd
	rm -f *.o

libspi: spi.o
	$(AR) -cr ../../libs/lib$(<:.o=.a) $<

liblcd: lcd.o ili9341.o font8x16.o
	$(AR) -cr ../../libs/liblcd.a lcd.o ili9341.o font8x16.o
	
dump: $(TARGET).axf
	$(OBJDUMP) -d -S $(TARGET).o

.c.o:
	$(CC) $(CFLAGS) $(SYMBOLS)  $(INCSPATH) -c $< -o $(<:.c=.o)


	


