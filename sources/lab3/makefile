CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
DBG = arm-none-eabi-insight
AR = arm-none-eabi-ar
OBJDUMP = arm-none-eabi-objdump


TARGET = lab3Test
LIBTARGET = 

OBJS = init.o $(TARGET).o timer.o led.o button.o

AFLAGS= -gstabs
CFLAGS= -g -mapcs
LFLAGS= 
LDSCRIPT= -T ../../bsp/ldscript_ram

LIBS = -lgcc
LIBSPATH = -L../../libs -L/usr/local/arm-tools/arm-2009q1/lib/gcc/arm-none-eabi/4.3.3

SYMBOLS =

INCSPATH = -I../../includes

all: $(TARGET).axf

$(TARGET).axf: $(OBJS)
	$(LD) $(LFLAGS) $(LDSCRIPT) $(LIBSPATH) $(OBJS) -o $(TARGET).axf $(LIBS)

init.o:
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

clean:
	rm -f $(OBJS) $(TARGET).o $(TARGET).axf 
	
debug:  $(TARGET).axf
	@$(DBG) $(TARGET).axf
	
lib:
	$(CC) $(CFLAGS) $(SYMBOLS)  $(INCSPATH) -c $(LIBTARGET).c -o $(LIBTARGET).o
	$(AR) rcs ../../libs/lib$(LIBTARGET).a $(LIBTARGET).o
	
dump: $(TARGET).axf
	$(OBJDUMP) -d -S $(TARGET).o

.c.o:
	$(CC) $(CFLAGS) $(SYMBOLS)  $(INCSPATH) -c $< -o $(<:.c=.o)
	


