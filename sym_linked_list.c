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

void LL_Init( LList* list ) {
    list->lastElement = NULL;
    list->activeElement = NULL;
}

void LL_Dispose( LList* list ) {

    struct LLElement *current = NULL;
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

void LL_InsertLast( LList* list, symTree_t* root) {
    struct LLElement* newElement;
    newElement->root = root;
    newElement->nextElement = NULL;

    if(list->lastElement == NULL){
        list->lastElement = newElement;
    } else {
        newElement->nextElement = list->lastElement;
        list->lastElement = newElement;
    }
}

void LL_DeleteLast( LList* list ){
    struct LLElement *delElement = NULL;
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

symTree_t * LL_GetFirst( LList* list){
    if(list->lastElement == NULL){
        return NULL;
    }
    struct LLElement* current;
    current = list->lastElement;
    while(current->nextElement != NULL){
        current = current->nextElement;
    }
    return current->root;
}

symTree_t * LL_GetLast( LList* list){
    return list->lastElement->root;
}

void LL_DeleteAfter( LList* list){
    struct LLElement *delElement = NULL;
    if(list->activeElement == NULL || list->activeElement->nextElement == NULL){
        return;
    }
    delElement = list->activeElement->nextElement;
    list->activeElement->nextElement = list->activeElement->nextElement->nextElement;
    delElement = NULL;
}

void LL_InsertAfter( LList* list, symTree_t* root){
    if(list->activeElement == NULL){
        return;
    }
    struct LLElement *newElement;
    newElement->root = root;
    if(list->activeElement == list->lastElement) {
        list->lastElement = newElement;
        newElement->nextElement = NULL;
    }else{
        newElement->nextElement = list->activeElement->nextElement;
        list->activeElement->nextElement = newElement;
    }
}

void LL_GetValue( LList* list, symTree_t* root ){
    if(list->activeElement == NULL){
        return;
    }
    *root = list->activeElement->root;
}

void LL_Next( LList* list){
    if(list->activeElement == NULL){
        return;
    }
    list->activeElement = list->activeElement->nextElement;
}

int LL_IsActive( LList* list){
    return (list->activeElement != NULL) ? 0 : -1;
}

