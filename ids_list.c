#include <stdlib.h>
#include <string.h>

#include "ids_list.h"
#include "error.h"
#include "data_types.h"

void idInsert(ids_list_t** ids_list, data_type_t type, char* id)
{    
    /* DONE free */
    ids_list_t* newId = (ids_list_t*) malloc(sizeof(ids_list_t));

    if(!newId){
        err = E_INTERNAL;
        return;
    }

    /* DONE free */
    newId->id = (char*) malloc(strlen(id)+1);

    if (newId->id == NULL)
    {
        free(newId);
        newId = NULL;
        err = E_INTERNAL;
        return;
    }
    
    strcpy(newId->id, id);
    newId->type = type; 

    if(*ids_list == NULL){
        *ids_list = newId;
        (*ids_list)->next = NULL;
    }else{        
        ids_list_t* current;
        current = (*ids_list);

        while(current->next != NULL){
            current = current->next;
        }
        newId->next = NULL;        
        current->next = newId;
    }    
}

void save_ids_list(ids_list_t* orig, ids_list_t** dest)
{
    ids_list_t* current = orig;

    while (current != NULL)
    {
        //printf("\ncurrent id: %s\n", current->id);
        idInsert(dest, current->type, current->id);

        current = current->next;
    }    
}

char* get_last_id (ids_list_t* ids_list)
{
    ids_list_t* current = ids_list;

    if (current == NULL)
    {
        return NULL;
    }    

    while (current->next != NULL)
    {
        current = current->next;
    }
    
    return current->id;
}

void delete_last_id (ids_list_t** ids_list)
{
    ids_list_t* current = *ids_list;

    if (current == NULL)
    {
        return;
    }

    /* Last element in list */
    if (current->next == NULL)
    {
        free(current->id);
        current->id = NULL;
        free(current);
        current = NULL;
        *ids_list = current;
        return;
    }    

    while (current->next->next != NULL)
    {        
        current = current->next;    
    }

    free(current->next->id);
    current->next->id = NULL;
    free(current->next);
    current->next = NULL;
}

void delete_ids_list(ids_list_t* ids_list)
{
    ids_list_t* current = NULL;

    while (ids_list != NULL)
    {
        current = ids_list;
        ids_list = ids_list->next;   

        free(current->id);
        current->id = NULL;
        free(current);
        current = NULL;
    }
}