#OBJS specifies which files to compile as part of the project 
SRCS=lcdsdlTest.c
SRCS += lcdsdl.c
INCLUDES=-I"../../includes"

TARGET = lcdsdltest

OBJS= $(SRCS:.c=.o)

CC = gcc 
COMPILER_FLAGS = -Wall 
LINKER_FLAGS = -lSDL2 

all : $(TARGET)

$(TARGET): $(OBJS) 
	$(CC)  $(OBJS) $(LINKER_FLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)		

clean:
	rm -f $(OBJS) $(TARGET)

.c.o:
	$(CC) $(INCLUDES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $< -o $(<:.c=.o)


	

	
