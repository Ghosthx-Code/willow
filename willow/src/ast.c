#include "include/ast.h"
#include <stdlib.h>
#include <stdio.h>
ast_t* init_ast(ast_kind kind) {
    ast_t* node = calloc(1, sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "[AST] Memory allocation failed\n");
        exit(1);
    }
    node->kind = kind;
    switch (kind) {
        case NODE_COMPOUND:
            node->data.compound.children = NULL;
            node->data.compound.size = 0;
            break;
        case NODE_INT:
            node->data.int_value = 0;
            break;
        case NODE_STRING:
        case NODE_VAR:
            node->data.string_value = NULL;
            break;
        case NODE_CHAR:
            node->data.char_value = '\0';
            break;
        default:
            break;
    }
    return node;
}
void ast_add_child(ast_t* parent, ast_t* child) {
    if (!parent || !child)
        return;
    if (parent->kind != NODE_COMPOUND) {
        fprintf(stderr, "[AST] Tried to add child to non-compound node\n");
        exit(1);
    }
    size_t new_size = parent->data.compound.size + 1;
    ast_t** new_children = realloc(
        parent->data.compound.children,
        sizeof(ast_t*) * new_size
    );
    if (!new_children) {
        fprintf(stderr, "[AST] realloc failed while adding child\n");
        exit(1);
    }
    parent->data.compound.children = new_children;
    parent->data.compound.children[parent->data.compound.size] = child;
    parent->data.compound.size = new_size;
}
