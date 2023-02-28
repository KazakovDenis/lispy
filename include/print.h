#ifndef LISPY_PRINT_H
#define LISPY_PRINT_H

#include "struct.h"


void lval_print(lval* v);

void lval_expr_print(lval* v, char open, char close);

void lval_print_str(lval* v);

void lval_print(lval* v);

void lval_println(lval* v);


#endif
