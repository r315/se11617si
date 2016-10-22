
all: maiorde3.axf

maiorde3.axf: maiorde3.S
	arm-none-eabi-as -g maiorde3.S -o maiorde3.o
	arm-none-eabi-ld maiorde3.o -o maiorde3.axf

debug: maiorde3.axf
	arm-none-eabi-insight maiorde3.axf

clean:
	rm -f maiorde3.o maiorde3.axf
