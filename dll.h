/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Double linked list for code generator
 *
 * Author:  Stepan Bakaj     <xbakaj00@stud.fit.vutbr.cz>
 *
 * Date:    23-10-2021
 */


#ifndef IFJ_BRATWURST2021_DLL_H
#define IFJ_BRATWURST2021_DLL_H


/** Prvek dvousměrně vázaného seznamu. */
typedef struct DLLElement {
    /** Užitečná data. */
    char *data;
    /** Ukazatel na předcházející prvek seznamu. */
    struct DLLElement *previousElement;
    /** Ukazatel na následující prvek seznamu. */
    struct DLLElement *nextElement;
} *DLLElementPtr;

/** Dvousměrně vázaný seznam. */
typedef struct {
    /** Ukazatel na první prvek seznamu. */
    DLLElementPtr firstElement;
    /** Ukazatel na posledni prvek seznamu. */
    DLLElementPtr lastElement;
} DLList;

void DLL_Init( DLList * );

void DLL_Dispose( DLList * );

void DLL_PrintAll( DLList * );

void DLL_InsertLast( DLList *, char * );

#endif //IFJ_BRATWURST2021_DLL_H
