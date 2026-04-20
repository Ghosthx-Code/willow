#include "include/lexer.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
lexer_T* init_lexer(const char* src) {
    lexer_T* lexer = calloc(1, sizeof(lexer_T)); 
    lexer->src = src;
    lexer->i = 0;
    lexer->line = 1;
    lexer->col = 1;
    lexer->c = src[lexer->i];
    return lexer;
}
void lexer_advance(lexer_T* lexer) {
    if (lexer->c != '\0') {
        if (lexer->c == '\n') {
            lexer->line += 1;
            lexer->col = 1;
        } else {
            lexer->col += 1;
        }
        lexer->i += 1;
        lexer->c = lexer->src[lexer->i];
    }
}
void lexer_skip_whitespace(lexer_T* lexer) {
    while (isspace(lexer->c)) {
        lexer_advance(lexer);
    }
}
token_t* lexer_collect_id(lexer_T* lexer) {
    int start = lexer->i;

    while (isalnum(lexer->c) || lexer->c == '_' || lexer->c == '*') {
        lexer_advance(lexer);
    }

    int len = lexer->i - start;
    char* value = calloc(len + 1, sizeof(char));
    memcpy(value, &lexer->src[start], len);

    for (int i = 0; i < (sizeof(token_strings) / sizeof(char*)); i++) {
        if (strcmp(value, token_strings[i]) == 0) {
            return init_token(i, value);
        }
    }

    return init_token(token_id, value);
}
token_t* lexer_collect_int(lexer_T* lexer) {
    int start = lexer->i;
    while (isdigit(lexer->c)) {
        lexer_advance(lexer);
    }

    int len = lexer->i - start;
    char* value = calloc(len + 1, sizeof(char));
    memcpy(value, &lexer->src[start], len);
    return init_token(token_int3, value); 
}
token_t* lexer_collect_string_literal(lexer_T* lexer) {
    lexer_advance(lexer); // skip opening "
    int start = lexer->i;

    while (lexer->c != '"' && lexer->c != '\0') {
        lexer_advance(lexer);
    }

    int len = lexer->i - start;
    char* value = calloc(len + 1, sizeof(char));
    memcpy(value, &lexer->src[start], len);
    
    if (lexer->c == '"') lexer_advance(lexer); 
    return init_token(token_string, value);
}
token_t* lexer_next_token(lexer_T* lexer) {
    while (lexer->c != '\0') {
        if (isspace(lexer->c)) {
            lexer_skip_whitespace(lexer);
            continue;
        }
        if (isalpha(lexer->c)) {
            return lexer_collect_id(lexer);
        }
        if (isdigit(lexer->c)) {
            return lexer_collect_int(lexer);
        }
        if (lexer->c == '"') {
            return lexer_collect_string_literal(lexer);
        }
        if (lexer->c == '\'') {
            lexer_advance(lexer);
            char char_buf[2] = {lexer->c, '\0'};
            lexer_advance(lexer); 
            if (lexer->c == '\'') lexer_advance(lexer);
            return init_token(token_char, strdup(char_buf));
        }
        if (lexer->c == '<') {
            lexer_advance(lexer);
            if (lexer->c == '-') {
                lexer_advance(lexer);
                return init_token(token_Larrow, "<-");
            }
        }

        if (lexer->c == '-') {
            lexer_advance(lexer);
            if (lexer->c == '>') {
                lexer_advance(lexer);
                return init_token(token_Rarrow, "->");
            }
        }

        // Single character tokens
        switch (lexer->c) {
            case ';': lexer_advance(lexer); return init_token(token_semi, ";");
            case ':': lexer_advance(lexer); return init_token(token_con, ":");
            case '=': lexer_advance(lexer); return init_token(token_Eq, "=");
            case '(': lexer_advance(lexer); return init_token(token_Lpar, "(");
            case ')': lexer_advance(lexer); return init_token(token_Rpar, ")");
            case '{': lexer_advance(lexer); return init_token(token_Lcurl, "{");
            case '}': lexer_advance(lexer); return init_token(token_Rcurl, "}");
            case '?': lexer_advance(lexer); return init_token(token_break_func, "?");
        }

        printf("[Lexer] Unknown character '%c' at %d:%d\n", lexer->c, lexer->line, lexer->col);
        exit(1);
    }
    return init_token(token_eof, "EndOfFile");
}
