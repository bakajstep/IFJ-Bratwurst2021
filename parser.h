#ifndef IFJ_BRATWURST2021_PARSER_H
#define IFJ_BRATWURST2021_PARSER_H

#include <stdbool.h>
#include "scanner.h"
#include "symtable.h"

#define PARSE_NO_ERR false
#define PARSE_ERR true

typedef bool parser_error_t;

typedef struct p_data {
    token_t* token;
    symTree_t** glb_sym_tab;
} *p_data_ptr_t;

parser_error_t parser ();
void next_token(p_data_ptr_t data);

#endif //IFJ_BRATWURST2021_PARSER_H