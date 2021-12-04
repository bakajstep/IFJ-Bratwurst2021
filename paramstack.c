#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "paramstack.h"

void param_stack_init(param_stack* stack)
{
    stack->top = NULL;
}

bool param_stack_push(param_stack* stack, param_type_t param_type, param_attribute_t param_attr)
{
    param_stack_item* new_item = (param_stack_item*) malloc(sizeof(param_stack_item));

    if (!new_item)
    {
        return false;
    }

    new_item->type = param_type;

    switch (param_type)
    {
    case P_ID:
        new_item->attribute.id = (char*) malloc(strlen(param_attr.id) + 1);

        if (!(new_item->attribute.id))
        {
            free(new_item);
            return false;
        }
        
        strcpy(new_item->attribute.id, param_attr.id);

        break;
    
    case P_INT:
        new_item->attribute.integer = param_attr.integer;
        break;

    case P_NUMBER:
        new_item->attribute.number = param_attr.number;
        break;

    case P_STR:
        new_item->attribute.id = (char*) malloc(strlen(param_attr.str) + 1);

        if (!(new_item->attribute.id))
        {
            free(new_item);
            return false;
        }

        strcpy(new_item->attribute.id, param_attr.str);

        break;            

    default:
        break;
    }

    new_item->next = stack->top;

    return true;    
}

bool param_stack_pop(param_stack* stack, param_type_t* param_type, param_attribute_t* param_attr)
{
    if (stack->top != NULL)
    {
        
    }
    
    return false;
}