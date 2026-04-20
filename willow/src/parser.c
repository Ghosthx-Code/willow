#include "include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/lexer.h" 
#include "include/ast.h"
parser_t* init_parser(lexer_T* lexer) {
    parser_t* parser = calloc(1, sizeof(parser_t));
    parser->lexer = lexer;
    parser->prev_token = NULL;
    parser->current_token = lexer_next_token(lexer);
    return parser;
}
token_t* parser_eat(parser_t* parser, int token_type) {
    if (parser->current_token->type == token_type) {
        parser->prev_token = parser->current_token;
        parser->current_token = lexer_next_token(parser->lexer);
        return parser->prev_token;
    } else {
        printf("[Parser] Unexpected token: '%s' (Expected type %d) at line %d\n", 
                parser->current_token->value, 
                token_type, 
                parser->lexer->line);
        exit(1);
    }
}
ast_t* parser_parse(parser_t* parser) {
    ast_t* root = init_ast(NODE_COMPOUND);
    while (parser->current_token->type != token_eof) {
        ast_t* stmt = parser_parse_statement(parser);
        if (stmt)
            ast_add_child(root, stmt);
    }
    return root;
}
ast_t* parser_parse_statement(parser_t* parser) {
    switch(parser->current_token->type) {
        case token_print:
            return parser_parse_print(parser);
        case token_func:
            return parser_parse_function(parser);
        case token_if:
            return parser_parse_if(parser);
        case token_input:
            return parser_parse_input(parser);
        case token_Lcurl:
            parser_eat(parser, token_Lcurl);
            ast_t* compound = parser_parse_compound(parser);
            parser_eat(parser, token_Rcurl);
            return compound;
        case token_int3:
        case token_int6:
        case token_char:
            return parser_parse_variable_declaration(parser);
        case token_id:
        case token_string:
            return parser_parse_expr(parser);

        case token_eof:
            return NULL;

        default:
            printf("[Parser] Unknown token starting statement: %s at line %d\n", 
                    parser->current_token->value, parser->lexer->line);
            exit(1);
    }
}
ast_t* parser_parse_compound(parser_t* parser) {
    ast_t* compound = init_ast(NODE_COMPOUND);

    while (parser->current_token->type != token_Rcurl &&
           parser->current_token->type != token_eof) {
        
        ast_t* stmt = parser_parse_statement(parser);
        if (stmt)
            ast_add_child(compound, stmt);
    }

    return compound;
}
ast_t* parser_parse_print(parser_t* parser) {
    parser_eat(parser, token_print); 
    parser_eat(parser, token_con); 
    parser_eat(parser, token_Lpar); 

    ast_t* expr = parser_parse_expr(parser); 

    parser_eat(parser, token_Rpar); 
    parser_eat(parser, token_break_func);
    parser_eat(parser, token_semi);

    ast_t* node = init_ast(NODE_PRINT);
    node->data.print.value = expr;
    
    return node;
}
ast_t* parser_parse_input(parser_t* parser) {
    parser_eat(parser, token_input);
    parser_eat(parser, token_con);
    parser_eat(parser, token_Lpar);

    ast_t* expr = parser_parse_expr(parser); 

    parser_eat(parser, token_Rpar); 
    parser_eat(parser, token_break_func);
    parser_eat(parser, token_semi);

    ast_t* node = init_ast(NODE_INPUT);
    node->data.input.value = expr; 
    
    return node;
}
ast_t* parser_parse_if(parser_t* parser) {
    parser_eat(parser, token_if);
    parser_eat(parser, token_Lpar);

    ast_t* condition = parser_parse_expr(parser);

    parser_eat(parser, token_Rpar);
    parser_eat(parser, token_Lcurl);

    ast_t* body = parser_parse_compound(parser);

    parser_eat(parser, token_Rcurl);

    ast_t* node = init_ast(NODE_IF);
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.body = body;

    return node;
}
ast_t* parser_parse_function(parser_t* parser) {
    parser_eat(parser, token_func); 

    token_t* name_tok = parser_eat(parser, token_id);
    char* func_name = name_tok->value;

    parser_eat(parser, token_Lpar);
    parser_eat(parser, token_Rpar);
    
    parser_eat(parser, token_break_func);
    parser_eat(parser, token_Larrow);
    
    token_t* type_tok = parser_eat(parser, token_id); 
    char* llvm_ret_type = type_tok->value;

    parser_eat(parser, token_Lcurl);

    ast_t* func_body = parser_parse_compound(parser);

    parser_eat(parser, token_Rcurl);

    ast_t* node = init_ast(NODE_FUNCTION);
    node->data.function.name = func_name;
    node->data.function.ret_type = llvm_ret_type;
    node->data.function.body = func_body;

    return node;
}
ast_t* parser_parse_expr(parser_t* parser) {
    switch(parser->current_token->type) {
        case token_int3:
        case token_int6:
            return parser_parse_int(parser);

        case token_string:
            return parser_parse_string(parser);

        case token_char:
            return parser_parse_char(parser);

        case token_id:
            return parser_parse_id(parser);

        default:
            printf("[Parser] Unexpected token in expression: %d\n", parser->current_token->type);
            exit(1);
    }
}
ast_t* parser_parse_variable_declaration(parser_t* parser) {
    token_e data_type = parser->current_token->type;
    parser_eat(parser, data_type); 

    parser_eat(parser, token_con);

    token_t* var_name = parser_eat(parser, token_id);

    parser_eat(parser, token_Eq);

    ast_t* value = parser_parse_expr(parser);

    parser_eat(parser, token_break_func);
    parser_eat(parser, token_semi);

    ast_t* node = init_ast(NODE_VAR_DECL);
    node->data.var_decl.name = strdup(var_name->value);
    node->data.var_decl.value = value;
    node->data.var_decl.type = data_type;

    return node;
}
ast_t* parser_parse_int(parser_t* parser) {
    token_t* token = parser->current_token;
    parser_eat(parser, token->type);

    ast_t* node = init_ast(NODE_INT);
    node->data.int_value = atoi(token->value); 
    
    return node;
}

ast_t* parser_parse_string(parser_t* parser) {
    token_t* token = parser_eat(parser, token_string);

    ast_t* node = init_ast(NODE_STRING);
    node->data.string_value = token->value;
    
    return node;
}

ast_t* parser_parse_char(parser_t* parser) {
    token_t* token = parser_eat(parser, token_char);

    ast_t* node = init_ast(NODE_CHAR);
    node->data.char_value = token->value[0];
    
    return node;
}
ast_t* parser_parse_id(parser_t* parser) {
    token_t* token = parser_eat(parser, token_id);

    ast_t* node = init_ast(NODE_VAR);
    node->data.string_value = strdup(token->value);
    
    return node;
}