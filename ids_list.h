/**
 * Project: IFJ21 imperative language compiler   
 * 
 * Author:  David Chocholaty <xchoch09>
 *  
 */

#ifndef IFJ_BRATWURST2021_IDS_LIST_H
#define IFJ_BRATWURST2021_IDS_LIST_H

#include "data_types.h"

typedef struct ids_list {
    data_type_t type;
    struct ids_list* next;
    char* id;
} ids_list_t;

void idInsert(ids_list_t** ids_list, data_type_t type, char* id);
void save_ids_list(ids_list_t* orig, ids_list_t** dest);
char* get_last_id (ids_list_t* ids_list);
void delete_last_id (ids_list_t** ids_list);
void delete_ids_list(ids_list_t* ids_list);

#endif // IFJ_BRATWURST2021_IDS_LIST_H