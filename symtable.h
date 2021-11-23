/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Symbol table implemented by binary tree
 *
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 * Author:  David Chocholaty <xchoch09@stud.fit.vutbr.cz>
 *
 * Date:    12-11-2021
 */

#ifndef IFJ_BRATWURST2021_SYMTABLE_H
#define IFJ_BRATWURST2021_SYMTABLE_H

#include <stdlib.h>
#include <stdbool.h>

#include "data_types.h"

typedef struct function_params {
    data_type_t param_type;
    char *param_name;
    struct function_params_t* param_next;
} function_params_t;

typedef struct function_returns {
    data_type_t return_type;
    struct function_returns_t* ret_next;
} function_returns_t;

typedef struct symData{    
    bool declared;                  /* func / var */
    bool defined;                   /* func / var (initialized) */
    data_type_t data_type;          /* data type */
    unsigned params_count;       /* func params count*/
    unsigned params_type_count;       /* func params count*/
    unsigned returns_count;
    function_params_t* first_param; /* func params list */
    function_params_t* first_type_param; /* func type params list */
    function_returns_t* first_ret;  /* func returns list */
} symData_t;

typedef struct symTree{
    const char* key;                /* func / id name */
    symData_t* data;                 /* data */
    struct symTree* nextLeft;
    struct symTree* nextRight;
} symTree_t;

void symTableInit(symTree_t **tree);
void symDataInit(symData_t* data);
void paramInsert(symData_t* data, data_type_t type, char* param_name);
/* TODO */
void paramTypeInsert(symData_t* data, data_type_t type);
void returnInsert(symData_t* data, data_type_t type);
symData_t* symTableSearch(symTree_t *tree, char* key);
symData_t* symTableInsert(symTree_t **tree, char* key, symData_t* data);
void symTableDispose(symTree_t **tree);


#endif //IFJ_BRATWURST2021_SYMTABLE_H
