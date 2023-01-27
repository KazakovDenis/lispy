#include "src/lval.h"
#include "src/parser.h"
#include "src/print.h"

/* for Windows */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function */
void add_history(char* unused) {}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif


int main(int argc, char** argv) {
  load_parser();

  puts("Lispy v0.0.1");
  puts("Press Ctrl+C to Exit\n");

  lenv* e = lenv_new();
  lenv_add_builtins(e);

  mpc_result_t r;
  int type;

  while (1) {
    char* input = readline(">>> ");
    add_history(input);

    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      lval* x = lval_eval(e, lval_read(r.output));
      type = x->type;

      lval_println(x);
      lval_del(x);

      mpc_ast_delete(r.output);
    } else {    
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
    if (type == LVAL_EXIT) { break; }
  }
  
  lenv_del(e);
  mpc_cleanup(6, Number, Symbol, Sexpr, Qexpr, Expr, Lispy);
  return 0;
}
