SRC_DIR  = ./src
OBJ_DIR  = ./obj

DEPS     = ./mpc/mpc.c
DEP_OBJS = $(patsubst ./mpc/%.c, $(OBJ_DIR)/%.o, $(DEPS))

SRC	     = $(wildcard $(SRC_DIR)/*.c)
OBJS	 = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)) $(DEP_OBJS)

OUT      = lispy
CC	     = gcc
SANS     = address,undefined,leak,pointer-subtract
FLAGS	 = -g -std=gnu17 -Wall -Wextra -Werror -fsanitize=$(SANS) -I./mpc  -I./include -I./stdlib -ledit -lm 

install:
	@sudo apt install libedit-dev
	@git pull --recurse-submodules

$(DEP_OBJS): $(DEPS)
	@$(CC) -c $< $(FLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -c $< $(FLAGS) -o $@

$(OUT): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $@

run: $(OUT)
	@./$<

clean:
	rm -f $(OBJ_DIR)/*.o $(OUT)
