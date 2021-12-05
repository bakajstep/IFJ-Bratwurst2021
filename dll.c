/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Double linked list for code generator
 *
 * Author:  Stepan Bakaj     <xbakaj00@stud.fit.vutbr.cz>
 *
 * Date:    23-10-2021
 */

#include <stdlib.h>
#include <string.h>

#include "dll.h"
#include "error.h"


void DLL_Init( DLList *list ) {

    list->firstElement = NULL;
    list->lastElement = NULL;
}

void DLL_Dispose( DLList *list ) {

    DLLElementPtr tmp = list->firstElement;
    while (list->firstElement != NULL){
        list->firstElement = list->firstElement->nextElement;
        free(tmp->data);
        tmp->data = NULL;
        free(tmp);
        tmp = NULL;
        tmp = list->firstElement;
    }
    list->activeElement = NULL;
    list->lastElement = NULL;
}

void DLL_InsertLast( DLList *list, char *data ) {

    DLLElementPtr tmp = (DLLElementPtr)malloc(sizeof(struct DLLElement));
    if (tmp != NULL){
        tmp->data = (char *) malloc(sizeof(strlen(data)));
        if (tmp->data != NULL) {
            strcpy_s(data,tmp->data);
        } else {
            free(tmp);
            err = E_INTERNAL;
            return;
        }
        tmp->nextElement = NULL;
        tmp->previousElement = list->lastElement;
        if (list->firstElement == NULL){
            list->firstElement = tmp;
        } else {
            list->lastElement->nextElement = tmp;
        }
        list->lastElement = tmp;
    } else {
        err = E_INTERNAL;
    }
}

