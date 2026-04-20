#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct PARSER_STRUCT {
    lexer_T* lexer;
    token_t* current_token;
    token_t* prev_token;
} parser_t;

// Standard Parser Functions
parser_t* init_parser(lexer_T* lexer);
token_t* parser_eat(parser_t* parser, int token_type);

// The Core "Switch" Dispatchers
ast_t* parser_parse(parser_t* parser);           // Parses the whole program
ast_t* parser_parse_statement(parser_t* parser); // Parses one line/action
ast_t* parser_parse_expr(parser_t* parser);      // Parses a value (string, int, id)

// Specific Willow Syntax Parsers
ast_t* parser_parse_function(parser_t* parser);
ast_t* parser_parse_print(parser_t* parser);
ast_t* parser_parse_compound(parser_t* parser);  // Parses { ... }

ast_t* parser_parse_if(parser_t* parser);

ast_t* parser_parse_input(parser_t* parser);

ast_t* parser_parse_int(parser_t* parser);

ast_t* parser_parse_string(parser_t* parser);
ast_t* parser_parse_char(parser_t* parser);
ast_t* parser_parse_id(parser_t* parser);

ast_t* parser_parse_variable_declaration(parser_t* parser);
#endif
