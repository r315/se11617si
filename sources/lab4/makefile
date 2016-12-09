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

INCSDIR = ../../includes
LIBSDIR = ../../libs

TARGET = lab4Test
LIBTARGET = rtc

SYMBOLS =
OBJS = init.o $(TARGET).o
LIBS = -lrtc -lclock -lled -lgcc

LIBSPATH = -L$(LIBSDIR) -L/usr/local/arm-tools/arm-2009q1/lib/gcc/arm-none-eabi/4.3.3
INCSPATH = -I$(INCSDIR)

all: $(TARGET).axf

$(TARGET).axf: $(OBJS)
	$(LD) $(LFLAGS) $(LDSCRIPT) $(LIBSPATH) $(OBJS) -o $(TARGET).axf $(LIBS)

init.o:
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

clean:
	rm -f *.o $(TARGET).axf 
	
debug:  $(TARGET).axf
	@$(DBG) $(TARGET).axf

lib: $(LIBTARGET).o
	rm -f $(LIBSDIR)/lib$(LIBTARGET).a
	$(AR) -cr $(LIBSDIR)/lib$(LIBTARGET).a $(LIBTARGET).o
	rm -f $(LIBTARGET).o
	
dump: $(TARGET).axf
	$(OBJDUMP) -d -S $(TARGET).o

.c.o:
	$(CC) $(CFLAGS) $(SYMBOLS)  $(INCSPATH) -c $< -o $(<:.c=.o)
	


