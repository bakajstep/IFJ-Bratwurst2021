/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Symbol table implemented by binary tree iterative
 *
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 *
 * Date:    12-11-2021
 */

#ifndef IFJ_BRATWURST2021_SYMTABLE_H
#define IFJ_BRATWURST2021_SYMTABLE_H

#include<stdlib.h>
#include<stdbool.h>

typedef enum e_data_type{
    INT,
    DOUBLE,
    STR,
    NIL
} data_type_t

typedef struct symData{    
    bool declared;         /* func / var */
    bool defined;          /* func / var (initialized) */
    data_type_t data_type; /* data type */
    unsigned params_count; /* func params count*/
    struct function_params *first_param;
} symData_t;

struct function_params{
    data_type_t param_type;
    char *param_name;
    struct function_params *param_next;
};

typedef struct symTree{
    const char *key;           /* func / id name */
    symTree_t data;            /* data */
    struct symTree *nextLeft;  
    struct symTree *nextRight;
} symTree_t;

void symTableInit(symTree_t **tree);
T_symData *symTableSearch(symTree_t **tree, char key);
T_symData *symTableInsert(symTree_t **tree, char key, symData_t data);
void symTableDispose(symTree_t **tree);


#endif //IFJ_BRATWURST2021_SYMTABLE_H
