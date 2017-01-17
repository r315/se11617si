CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
DBG = arm-none-eabi-insight
GDB = arm-none-eabi-gdb
AR = arm-none-eabi-ar
OBJDUMP = arm-none-eabi-objdump

AFLAGS= -gstabs
CFLAGS= -g -mapcs
LFLAGS= 
LDSCRIPT= -T ../../bsp/ldscript_ram

TARGET = lab3Test
LIBTARGET = timer.a button.a clock.a

INCSDIR = ../../includes
LIBSDIR = ../../libs

OBJS = init.o $(TARGET).o

LIBS = -lled -ltimer -lbutton -lgcc -lclock
LIBSPATH = -L$(LIBSDIR) -L/usr/local/arm-tools/arm-2009q1/lib/gcc/arm-none-eabi/4.3.3
INCSPATH = -I$(INCSDIR)

SYMBOLS =

all: $(TARGET).axf

$(TARGET).axf: $(OBJS)
	$(LD) $(LFLAGS) $(LDSCRIPT) $(LIBSPATH) $(OBJS) -o $(TARGET).axf $(LIBS)

init.o:
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

clean:
	rm -f *.o $(TARGET).axf 
	
debug:  $(TARGET).axf
	@$(DBG) $(TARGET).axf

lib: $($(LIBTARGET):.a=.o) $(LIBTARGET)

libled: led.o
	$(AR) -cr  $(LIBSDIR)/libled.a led.o
	
LCLEAN = $(addprefix $(LIBSDIR)/lib, $(LIBTARGET))
libclean: 
	rm -f $(LCLEAN)
	
dump: $(TARGET).axf
	$(OBJDUMP) -d -S $(TARGET).o

.c.o:
	$(CC) $(CFLAGS) $(SYMBOLS)  $(INCSPATH) -c $< -o $(<:.c=.o)

.o.a:
	$(AR) -cr  $(LIBSDIR)/lib$(<:.o=.a) $<


