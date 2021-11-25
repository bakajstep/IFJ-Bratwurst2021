/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Linked list for symtables
 *
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 *
 * Date:    12-11-2021
 */

#ifndef IFJ_BRATWURST2021_SYM_LINKED_LIST_H
#define IFJ_BRATWURST2021_SYM_LINKED_LIST_H

#include"symtable.h"

typedef struct LLElement {
    symTree_t* root;
    struct LLElement* nextElement;
} *LLElementPtr;

typedef struct {
    LLElementPtr activeElement;
    LLElementPtr lastElement;
} LList;

void LL_Init( LList * );

void LL_Dispose( LList * );

void LL_InsertLast( LList *, symTree_t * );

symTree_t * LL_GetFirst( LList *);

symTree_t * LL_GetLast( LList *);

void LL_DeleteLast( LList * );

void LL_DeleteAfter( LList * );

void LL_InsertAfter( LList *, symTree_t * );

void LL_GetValue( LList *, symTree_t * );

void LL_Next( LList * );

int LL_IsActive( LList * );

#endif