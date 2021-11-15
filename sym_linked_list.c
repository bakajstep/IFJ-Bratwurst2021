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

void DLL_Init( DLList* list ) {
    list->lastElement = NULL;
    list->activeElement = NULL;
}

void DLL_Dispose( DLList* list ) {

    struct DLLElement *current = NULL;
    current = list->lastElement;

    if(list->lastElement == NULL){
        return;
    }

    while(current->nextElement != NULL){
        current = current->nextElement;
    }
    list->lastElement = NULL;
    list->activeElement = NULL;
}

void DLL_InsertLast( DLList* list, symTree_t* root) {
    struct DLLElement newElement;
    newElement->root = root;
    newElement->nextElement = NULL;

    if(list->lastElement == NULL){
        list->lastElement = newElement;
    } else {
        newElement->nextElement = list->lastElement;
        list->lastElement = newElement;
    }
}

void DLL_DeleteLast( DLList* list ){
    struct DLLElement *delElement = NULL;
    if(list->lastElement == NULL){
        return;
    }
    if(list->lastElement == list->activeElement){
        list->activeElement = NULL;
    }
    if(list->lastElement->nextElement == NULL){
        list->lastElement = NULL;
    }else{
        delElement = list->lastElement;
        list->lastElement = list->lastElement->nextElement;
        delElement = NULL;
    }
}
void DLL_DeleteAfter( DLList* list){
    struct DLLElement *delElement = NULL;
    if(list->activeElement == NULL || list->activeElement->nextElement == NULL){
        return;
    }
    delElement = list->activeElement->nextElement;
    list->activeElement->nextElement = list->activeElement->nextElement->nextElement;
    delElement = NULL;
}

void DLL_InsertAfter( DLList* list, symTree_t* root){
    if(list->activeElement == NULL){
        return;
    }
    struct DLLElement *newElement = NULL;
    newElement->root = root;
    if(list->activeElement == list->lastElement) {
        list->lastElement = newElement;
        newElement->nextElement = NULL;
    }else{
        newElement->nextElement = list->activeElement->nextElement;
        list->activeElement->nextElement = newElement;
    }
}

void DLL_GetValue( DLList* list, symTree_t* root ){
    if(list->activeElement == NULL){
        return;
    }
    *root = list->activeElement->root;
}

void DLL_Next( DLList* list){
    if(list->activeElement == NULL){
        return;
    }
    list->activeElement = list->activeElement->nextElement;
}

int DLL_IsActive( DLList* ){
    int DLL_IsActive( DLList *list ) {
        return list->activeElement != NULL;
    }
}

