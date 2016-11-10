#OBJS specifies which files to compile as part of the project 
SRCS=lcdsdlTest.c
SRCS += lcdsdl.c
INCLUDES=-I"../../includes"

OBJS= $(SRCS:.c=.o)

#CC specifies which compiler we're using 
CC = gcc 

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w 

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 

#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = lcdsdltest

#This is the target that compiles our executable 
all : $(OBJS) 
	$(CC)  $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	
.c.o:
	$(CC) $(INCLUDES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $< -o $(<:.c=.o)
	
