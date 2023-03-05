#include "lispy.h"
#include "print.h"
#include "struct.h"

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


mpc_parser_t* Number;
mpc_parser_t* Symbol;
mpc_parser_t* String;
mpc_parser_t* Comment;
mpc_parser_t* Sexpr;
mpc_parser_t* Qexpr;
mpc_parser_t* Expr;
mpc_parser_t* Lispy;


void load_parser() {
    Lispy    = mpc_new("lispy");
    Number   = mpc_new("number");
    Symbol   = mpc_new("symbol");
    Sexpr    = mpc_new("sexpr");
    String   = mpc_new("string");
    Comment  = mpc_new("comment");
    Qexpr    = mpc_new("qexpr");
    Expr     = mpc_new("expr");

    mpca_lang(
        MPCA_LANG_DEFAULT,
        "                                                           \
            number   : /-?[0-9]+/ ;                                 \
            symbol   : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&^%]+/           \
                     | \"list\" | \"head\" | \"tail\" | \"join\"    \
                     | \"eval\" | \"exit\" ;                        \
            string   : /\"(\\\\.|[^\"])*\"/ ;                       \
            comment  : /;[^\\r\\n]*/ ;                              \
            sexpr    : '(' <expr>* ')' ;                            \
            qexpr    : '{' <expr>* '}' ;                            \
            expr     : <number> | <symbol> | <string> | <comment>   \
                     | <sexpr> | <qexpr> ;                          \
            lispy    : /^/ <expr>* /$/ ;                            \
        ",
        Number, Symbol, String, Comment, Sexpr, Qexpr, Expr, Lispy
    );
}


int main(int argc, char** argv) {
  load_parser();
  lenv* e = lenv_new();
  lenv_add_builtins(e);

  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      load_file(e, argv[i]);
    }
  } else {
    puts("Lispy v0.0.1");
    puts("Press Ctrl+C to Exit\n");

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
  }
  
  lenv_del(e);
  mpc_cleanup(8, Number, Symbol, String, Comment, Sexpr, Qexpr, Expr, Lispy);
  return 0;
}
