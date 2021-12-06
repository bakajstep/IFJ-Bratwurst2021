#ifndef IFJ_BRATWURST2021_PARSER_H
#define IFJ_BRATWURST2021_PARSER_H

#include <stdbool.h>
#include "scanner.h"
#include "symtable.h"
#include "sym_linked_list.h"
#include "paramstack.h"

#define PARSE_NO_ERR false
#define PARSE_ERR true

typedef bool parser_error_t;

typedef enum e_arg_ret {
    ARG_DEF_TYPE,
    RET_DEF_TYPE
} arg_ret_t;

typedef struct ids_list {
    data_type_t type;
    struct ids_list* next;
    char* id;
} ids_list_t;

typedef struct p_data {
    token_t* token;
    LList* tbl_list;
    char* func_name; 
    char* body_func_name;   

    unsigned write_params_cnt;

    arg_ret_t arg_ret;    
    data_type_t type;
    data_type_t psa_data_type; // psa data type
    unsigned returns_def_count;

    function_params_t* param;
    function_returns_t* ret;
    ids_list_t* ids_list;

    param_stack* stack;
} *p_data_ptr_t;

parser_error_t parser ();
bool check_identifier_is_defined (LList* tbl_list, char* id);
data_type_t identifier_type (LList* tbl_list, char* id);
void next_token(p_data_ptr_t data);
bool is_func(LList* tbl_list, char* id);

#endif //IFJ_BRATWURST2021_PARSER_H