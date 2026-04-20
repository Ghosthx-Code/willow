#ifndef AST_H
#define AST_H
#include "token.h"
#include <stdlib.h>
#include <stddef.h> 
typedef enum {
    NODE_FUNCTION,
    NODE_PRINT,
    NODE_INPUT,
    NODE_RETURN,
    NODE_VAR,       
    NODE_INT,
    NODE_STRING,
    NODE_CHAR,
    NODE_VAR_DECL,   
    NODE_COMPOUND,
    NODE_ASSIGNMENT,
    NODE_IF,
    NODE_NOP
} ast_kind;
typedef struct AST_NODE {
    ast_kind kind;
    union {
        struct {
            char* name;
            char* ret_type;
            struct AST_NODE* body;
        } function;
        struct {
            struct AST_NODE* value;
        } print;
        struct {
            struct AST_NODE* value;
        } input;
        struct {
            struct AST_NODE* value;
        } ret;
        struct {
            struct AST_NODE* condition;
            struct AST_NODE* body;
        } if_stmt;
        struct {
            char* name;
            int type; 
            struct AST_NODE* value;
        } var_decl;
        struct {
            char* name;
            struct AST_NODE* value;
        } assignment;
        char* string_value;
        int int_value;
        char char_value;
        struct {
            struct AST_NODE** children;
            size_t size;
        } compound;

    } data;

} ast_t;
ast_t* init_ast(ast_kind kind);
void ast_add_child(ast_t* parent, ast_t* child);
#endif
