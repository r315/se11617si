#OBJS specifies which files to compile as part of the project 
SRCS=lcdsdlTest.c
SRCS += lcdsdl.c
SRCS += emulator.c
SRCS += lcd.c
SRCS += font8x16.c
INCLUDES=-I"../../includes"

TARGET = lcdsdltest

OBJS= $(SRCS:.c=.o)

CC = gcc 
COMPILER_FLAGS = -Wall -D_EMU_
LINKER_FLAGS = -lSDL2 -lpthread

all : $(TARGET)

$(TARGET): $(OBJS) 
	$(CC)  $(OBJS) $(LINKER_FLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)		

clean:
	rm -f $(OBJS) $(TARGET)

.c.o:
	$(CC) $(INCLUDES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $< -o $(<:.c=.o)

lib: lcdsdl.o lcd.o emulator.o font8x16.o
#	$(GCC)  $(INCSPATH) -Wall -lSDL2 -c $(EDIR)/lcdsdl.c -o lcdsdl.o
#	$(GCC)  $(INCSPATH) -Wall -lSDL2 -c $(EDIR)/lcd.c -o lcd.o
#	$(GCC)  $(INCSPATH) -Wall -lSDL2 -c $(EDIR)/emulator.c -o emulator.o
#	$(GCC)  $(INCSPATH) -Wall -lSDL2 -c $(EDIR)/font8x16.c -o font8x16.o
	ar rcs libemu.a lcdsdl.o lcd.o emulator.o font8x16.o
	

	
