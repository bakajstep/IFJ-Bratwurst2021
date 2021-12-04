#ifndef IFJ_BRATWURST2021_PARAMSTACK_H
#define IFJ_BRATWURST2021_PARAMSTACK_H

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
    sym_stack_item *top;
} param_stack;



#endif //IFJ_BRATWURST2021_PARAMSTACK_H

