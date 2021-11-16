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

typedef struct{
    TYPE_VAR;
    TYPE_FUNC;
} type_t;

typedef struct symData{
    type_t type;
    bool defined;
    int prams;
} symData_t;

typedef struct symTree{
    char *key;
    symTree_t data;
    struct symTree *nextLeft;
    struct symTree *nextRight;
} symTree_t;

void symTableInit(symTree_t **tree);
T_symData *symTableSearch(symTree_t **tree, char key);
T_symData *symTableInsert(symTree_t **tree, char key, symData_t data);
void symTableDispose(symTree_t **tree);


#endif //IFJ_BRATWURST2021_SYMTABLE_H
