/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Linked list for symtables
 *
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 *
 * Date:    12-11-2021
 */

#include "sym_linked_list.h"

void DLL_Init( DLList *list ) {
    list->firstElement = NULL;
    list->lastElement = NULL;
    list->activeElement = NULL;
}

void DLL_Dispose( DLList *list ) {

    struct DLLElement *current = NULL;
    current = list->firstElement;

    if(list->firstElement == NULL){
        return;
    }

    while(current->nextElement != NULL){
        current = current->nextElement;
    }
    list->lastElement = NULL;
    list->firstElement = NULL;
    list->activeElement = NULL;
}

void DLL_InsertFirst( DLList *list, symTree_t* root) {
    newElement->root = root;
    newElement->nextElement = NULL;

    if(list->firstElement == NULL){
        list->firstElement = newElement;
        list->lastElement = newElement;
    } else {
        list->firstElement = newElement;
    }
}

