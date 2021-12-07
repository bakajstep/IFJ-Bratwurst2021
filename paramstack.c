/**
 * Project: IFJ21 imperative language compiler
 * 
 * Brief:   Stack for function call parameters
 *  
 * Author:  David Chocholaty <xchoch09>
 * 
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* TODO smazat */
#include <stdio.h>

#include "paramstack.h"

void param_stack_init (param_stack* stack)
{
    stack->top = NULL;
}

bool param_stack_push (param_stack* stack, param_type_t param_type, param_attribute_t param_attr)
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
            new_item = NULL;
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
            new_item = NULL;
            return false;
        }

        strcpy(new_item->attribute.id, param_attr.str);

        break;            

    default:
        break;
    }

    new_item->next = stack->top;
    stack->top = new_item;

    return true;    
}

bool param_stack_pop (param_stack* stack, param_type_t* param_type, param_attribute_t* param_attr)
{
    param_stack_item* tmp = NULL;

    if (param_type == NULL &&
        param_attr == NULL &&
        stack != NULL &&
        stack->top != NULL)
    {        
        tmp = stack->top;

        if (tmp->type == P_ID)
        {
            free(tmp->attribute.id);
            tmp->attribute.id = NULL;
        }
        else if(tmp->type == P_STR)
        {
            free(tmp->attribute.str);
            tmp->attribute.str = NULL;
        }

        stack->top = tmp->next;

        free(tmp);     
        tmp = NULL;

        return true;
    }            

    if (stack != NULL && 
        stack->top != NULL)
    {        
        tmp = stack->top; 
        stack->top = tmp->next;

        *param_type = tmp->type;

        switch (*param_type)
        {
        case P_ID:
            param_attr->id = (char*) malloc(strlen(tmp->attribute.id) + 1);

            if (!(param_attr->id))
            {   
                free(tmp->attribute.id);  
                tmp->attribute.id = NULL;
                free(tmp);                         
                tmp = NULL;
                return false;
            }
            
            strcpy(param_attr->id , tmp->attribute.id);

            free(tmp->attribute.id);
            tmp->attribute.id = NULL;

            break;
        
        case P_INT:
            param_attr->integer = tmp->attribute.integer;
            break;

        case P_NUMBER:                    
            param_attr->number = tmp->attribute.number;
            break;

        case P_STR:
            param_attr->str = (char*) malloc(strlen(tmp->attribute.str) + 1);

            if (!(param_attr->str))
            {
                free(tmp->attribute.str);
                tmp->attribute.str = NULL;
                free(tmp);
                tmp = NULL;
                return false;
            }

            strcpy(param_attr->str, tmp->attribute.str);

            free(tmp->attribute.str);
            tmp->attribute.str = NULL;

            break;

        default:
            break;
        }

        free(tmp);
        tmp = NULL;

        return true;
    }
    
    return false;
}

void param_stack_dispose (param_stack* stack)
{    
    while (param_stack_pop(stack, NULL, NULL));        
}