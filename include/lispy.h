#ifndef LISPY_H
#define LISPY_H

#include "mpc.h"

#include "print.h"


#define LASSERT(args, cond, fmt, ...) \
  if (!(cond)) { lval* err = lval_err(fmt, ##__VA_ARGS__); lval_del(args); return err; }

#define LASSERT_TYPE(func, args, index, expect) \
  LASSERT(args, args->cell[index]->type == expect, \
    "Function '%s' passed incorrect type for argument %i. Got %s, Expected %s.", \
    func, index, ltype_name(args->cell[index]->type), ltype_name(expect))

#define LASSERT_COUNT(func, args, num) \
  LASSERT(args, args->count == num, \
    "Function '%s' passed incorrect number of arguments. Got %i, Expected %i.", \
    func, args->count, num)

#define LASSERT_NOT_EMPTY(func, args, index) \
  LASSERT(args, args->cell[index]->count != 0, \
    "Function '%s' passed {} for argument %i.", func, index);


char* ltype_name(int t);

lval* lval_num(long x);

lval* lval_err(char* fmt, ...);

lval* lval_sym(char* s);

lval* lval_str(char* s);

lval* lval_sexpr(void);

lval* lval_qexpr(void);

lval* lval_fun(lbuiltin func);

lval* lval_lambda(lval* formals, lval* body);

void lval_del(lval* v);

lval* lval_add(lval* v, lval* x);

lval* lval_copy(lval* v);

lval* lval_read_num(mpc_ast_t* t);

lval* lval_read_str(mpc_ast_t* t);

lval* lval_read(mpc_ast_t* t);

lval* lval_pop(lval* v, int i);

lval* lval_take(lval* v, int i);

lval* lval_eval(lenv* e, lval* v);

lval* lval_call(lenv* e, lval* f, lval* a);

lval* lval_eval_sexpr(lenv* e, lval* v);

lval* lval_join(lval* x, lval* y);

int lval_eq(lval* x, lval* y);

/* --- Environment --- */
lenv* lenv_new(void);

void lenv_del(lenv* e);

void lenv_put(lenv* e, lval* k, lval* v);

lval* lenv_get(lenv* e, lval* k);

lenv* lenv_copy(lenv* e);

void lenv_def(lenv* e, lval* k, lval* v);

void lenv_add_builtin(lenv* e, char* name, lbuiltin func);

void lenv_add_builtin_exit(lenv* e);

void lenv_add_builtins(lenv* e);

/* --- Builtins --- */
lval* builtin_head(lenv* e, lval* a);

lval* builtin_tail(lenv* e, lval* a);

lval* builtin_list(lenv* e, lval* a);

lval* builtin_op(lenv* e, lval* a, char* op);

lval* builtin_add(lenv* e, lval* a);

lval* builtin_sub(lenv* e, lval* a);

lval* builtin_mul(lenv* e, lval* a);

lval* builtin_div(lenv* e, lval* a);

lval* builtin_rem(lenv* e, lval* a);

lval* builtin_pow(lenv* e, lval* a);

lval* builtin_cmp(lenv* e, lval* a, char* op);

lval* builtin_eq(lenv* e, lval* a);

lval* builtin_ne(lenv* e, lval* a);

lval* builtin_ord(lenv* e, lval* a, char* op);

lval* builtin_gt(lenv* e, lval* a);

lval* builtin_ge(lenv* e, lval* a);

lval* builtin_lt(lenv* e, lval* a);

lval* builtin_le(lenv* e, lval* a);

lval* builtin_eval(lenv* e, lval* a);

lval* builtin_join(lenv* e, lval* a);

lval* builtin_var(lenv* e, lval* a, char* func);

lval* builtin_def(lenv* e, lval* a);

lval* builtin_put(lenv* e, lval* a);

lval* builtin_lambda(lenv* e, lval* a);

lval* builtin_if(lenv* e, lval* a);

lval* builtin_load(lenv* e, lval* fval);

lval* builtin_print(lenv* e, lval* a);

lval* builtin_error(lenv* e, lval* a);

lval* builtin(lenv* e, lval* a, char* func);

/* --- Load --- */
void load_file(lenv* e, char* filename);

void load_stdlib(lenv* e, char* content);

#endif
