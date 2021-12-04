#ifndef IFJ_BRATWURST2021_PARAMSTACK_H
#define IFJ_BRATWURST2021_PARAMSTACK_H

typedef union param_attribute
{
    char* id;
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

typedef struct func_param
{
    param_type_t param;
    param_attribute_t attribute;
} func_param_t;



#endif //IFJ_BRATWURST2021_PARAMSTACK_H

