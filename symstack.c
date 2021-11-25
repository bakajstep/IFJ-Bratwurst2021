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

bool symbol_stack_push(sym_stack* stack, psa_table_symbol_enum symbol, data_type_t data){
    sym_stack_item *new_item = (sym_stack_item *) malloc(sizeof(sym_stack_item));
    if (!new_item){
        return false;
    }
    new_item->symbol = symbol;
    new_item->data = data;
    new_item->next = stack->top;
    stack->top = new_item;
    return true;
}

sym_stack_item* symbol_stack_top_terminal(sym_stack* stack) {

    sym_stack_item* iterator = stack->top;

    while (iterator){
        if (iterator->symbol < STOP){
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

bool symbol_stack_insert_after_top_terminal(sym_stack* stack, psa_table_symbol_enum symbol, data_type_t data){

    sym_stack_item* prev = NULL;
    sym_stack_item* iterator = stack->top;

    while (iterator){
        if (iterator->symbol < STOP){
            sym_stack_item *new_item = (sym_stack_item *) malloc(sizeof(sym_stack_item));
            if (!new_item){
                return false;
            }

            new_item->symbol = symbol;
            new_item->data = data;

            if (prev == NULL)
            {
                new_item->next = stack->top;
                stack->top = new_item;
            }
            else
            {
                new_item->next = prev->next;
                prev->next = new_item;
            }
            return true;
        }
        prev = iterator;
        iterator = iterator->next;
    }
    return false;
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

void symbol_stack_free(sym_stack* stack) {
    while (symbol_stack_pop(stack));
}


