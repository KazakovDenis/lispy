#include <stdio.h>

#define true 1


/* Declare a buffer for user input of size 2048 */
static char input[2048];

int main(int argc, char** argv) {

  /* Print Version and Exit Information */
  puts("Yalang v0.0.1");
  puts("Press Ctrl+C to Exit\n");

  /* In a never ending loop */
  while (true) {

    /* Output our prompt */
    fputs("yalang> ", stdout);

    /* Read a line of user input of maximum size 2048 */
    fgets(input, 2048, stdin);

    /* Echo input back to user */
    printf("No you're a %s", input);
  }

  return 0;
}