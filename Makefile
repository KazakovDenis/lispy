OBJS	 = main.o mpc.o
SOURCE	 = main.c
DEPS     = mpc/mpc.c
OUT      = lispy
CC	     = gcc
FLAGS	 = -g -std=c99 -Wall

install:
	@sudo apt install libedit-dev
	@git pull --recurse-submodules

$(OUT):
	@$(CC) $(FLAGS) $(SOURCE) $(DEPS) -ledit -lm -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OBJS) $(OUT)
