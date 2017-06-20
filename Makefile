all: osciloscope.c helpers.c
	$(CC) $^ -lpthread -lncurses -lm -o osciloscope

clean:
	$(RM) osciloscope
