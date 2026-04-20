#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include "token.h"

typedef struct LEXER_STRUCT {
    const char* src;      
    size_t src_size;      
    char c;               
    unsigned int i;       
    unsigned int line; 
    unsigned int col;  
} lexer_T;

lexer_T* init_lexer(const char* src);                                                          

void lexer_advance(lexer_T* lexer);

void lexer_skip_whitespace(lexer_T* lexer);

token_t* lexer_collect_id(lexer_T* lexer);

token_t* lexer_next_token(lexer_T* lexer);

#endif
