/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Symbol stack
 *
 * Author:  Stepan Bakaj     <xbakaj00@stud.fit.vutbr.cz>
 *
 * Date:    15-11-2021
 */


#include <stdlib.h>

#include "symstack.h"


void sym_stack_init(sym_stack* stack){
    stack->top = NULL;
}

bool symbol_stack_push(sym_stack* stack, psa_table_symbol_enum symbol){
    sym_stack_item *new_item = (sym_stack_item *) malloc(sizeof(sym_stack_item));
    if (!new_item){
        return false;
    }
    new_item->symbol = symbol;
    new_item->next = stack->top;
    stack->top = new_item;
    return true;
}

bool symbol_stack_pop(sym_stack* stack){
    if (stack->top != NULL)
    {
        sym_stack_item* tmp = stack->top;
        stack->top = tmp->next;
        free(tmp);

        return true;
    }
    return false;
}

sym_stack_item* symbol_stack_top(sym_stack* stack)
{
    return stack->top;
}


