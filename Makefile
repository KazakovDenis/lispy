build:
	@cc -std=c99 -Wall main.c -o main

run: build
	@./main
