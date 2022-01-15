install:
	@sudo apt install libedit-dev

pull:
	@git pull --recurse-submodules

build:
	@cc -std=c99 -Wall main.c mpc/mpc.c -ledit -lm -o yalang

run: build
	@./yalang
