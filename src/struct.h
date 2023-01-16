#ifndef LISPY_STRUCT_H
#define LISPY_STRUCT_H

enum ValTypes { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_FUN, LVAL_SEXPR, LVAL_QEXPR };

struct lval;
struct lenv;

// Cyclic types
typedef struct lval lval;
typedef struct lenv lenv;

// To get an lval* we dereference lbuiltin
// and call it with a lenv* and a lval*
typedef lval*(*lbuiltin)(lenv*, lval*);

struct lval {
  int type;
  long num;
  char* err;
  char* sym;
  lbuiltin fun;
  int count;
  lval** cell;
};

struct lenv {
  int count;
  char** syms;
  lval** vals;
};


char* ltype_name(int t) {
  switch(t) {
    case LVAL_FUN: return "Function";
    case LVAL_NUM: return "Number";
    case LVAL_ERR: return "Error";
    case LVAL_SYM: return "Symbol";
    case LVAL_SEXPR: return "S-Expression";
    case LVAL_QEXPR: return "Q-Expression";
    default: return "Unknown";
  }
}

#endif
