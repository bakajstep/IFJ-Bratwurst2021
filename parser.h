#ifndef IFJ_BRATWURST2021_PARSER_H
#define IFJ_BRATWURST2021_PARSER_H

#include <stdbool.h>
#include "scanner.h"
#include "symtable.h"
#include "sym_linked_list.h"

#define PARSE_NO_ERR false
#define PARSE_ERR true

typedef bool parser_error_t;

typedef struct p_data {
    token_t* token;
    DLList* tbl_list;
    data_type_t type;
} *p_data_ptr_t;

parser_error_t parser ();
void next_token(p_data_ptr_t data);

#endif //IFJ_BRATWURST2021_PARSER_H