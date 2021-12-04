#ifndef IFJ_BRATWURST2021_PARAMSTACK_H
#define IFJ_BRATWURST2021_PARAMSTACK_H

#include <stdbool.h>

typedef union param_attribute
{
    char* id;
    char* str;    
    int integer;
    double number;    
} param_attribute_t;

typedef enum param_type
{
    P_ID,
    P_INT,
    P_NUMBER,
    P_STR,
    P_NIL
} param_type_t;

/**
 * @struct Stack item represetation.
 */
typedef struct stack_param
{
    param_type_t type;
    param_attribute_t attribute;  
    struct stack_param *next;
} param_stack_item;

/**
 * @struct Stack representation.
 */
typedef struct
{
    param_stack_item *top;
} param_stack;

void param_stack_init (param_stack* stack);
bool param_stack_push (param_stack* stack, param_type_t param_type, param_attribute_t param_attr);
bool param_stack_pop (param_stack* stack, param_type_t* param_type, param_attribute_t* param_attr);
void param_stack_dispose (param_stack* stack);

#endif //IFJ_BRATWURST2021_PARAMSTACK_H

