/**
 * Project: IFJ21 imperative language compiler  
 *  
 * Author:  Stepan Bakaj     <xbakaj00> 
 * 
 */

#ifndef IFJ_BRATWURST2021_DLL_H
#define IFJ_BRATWURST2021_DLL_H


/** Two-way bound list element */
typedef struct DLLElement {
    /** Useful data */
    char* data;
    /** Pointer to the previous list element */
    struct DLLElement *previousElement;
    /** Pointer to the next list element */
    struct DLLElement *nextElement;
} *DLLElementPtr;

/** Two-way bound list */
typedef struct {
    /** Pointer to the first element of the list */
    DLLElementPtr firstElement;
    /** Pointer to the last element of the list */
    DLLElementPtr lastElement;
} DLList;

void DLL_Init( DLList * );

void DLL_Dispose( DLList * );

void DLL_PrintAll( DLList * );

void DLL_InsertLast( DLList *, char * );

#endif //IFJ_BRATWURST2021_DLL_H
