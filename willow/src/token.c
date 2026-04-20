#include <stdlib.h>
#include "include/token.h"

token_t* init_token(int type, char* value) {
    token_t* token = calloc(1, sizeof(token_t));
    token->type = type;
    token->value = value;
    return token;
}
