#ifndef TOKEN_H
#define TOKEN_H

#define TOKENS_LIST \
    x(token_eof,        "EndOfFile") \
    x(token_semi,       "?;")        \
    x(token_con,        ":")         \
    x(token_print,      "printfl")   \
    x(token_input,      "inputfl")   \
    x(token_Eq,         "=")         \
    x(token_id,         "id")        \
    x(token_if,         "if")        \
    x(token_else_if,    "else if")   \
    x(token_else,       "else")      \
    x(token_while,      "while")     \
    x(token_for,        "for")       \
    x(token_true,       "true")      \
    x(token_false,      "false")     \
    x(token_int3,       "i32")       \
    x(token_int6,       "i64")       \
    x(token_char,       "i8")        \
    x(token_string,     "i8*")       \
    x(token_break_func, "?")         \
    x(token_Larrow,     "<-")        \
    x(token_Rarrow,     "->")        \
    x(token_Lpar,       "(")         \
    x(token_Rpar,       ")")         \
    x(token_Lcurl,      "{")         \
    x(token_Rcurl,      "}")         \
    x(token_func,       "func")

// 1. Generate the Enum
typedef enum {
#define x(name, str) name,
    TOKENS_LIST
#undef x
} token_e; // Changed to token_e to avoid common name conflicts

// 2. Generate the String Array
static const char* token_strings[] = {
#define x(name, str) str,
    TOKENS_LIST
#undef x
}; // Added semicolon here

// 3. The Token Structure
typedef struct TOKEN_STRUCT {
    token_e type;
    char* value;     
} token_t;

// 4. Function prototype
token_t* init_token(int type, char* value);

#endif
