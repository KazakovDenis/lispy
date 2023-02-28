OBJS	 = main.o mpc.o
SOURCE	 = $(wildcard src/*.c)
DEPS     = mpc/mpc.c
OUT      = lispy
CC	     = gcc
SANS     = address,undefined,leak,pointer-subtract
FLAGS	 = -g -std=gnu17 -Wall -Wextra -Werror -fsanitize=$(SANS) -I./include -I./mpc 

install:
	@sudo apt install libedit-dev
	@git pull --recurse-submodules

$(OUT): clean
	@$(CC) $(FLAGS) $(SOURCE) $(DEPS) -ledit -lm -o $(OUT)

run: $(OUT)
	@./$(OUT)

clean:
	rm -f $(OBJS) $(OUT)
