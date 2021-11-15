/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Symbol stack
 *
 * Author:  Stepan Bakaj     <xbakaj00@stud.fit.vutbr.cz>
 *
 * Date:    15-11-2021
 */


#ifndef IFJ_BRATWURST2021_SYMSTACK_H
#define IFJ_BRATWURST2021_SYMSTACK_H

#include "psa.h"


/**
 * @struct Stack item represetation.
 */
typedef struct stack_item
{
    psa_table_symbol_enum symbol; /// Symbol of stack item.
    //Data_type data;               /// Data type used for semantic analysis.
    struct stack_item *next;      /// Pointer to next stack item.
} sym_stack_item;

/**
 * @struct Stack representation.
 */
typedef struct
{
    sym_stack_item *top;
} sym_stack;

/**
 * Function initializes stack.
 *
 * @param stack Pointer to stack.
 */
void sym_stack_init(sym_stack *stack);

/**
 * Function pushes symbol to stack and sets its data type.
 *
 * @param stack Pointer to stack.
 * @param symbol Symbol to be pushed.
 * @return True if successfull else false.
 */
bool symbol_stack_push(sym_stack* stack, psa_table_symbol_enum symbol);

/**
 * Function pops top symbol from stack.
 *
 * @param stack Pointer to stack.
 * @return True if successfull else false.
 */
bool symbol_stack_pop(sym_stack* stack);

/**
 * Function returns top termial.
 *
 * @param stack Pointer to stack.
 * @return Returns pointer to top terminal.
 */
sym_stack_item* symbol_stack_top_terminal(sym_stack* stack);

/**
 * Function inserts symbol after top terminal.
 *
 * @param stack Pointer to stack.
 * @param symbol Symbol to be pushed.
 * @return True if successfull else false.
 */
bool symbol_stack_insert_after_top_terminal(sym_stack* stack, psa_table_symbol_enum symbol);

/**
 * Function returns top symbol.
 *
 * @param stack Pointer to stack.
 * @return Pointer to symbol on top of stack.
 */
sym_stack_item* symbol_stack_top(sym_stack* stack);

/**
 * Function frees resources used for stack.
 *
 * @param stack Pointer to stack.
 */
void symbol_stack_free(sym_stack* stack);

#endif //IFJ_BRATWURST2021_SYMSTACK_H
