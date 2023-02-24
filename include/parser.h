#ifndef LISPY_PARSER_H
#define LISPY_PARSER_H

#include "../mpc/mpc.h"


mpc_parser_t* Number;
mpc_parser_t* Symbol;
mpc_parser_t* String;
mpc_parser_t* Comment;
mpc_parser_t* Sexpr;
mpc_parser_t* Qexpr;
mpc_parser_t* Expr;
mpc_parser_t* Lispy;


void load_parser() {
    Number   = mpc_new("number");
    Symbol   = mpc_new("symbol");
    Sexpr    = mpc_new("sexpr");
    String   = mpc_new("string");
    Comment  = mpc_new("comment");
    Qexpr    = mpc_new("qexpr");
    Expr     = mpc_new("expr");
    Lispy    = mpc_new("lispy");

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

#endif