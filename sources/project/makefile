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
LDSCRIPT= -T ../../bsp/ldscript


TARGET = proj
LIBTARGET =

OBJS = init.o $(TARGET).o system.o

SYMBOLS =
LIBS = -lled -ltimer -lbutton -lrtc -lclock -lspi -llcd -lflash -lgcc -lc
LIBSPATH = -L../../libs -L/usr/local/arm-tools/arm-2009q1/lib/gcc/arm-none-eabi/4.3.3 -L/usr/local/arm-tools/arm-2009q1/arm-none-eabi/lib
INCSPATH = -I../../includes

all: $(TARGET).axf

$(TARGET).axf: $(OBJS)
	$(LD) $(LFLAGS) $(LDSCRIPT) $(LIBSPATH) $(OBJS) -o $(TARGET).axf $(LIBS)

init.o:
	$(AS) $(AFLAGS) ../../bsp/init.S -o init.o

clean:
	rm -f *.o *.obj $(TARGET).axf $(TARGET) $(TARGET).exe
	
debug:  $(TARGET).axf
	@$(DBG) $(TARGET).axf


dump: $(TARGET).axf
	$(OBJDUMP) -d -S $(TARGET).o
	
lst:
	$(OBJDUMP) -S --disassemble $(TARGET).axf > $(TARGET).lst

.c.o:
	$(CC) $(CFLAGS) $(SYMBOLS)  $(INCSPATH) -c $< -o $(<:.c=.o)


###############################################################
UNAME_S := $(shell uname -s)
GPP = gcc
ifeq ($(UNAME_S),Linux)

$(TARGET).obj: $(TARGET).c
	$(GPP)  $(INCSPATH) -Wall -lSDL2 -D_EMU_ -c $(TARGET).c -o $(TARGET).obj
	
$(TARGET): $(TARGET).obj
	$(GPP)  $(TARGET).obj -Wall -L../emulator -lemu -lSDL2 -o $(TARGET)
	
emulator: $(TARGET)
	./$(TARGET)
else

COMPILER_FLAGS = -D_EMU_ -w -Wl,-subsystem,windows
INCLUDES += -I"C:/tools/SDL2/include" -I"C:/tools/SDL2/include" -I../../includes
LINKER_FLAGS = -L"C:/tools/SDL2/lib" -LC:/tools/MinGw/lib -L../emulator -lemu -lmingw32 -lSDL2main -lSDL2

$(TARGET).exe: $(TARGET).c
	$(GPP) -c $(TARGET).c $(INCLUDES) $(COMPILER_FLAGS) -o $(TARGET).obj
	$(GPP) $(TARGET).obj $(LINKER_FLAGS) -o $(TARGET)
	
emulator: $(TARGET).exe
	cmd /c $(TARGET).exe
endif

	


