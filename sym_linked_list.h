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

#include<symtable.h>

typedef struct DLLElement {
    symTree_t* root;
    struct DLLElement* nextElement;
} *DLLElementPtr;

typedef struct {
    DLLElementPtr firstElement;
    DLLElementPtr activeElement;
    DLLElementPtr lastElement;
} DLList;

void DLL_Init( DLList * );

void DLL_Dispose( DLList * );

void DLL_InsertFirst( DLList *, int );

void DLL_InsertLast( DLList *, int );

void DLL_First( DLList * );

void DLL_Last( DLList * );

void DLL_GetFirst( DLList *, int * );

void DLL_GetLast( DLList *, int * );

void DLL_DeleteFirst( DLList * );

void DLL_DeleteLast( DLList * );

void DLL_DeleteAfter( DLList * );

void DLL_DeleteBefore( DLList * );

void DLL_InsertAfter( DLList *, int );

void DLL_InsertBefore( DLList *, int );

void DLL_GetValue( DLList *, int * );

void DLL_SetValue( DLList *, int );

void DLL_Next( DLList * );

void DLL_Previous( DLList * );

int DLL_IsActive( DLList * );

#endif