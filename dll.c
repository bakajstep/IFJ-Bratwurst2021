/**
 * Project: IFJ21 imperative language compiler
 * 
 * Brief:   Double Linked List used in Code Generator for IFJ21 compiler
 *  
 * Author:  Stepan Bakaj     <xbakaj00> 
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    list->lastElement = NULL;
}

void DLL_InsertLast( DLList *list, char *data ) {

    DLLElementPtr tmp = (DLLElementPtr)malloc(sizeof(struct DLLElement));
    if (tmp != NULL){        
        //tmp->data = (char *) malloc(strlen(data)+1+24);
        //printf("data: %s", data);
        tmp->data = (char *) malloc(strlen(data)+1+24);
        if (tmp->data != NULL) {
            strcpy(tmp->data, data);
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


void DLL_PrintAll( DLList *list ){

    DLLElementPtr tmp = list->firstElement;

    while (tmp != NULL){
        printf("%s", tmp->data);        
        tmp = tmp->nextElement;
    }
}




