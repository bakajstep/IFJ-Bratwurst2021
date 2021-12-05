#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "scanner.h"
#include "error.h"
#include "psa.h"
#include "symtable.h"
#include "sym_linked_list.h"
#include "code_generator.h"
#include "paramstack.h"

/*TODO smazat*/
#include <stdio.h>

#define PROLOG "ifj21"
#define VALIDATE_TOKEN(token)    \
        if (!valid_token(token)) \
        {                        \
            return false;        \
        }

#define TEST_EOF(token)                      \
        if(token == NULL && err == E_NO_ERR) \
        {                                    \
            return false;                    \
        }                                    \
        
#define PUSH_PARAMS(data)                             \
        if (!push_params_code_gen(data))              \
        {                                             \
            return false;                             \
        }                                             \


/*
    NON-TERMINALS
    <prog>
    <main_b>
    <stats>
    <id_func>
    <params>
    <n_params>
    <n_ids>
    <vals>
    <n_vals>
    <as_vals>
    <ret_vals>
    <assign>
    <assign_val>
    <term>
    <args>
    <n_args>
    <arg_def_types>
    <ret_func_types>
    <ret_def_types>
    <func_types>
    <n_func_types>
    <func_def_types>
    <n_func_def_types>
    <type>
    <const>
*/
bool prog (p_data_ptr_t data);
bool main_b (p_data_ptr_t data);
bool stats (p_data_ptr_t data);
bool id_func (p_data_ptr_t data);
bool params (p_data_ptr_t data);
bool n_params (p_data_ptr_t data);
bool n_ids (p_data_ptr_t data);
bool vals (p_data_ptr_t data);
bool r_vals (p_data_ptr_t data);
bool n_vals (p_data_ptr_t data);
bool r_n_vals (p_data_ptr_t data);
bool as_vals (p_data_ptr_t data);
bool ret_vals (p_data_ptr_t data);
bool assign (p_data_ptr_t data);
bool assign_val (p_data_ptr_t data);
bool term (p_data_ptr_t data);
bool args (p_data_ptr_t data);
bool n_args (p_data_ptr_t data);
bool arg_def_types (p_data_ptr_t data);
bool ret_func_types (p_data_ptr_t data);
bool ret_def_types (p_data_ptr_t data);
bool func_types (p_data_ptr_t data);
bool n_func_types (p_data_ptr_t data);
bool func_def_types (p_data_ptr_t data);
bool a_n_func_def_types (p_data_ptr_t data);
bool r_n_func_def_types (p_data_ptr_t data);
bool type (p_data_ptr_t data);
bool constant (p_data_ptr_t data);

/* TODO 
 * todo vymazat v data returny
 */

/* TODO smazat */

void print(p_data_ptr_t data)
{
    if (data->token == NULL)
    {
        return;
    }
    
    token_t* token = data->token;

    switch (token->type) {
            case T_MUL:
                printf("T_MUL\n");
                break;
            case T_DIV:
                printf("T_DIV\n");
                break;
            case T_INT_DIV:
                printf("T_INT_DIV\n");
                break;
            case T_PLUS:
                printf("T_PLUS\n");
                break;
            case T_MINUS:
                printf("T_MINUS\n");
                break;
            case T_CHAR_CNT:
                printf("T_CHAR_CNT\n");
                break;
            case T_CONCAT:
                printf("T_CONCAT\n");
                break;
            case T_LESS_THAN:
                printf("T_LESS_THAN\n");
                break;
            case T_LESS_EQ:
                printf("T_LESS_EQ\n");
                break;
            case T_GTR_THAN:
                printf("T_GTR_THAN\n");
                break;
            case T_GTR_EQ:
                printf("T_GTR_EQ\n");
                break;
            case T_NOT_EQ:
                printf("T_NOT_EQ\n");
                break;
            case T_ASSIGN:
                printf("T_ASSIGN\n");
                break;
            case T_EQ:
                printf("T_EQ\n");
                break;
            case T_COLON:
                printf("T_COLON\n");
                break;
            case T_LEFT_BRACKET:
                printf("T_LEFT_BRACKET\n");
                break;
            case T_RIGHT_BRACKET:
                printf("T_RIGHT_BRACKET\n");
                break;
            case T_COMMA:
                printf("T_COMMA\n");
                break;
            case T_INT:
                printf("T_INT - %d\n",token->attribute.integer);
                break;
            case T_DECIMAL:
                printf("T_DECIMAL - %f\n",token->attribute.decimal);
                break;
            case T_DECIMAL_W_EXP:
                printf("T_DECIMAL_W_EXP - %f\n",token->attribute.decimal);
                break;
            case T_IDENTIFIER:
                printf("T_IDENTIFIER - %s\n",token->attribute.string);
                break;
            case T_KEYWORD:
                printf("T_KEYWORD - %d\n",token->attribute.keyword);
                break;
            case T_STRING:
                printf("T_STRING - %s\n",token->attribute.string);
                break;
        }
}

/***************** DATA FUNCTIONS ******************/

p_data_ptr_t create_data ()
{
    /* DONE free */
    return (p_data_ptr_t) malloc(sizeof(struct p_data));
}

void delete_data_param(function_params_t* param)
{
    function_params_t* current = NULL;

    while (param != NULL)
    {
        current = param;
        param = param->param_next;

        free(current->param_name);
        free(current);
    }    
}

void delete_data_ret(function_returns_t* ret)
{
    function_returns_t* current = NULL;

    while (ret != NULL)
    {
        current = ret;
        ret = ret->ret_next;

        free(current);   
    }    
}

void delete_ids_list(ids_list_t* ids_list)
{
    ids_list_t* current = NULL;

    while (ids_list != NULL)
    {
        current = ids_list;
        ids_list = ids_list->next;   

        free(current->id);
        free(current);
    }
}

void delete_tbl_list_mem(LList* tbl_list)
{
    free(tbl_list);
    tbl_list = NULL;
}

void delete_data (p_data_ptr_t data)
{
    delete_token(data->token);
    free(data->func_name);
    free(data->body_func_name);
    delete_data_param(data->param);
    delete_data_ret(data->ret);
    delete_ids_list(data->ids_list);    

    free(data);
    data = NULL;
}

void delete_symtable_data(symData_t** data)
{
    paramDispose((*data)->first_param);
    paramTypeDispose((*data)->first_type_param);
    returnDefDispose((*data)->first_def_ret);
    returnDispose((*data)->first_ret);

    (*data)->first_param = NULL;
    (*data)->first_type_param = NULL;
    (*data)->first_def_ret = NULL;
    (*data)->first_ret = NULL;

    free(*data);
}

/**************** BACKEND FUNCTIONS ****************/

void next_token(p_data_ptr_t data)
{
    delete_token(data->token);
    data->token = get_next_token();

    /* TODO smazat */
    //print(data);
}

bool valid_token (token_t* token)
{
    return (token != NULL || (token == NULL && err == E_NO_ERR));
}

bool expression (p_data_ptr_t data)
{
    return psa(data);
}

/***** SYMBOL TABLE *****/
void create_tbl_list (LList* tbl_list)
{    
    if (tbl_list == NULL)
    {        
        err = E_INTERNAL;        
    }
    else
    {
        LL_Init(tbl_list);
    }        
}

void create_sym_table (LList* tbl_list)
{
    /* DONE free */
    symTree_t* tree = (symTree_t*) malloc(sizeof(symTree_t));

    symTableInit(&tree);    

    LL_InsertLast(tbl_list, tree);
}

void create_symbol (symTree_t** tree, char* key)
{    
    symData_t* data = NULL;//(symData_t*) malloc(sizeof(symData_t));
    symDataInit(&data);

    if (err == E_NO_ERR)
    {        
        symTableInsert(tree, key, data);
        delete_symtable_data(&data);
        data = NULL;
    }    
}

void insert_parameter (LList *tbl_list, char* func_name, char* id, data_type_t data_type)
{        
    /* Get global symbol table */
    symTree_t* glb_tbl = LL_GetFirst(tbl_list); 

    /* Get row for this function in global symbol table */    
    symData_t* tbl = symTableSearch(glb_tbl, func_name);                    

    /* Insert Parameter */
    paramInsert(tbl, data_type, id);
    //printf("\nname: %s\n", tbl->first_param->param_name);
    //printf("\ntype: %d\n", tbl->first_param->param_type);    

    if (err != E_NO_ERR)
    {
        return;
    }    
    
    /* Inc parameter count */
    (tbl->params_count)++;
}

void insert_parameter_type (LList *tbl_list, char* func_name, data_type_t data_type)
{
    /* Get global symbol table */
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);

    /* Get row for this function in global symbol table */    
    symData_t* tbl = symTableSearch(glb_tbl, func_name);

    /* Insert Parameter */
    paramTypeInsert(tbl, data_type);

    if (err != E_NO_ERR)
    {
        return;
    }
    
    
    /* Inc parameter type count */
    (tbl->params_type_count)++;
}

void insert_return (LList *tbl_list, char* func_name, data_type_t data_type)
{
    /* Get global symbol table */
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);

    /* Get row for this function in global symbol table */    
    symData_t* tbl = symTableSearch(glb_tbl, func_name);

    /* Insert Parameter */
    returnInsert(tbl, data_type);

    if (err != E_NO_ERR)
    {
        return;
    }
    
    
    /* Inc parameter count */
    (tbl->returns_count)++;
}

void insert_def_return (LList *tbl_list, char* func_name, data_type_t data_type)
{
    /* Get global symbol table */
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);

    /* Get row for this function in global symbol table */    
    symData_t* tbl = symTableSearch(glb_tbl, func_name);

    /* Insert Parameter */
    returnDefInsert(tbl, data_type);

    if (err != E_NO_ERR)
    {
        return;
    }
    
    
    /* Inc parameter count */
    (tbl->returns_def_count)++;
}

/***** SEMANTIC ANALYSIS *****/
/*
 * Check first definition of identifier or function in table
 */
bool check_first_definition (symTree_t* table, char* identifier)
{
    bool ret_val = false;

    if (symTableSearch(table, identifier) == NULL)
    {
        ret_val = true;
    }
    
    return ret_val;
}

/*
 * Check conflict that identifier hasnt same name as function
 */
bool check_conflict_id_func (LList* tbl_list, char* identifier)
{
    bool ret_val = false;
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);

    if (symTableSearch(glb_tbl, identifier) == NULL)
    {
        ret_val = true;
    }
    
    return ret_val;
}

/*
 * Check if function with the same name wasnt defined
 */
bool check_function_is_not_defined (LList* tbl_list, char* func_name)
{
    bool ret_val = false;
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);
    

    symData_t* func_data = symTableSearch(glb_tbl, func_name);

    if (func_data == NULL)
    {
        ret_val = true;
    }
    else
    {
        if (func_data->defined == false)
        {
            ret_val = true;
        }        
    }

    return ret_val;    
}

bool check_no_multiple_function_declaration (LList* tbl_list, char* func_name)
{
    bool ret_val = false;
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);
    symData_t* func_data = symTableSearch(glb_tbl, func_name);

    if (func_data != NULL)
    {
        if (func_data->declared == false)
        {
            ret_val = true;
        }
    }
    else
    {
        ret_val = true;
    }    

    return ret_val;
}

/*
 * Check if function with this name is declared
 */
bool check_function_is_declared (LList* tbl_list, char* func_name)
{
    bool ret_val = false;
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);
    symData_t* func_data = symTableSearch(glb_tbl, func_name);

    if (func_data != NULL)
    {
        if (func_data->declared == true)
        {
            ret_val = true;
        }        
    }    

    return ret_val;
}

/*
 * Check that identifier is declared
 */
bool check_identifier_is_declared (LList* tbl_list, char* id)
{
    //printf("\nahoj\n");
    //printf("\ns: %s\n", tbl_list->lastElement->nextElement->root->key);

    bool ret_val = false;
    struct LLElement* elem = tbl_list->lastElement;
    symData_t* table_elem;

    /*
     * Go through tables in linked list
     */    
    while (elem != NULL)
    {                                       
        table_elem = symTableSearch(elem->root, id);        

        /*
         * Check if identifier is in table
         */                        
        if (table_elem != NULL)
        {                                                      
            if (table_elem->declared == true)
            {
                ret_val = true;                
            }

            //break;            
        }        

        elem = elem->nextElement;        
    }
     
    return ret_val;
}

/*
 * Check that identifier is defined
 */
bool check_identifier_is_defined (LList* tbl_list, char* id)
{
    bool ret_val = false;
    struct LLElement* elem = tbl_list->lastElement;
    symData_t* table_elem;

    /*
     * Go through tables in linked list
     */    
    while (elem != NULL)
    {                
        table_elem = symTableSearch(elem->root, id);        
        /*
         * Check if identifier is in table
         */                
        //printf("\njsem zde\n");
        if (table_elem != NULL)
        {                            
          //  printf("\nprvek je v tabulce\n");                            
            if (table_elem->defined == true)
            {                
                ret_val = true;                
            }

            //break;            
        }        

        elem = elem->nextElement;        
    }
        
    return ret_val;
}

void set_identifier_defined (LList* tbl_list, char* id)
{    
    struct LLElement* elem = tbl_list->lastElement;
    symData_t* table_elem;

    /*
     * Go through tables in linked list
     */    
    while (elem != NULL)
    {
        table_elem = symTableSearch(elem->root, id);

        if (table_elem != NULL)
        {
            table_elem->defined = true;
            break;
        }        

        elem = elem->nextElement;
    }    
}

data_type_t identifier_type (LList* tbl_list, char* id)
{    
    LLElementPtr elem = tbl_list->lastElement;
    symData_t* table_elem;
    data_type_t id_data_type = NIL;

    /*
     * Go through tables in linked list
     */
    while (elem != NULL)
    {
        table_elem = symTableSearch(elem->root, id);

        /*
         * Check if identifier is in table
         */
        if (table_elem != NULL)
        {            
            id_data_type = table_elem->data_type;           

            break;            
        }

        elem = elem->nextElement;        
    }

    return id_data_type;            
}

/*
 * Check list of parameters of function declaration and function definition
 */
bool check_function_is_declared_before (LList* tbl_list, char* func_name)
{
    bool ret_val = false;
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);
    symData_t* func_data = symTableSearch(glb_tbl, func_name);

    if (func_data != NULL)
    {
        if (func_data->declared == true)
        {
            ret_val = true;
        }        
    }
    
    return ret_val;
}

bool check_function_dec_def_params_list (unsigned params_type_count,
                                         function_params_t* first_type_param,
                                         unsigned params_count,
                                         function_params_t* first_param)
{
    bool ret_val = true;
    function_params_t* elem_declaration = NULL;
    function_params_t* elem_definition = NULL;

    //printf("\nparams_type_count: %d, params_count: %d\n", params_type_count, params_count);        

    /*
     * Identical count of parameters
     */
    if (params_type_count == params_count)
    {
        elem_declaration = first_type_param;
        elem_definition = first_param;

        while (elem_declaration != NULL && elem_definition != NULL)
        {
            if (elem_declaration->param_type != elem_definition->param_type)
            {
                ret_val = false;
                break;
            }
            
            elem_declaration = elem_declaration->param_next;            
            elem_definition = elem_definition->param_next;
        }
    }
    else
    {
        ret_val = false;
    }
    
    return ret_val;
}

bool check_function_dec_def_returns_list (unsigned returns_dec_count,
                                          function_returns_t* first_dec_return,
                                          unsigned returns_def_count,
                                          function_returns_t* first_def_return)
{
    bool ret_val = true;
    function_returns_t* elem_declaration = NULL;
    function_returns_t* elem_definition = NULL;
    
    //printf("\nreturns_dec_count: %d, returns_def_count: %d\n", returns_dec_count, returns_def_count);    

    if (returns_dec_count == returns_def_count)
    {        
        elem_declaration = first_dec_return;
        elem_definition = first_def_return;

        while (elem_declaration != NULL && elem_definition != NULL)
        {
            if (elem_declaration->return_type != elem_definition->return_type)
            {
                ret_val = false;
                break;
            }

            elem_declaration = elem_declaration->ret_next;
            elem_definition = elem_definition->ret_next;
        }                
    }
    else
    {
        ret_val = false;
    }    

    return ret_val;
}

/*
 * Check if function is declared but not defined then
 */
bool func_is_not_def (symTree_t* tree)
{
    if (tree != NULL)
    {
        if (tree->data->declared == true && tree->data->defined == false)
        {
            return false;
        }
        else
        {
            if (!func_is_not_def(tree->nextLeft))
            {
                return false;
            }
            
            if (!func_is_not_def(tree->nextRight))
            {
                return false;
            }       
        }
    }

    return true;    
}

bool is_func(LList* tbl_list, char* id)
{
    bool ret_val = false;
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);  
    
    if (symTableSearch(glb_tbl, id) != NULL)
    {
        ret_val = true;
    }
    
    return ret_val;
}

void copy_params_to_func_table (LList* tbl_list, char* func_name)
{    
    //symTree_t* func_tbl = LL_GetLast(tbl_list);
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);    
    function_params_t* elem = symTableSearch(glb_tbl, func_name)->first_param;
    symData_t* in_tbl_param_data;                

    while (elem != NULL)
    {                       
        /* INSERT PARAM TO FUNC TABLE */                
        // Add param to table
        //printf("\nfunc name: %s\n", func_name);
        create_symbol(&(tbl_list->lastElement->root), elem->param_name);

        if (err != E_NO_ERR)
        {
            return;
        }

        // Get param in table data
        in_tbl_param_data = symTableSearch(tbl_list->lastElement->root, elem->param_name);
        
        // Add data type to param in table
        in_tbl_param_data->data_type = elem->param_type;

        // Set parameter as defined in table - because have value from function call
        in_tbl_param_data->defined = true;

        /* END OF INSERT */

        elem = elem->param_next;
    }

   // printf("\nlocal param: %s\n", tbl_list->lastElement->root->key);        
}

bool check_func_assign (p_data_ptr_t data)
{
    bool ret_val = true;
    function_returns_t* func_returns = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_ret;            
    
    while (func_returns != NULL && data->ids_list != NULL)
    {                
        if (func_returns->return_type != data->ids_list->type)
        {       
            if (func_returns->return_type == NIL ||
                (data->ids_list->type == NUMBER && func_returns->return_type == INT))
            {
                // VALID
            }
            else
            {                                     
                err = E_SEM_PARAM;
                ret_val = false;
                break;
            }            
        }

        set_identifier_defined(data->tbl_list, data->ids_list->id);
        
        //symTableSearch(LL_GetLast(data->tbl_list), data->ids_list->id)->defined = true;
        
        func_returns = func_returns->ret_next;
        data->ids_list = data->ids_list->next;
    }
    /* The function returns fewer values ​​than the variables expect */
    if (func_returns == NULL && data->ids_list != NULL)
    {          
        err = E_SEM_PARAM;
        ret_val = false;
    }    
    
    return ret_val;
}

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

void create_tbl_list_mem (LList** tbl_list)
{
    /* DONE free */
    *tbl_list = (LList*) malloc(sizeof(LList));

    if (*tbl_list == NULL)
    {
        err = E_INTERNAL;
    }    
}

bool push_params_code_gen(p_data_ptr_t data)
{    
    param_type_t* param_type = NULL;
    param_attribute_t* param_attr = NULL;

    param_type = (param_type_t*) malloc(sizeof(param_type_t));

    if (param_type == NULL)
    {
        err = E_INTERNAL;                            
        return false;
    }
    

    param_attr = (param_attribute_t*) malloc(sizeof(union param_attribute));


    if (param_attr == NULL)
    {                            
        free(param_type);
        err = E_INTERNAL;
        return false;
    }                        
                                                    
    while (param_stack_pop(data->stack, param_type, param_attr))
    {        
        switch (*param_type)
        {
        case P_ID:            
            codeGen_push_var(param_attr->id);
            break;
        
        case P_INT:
            codeGen_push_int(param_attr->integer);
            break;

        case P_NUMBER:
            codeGen_push_float(param_attr->number);
            break;

        case P_STR:            
            //printf("\npush string: %s\n", param_attr->str);
            codeGen_push_string(param_attr->str);
            break;

        case P_NIL:
            codeGen_push_nil();
            break;

        default:
            break;
        }
    }

    param_stack_dispose(data->stack);

    if (*param_type == P_ID)
    {
        free(param_attr->id);
    }
    else if (*param_type == P_STR)
    {
        free(param_attr->str);
    }

    free(param_attr);                        
    free(param_type);    

    return true;
}

void insert_built_in_functions (LList* tbl_list)
{    
    tbl_list = tbl_list;    
    symTree_t* glb_tbl = NULL;//(symTree_t*) malloc(sizeof(symTree_t));        

    // TODO
    // function reads (): string
    symData_t* data = NULL;
    symDataInit(&data);
    data->defined = true;
    data->returns_count = 1;
    returnInsert(data, STR);
    symTableInsert(&glb_tbl, "reads", data);
    delete_symtable_data(&data);
    data = NULL;           

    // function readi (): integer
    symDataInit(&data);
    data->defined = true;
    data->returns_count = 1;
    returnInsert(data, INT);                        
    symTableInsert(&glb_tbl, "readi", data);
    delete_symtable_data(&data);
    data = NULL;    

    // function readn (): number
    symDataInit(&data);
    data->defined = true;
    data->returns_count = 1;
    returnInsert(data, NUMBER);
    symTableInsert(&glb_tbl, "readn", data);
    delete_symtable_data(&data);
    data = NULL;

    // function write (term_1, term_2, ..., term_n)
    symDataInit(&data);
    data->defined = true;    
    symTableInsert(&glb_tbl, "write", data);
    delete_symtable_data(&data);
    data = NULL;

    // function tointeger (f : number) : integer

    symDataInit(&data);
    data->defined = true;
    data->returns_count = 1;
    data->params_count = 1;
    paramInsert(data, NUMBER, "f");    
    returnInsert(data, INT);
    symTableInsert(&glb_tbl, "tointeger", data);
    delete_symtable_data(&data);
    data = NULL;

    // function substr (s : string, i : number, j : number) : string

    symDataInit(&data);
    data->defined = true;
    data->returns_count = 1;
    data->params_count = 3;
    paramInsert(data, STR, "s");
    paramInsert(data, NUMBER, "i");
    paramInsert(data, NUMBER, "j");
    returnInsert(data, STR);
    symTableInsert(&glb_tbl, "substr", data);
    delete_symtable_data(&data);
    data = NULL;

    // function ord (s : string, i : integer) : integer

    symDataInit(&data);
    data->defined = true;
    data->returns_count = 1;
    data->params_count = 2;
    paramInsert(data, STR, "s");
    paramInsert(data, INT, "i");
    returnInsert(data, INT);
    symTableInsert(&glb_tbl, "ord", data);
    delete_symtable_data(&data);
    data = NULL;

    // function chr (i : integer) : string

    symDataInit(&data);
    data->defined = true;
    data->returns_count = 1;
    data->params_count = 1;
    paramInsert(data, INT, "i");
    returnInsert(data, STR);
    symTableInsert(&glb_tbl, "chr", data);
    delete_symtable_data(&data);
    data = NULL;

    tbl_list->lastElement->root = glb_tbl; 

    /* -------------- CODE GEN --------------*/

    codeGen_built_in_function();

    /* ----------- END OF CODE GEN ----------*/
}

/******************* PARSER MAIN *******************/
/*
 * Parser main function
 */
parser_error_t parser ()
{    
    err = E_NO_ERR;
    p_data_ptr_t data;    

    data = create_data();

    if (!data)
    {
        err = E_INTERNAL;
        delete_data(data);

        return PARSE_ERR;
    }
    
    data->token = get_next_token();

    /* TODO smazat */
    //print(data);
    
    if (!valid_token(data->token))
    {                         
        err = E_SYNTAX; 
        delete_data(data);

        return PARSE_ERR;
    }
    
    /* -------------- SEMANTIC --------------*/
    
    create_tbl_list_mem(&(data->tbl_list));

    if (err != E_NO_ERR)
    {
        return PARSE_ERR;
    }    

    // Create linked list with symbol tables
    create_tbl_list(data->tbl_list);

    if (err != E_NO_ERR)
    {
        return PARSE_ERR;
    }    

    // Create global symbol table
    create_sym_table(data->tbl_list);        

    /* ----------- END OF SEMANTIC ----------*/    

    if (!prog(data))
    {
        if (err == E_NO_ERR)
        {                                                                                 
            err = E_SYNTAX;
        }
        
        delete_tbl_list_mem(data->tbl_list);
        delete_data(data);        

        return PARSE_ERR;
    }
    
    delete_tbl_list_mem(data->tbl_list);
    delete_data(data);

    return PARSE_NO_ERR;
}

/*************** NON-TERMINALS RULES ***************/

/*
 * NON-TERMINAL: <prog>
 *
 * RULES:
 * 1. <prog> -> require “ifj21” <main_b>
 */
bool prog (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;       

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;    

    if (token_type == T_KEYWORD && data->token->attribute.keyword == K_REQUIRE)
    {        
        next_token(data);        
        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);

        token_type = data->token->type;

        if (token_type == T_STRING &&
            strcmp(data->token->attribute.string, PROLOG) == 0)
        {            
            next_token(data);            

            /* -------------- SEMANTIC --------------*/
            
            data->func_name = NULL;
            data->body_func_name = NULL;
            data->param = NULL;
            data->ret = NULL;
            data->ids_list = NULL;                        
            
            /* ----------- END OF SEMANTIC ----------*/

            /* -------------- CODE GEN --------------*/

            data->write_params_cnt = 0;

            data->stack = (param_stack*) malloc(sizeof(param_stack));

            if (data->stack == NULL)
            {
                err = E_INTERNAL;
                return false;
            }

            codeGen_init();

            /* ----------- END OF CODE GEN ----------*/

            /* -------------- SEMANTIC --------------*/

            // Insert built in functions
            insert_built_in_functions(data->tbl_list); 

            /* ----------- END OF SEMANTIC ----------*/    

            if (main_b(data))
            {                                
                ret_val = true;
            }

            free(data->stack);            

            /* -------------- SEMANTIC --------------*/

            if (data->tbl_list != NULL)
            {
                LL_Dispose(data->tbl_list);
            }            

            /* ----------- END OF SEMANTIC ----------*/                  
        }                                
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <main_b>
 *
 * RULES:       
 * 2. <main_b> -> function id (<params>) <ret_func_types> <stats> end <main_b>
 * 3. <main_b> -> global id : function (<arg_def_types>) <ret_def_types> <main_b>
 * 4. <main_b> -> id (<args>) <main_b>
 * 5. <main_b> -> epsilon
 */
bool main_b (p_data_ptr_t data)
{    
    bool ret_val = false;
    token_type_t token_type;    
    symTree_t* tree = NULL;    
    symData_t* function_declaration_data = NULL;
    symData_t* func_code_gen = NULL;
    function_params_t* param_val = NULL;
    char* func_name = NULL;
    unsigned params_count_code_gen = 0;

    /* Create tree

    //tree = (symTree_t*) malloc(sizeof(symTree_t));

    if (tree == NULL)
    {
        err = E_INTERNAL;
        return false;
    }
    

    End of create tree */

    VALIDATE_TOKEN(data->token);

    /* 5. <main_b> -> epsilon */
    if (data->token == NULL)
    {
        /* -------------- SEMANTIC --------------*/
        
        tree = LL_GetFirst(data->tbl_list);
        
        if (!func_is_not_def(tree))
        {            
            //printf("ESD: %d\n", 1);
            err = E_SEM_DEF;
            return false;
        }        

        /* ----------- END OF SEMANTIC ----------*/

        /* EOF */
        ret_val = true;
    }
    else
    {
        token_type = data->token->type;        

        /* 2. <main_b> -> function id (<params>) <ret_func_types> <stats> end <main_b> */
        if (token_type == T_KEYWORD && data->token->attribute.keyword == K_FUNCTION)
        {           
            next_token(data);
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;

            if (token_type == T_IDENTIFIER)
            {   
                /* -------------- SEMANTIC --------------*/

                /* TODO pokud funkce jiz byla deklarovana - tabulka symbolu*/

                // Save function name to data->func_name
                /* Malloc data->func_name */

                if (data->func_name != NULL)
                {
                    free(data->func_name);
                }
                
                /* DONE free */
                data->func_name = (char*) malloc(strlen(data->token->attribute.string) + 1); // TODO pak realloc

                if (data->func_name == NULL)
                {
                    err = E_INTERNAL;
                    return false;
                }                

                strcpy(data->func_name, data->token->attribute.string);         

                if (data->body_func_name != NULL)
                {
                    free(data->body_func_name);
                }

                data->body_func_name = (char*) malloc(strlen(data->func_name) + 1);

                if (data->body_func_name == NULL)
                {
                    err = E_INTERNAL;
                    return false;
                }              

                strcpy(data->body_func_name, data->func_name);

                /*
                 * Check multiple definition of function
                 */
                if (!check_function_is_not_defined(data->tbl_list, data->func_name))
                {                    
                    //printf("\nESD: %d\n", 2);
                    err = E_SEM_DEF;
                    return false;
                }                                    

                tree = LL_GetFirst(data->tbl_list);                 

                /*
                 * Function has declaration before (global id : function ...)
                 */
                if (check_function_is_declared_before (data->tbl_list, data->func_name))
                {
                    function_declaration_data = symTableSearch(tree, data->func_name);
                }
                else
                {
                    //function_declaration_data = NULL;
                    // Add symbol to table                
                    create_symbol(&tree, data->func_name);
                }                
                //create_symbol(&tree, func_name);

                if (err != E_NO_ERR)
                {
                    return false;
                }                

                // Set function as defined
                symTableSearch(tree, data->func_name)->defined = true;

                // Create symbol table for function
                create_sym_table(data->tbl_list);                                                
                
                /* ----------- END OF SEMANTIC ----------*/

                func_name = (char*) malloc(strlen(data->func_name)+1);

                if (func_name == NULL)
                {
                    err = E_INTERNAL;
                    return false;
                }
                
                strcpy(func_name, data->func_name);

                /* -------------- CODE GEN --------------*/
                 
                codeGen_function_start(func_name);

                /* ----------- END OF CODE GEN ----------*/

                next_token(data);
                VALIDATE_TOKEN(data->token);
                TEST_EOF(data->token);
                token_type = data->token->type;

                if (token_type == T_LEFT_BRACKET)
                {
                    next_token(data);                

                    if (params(data))
                    {
                        /*
                        * Check if function has declaration before definition
                        */
                        if (function_declaration_data != NULL)
                        {
                            tree = LL_GetFirst(data->tbl_list);
                            symData_t* func_def = symTableSearch(tree, data->func_name);
                            
                            /*
                            * Check params lists of function declaration and definition
                            */                                                                
                            if (!check_function_dec_def_params_list (function_declaration_data->params_type_count,
                                                                        function_declaration_data->first_type_param,
                                                                        func_def->params_count,
                                                                        func_def->first_param))
                            {
                                //printf("\nESD: %d\n", 3);
                                err = E_SEM_DEF;                                
                                return false;
                            }                                                                                               
                        }

                        //printf("\ndata func name: %s\n", data->func_name);                                                                                  
                        /* Copy parameters to function symbol table as they are local variables */
                        copy_params_to_func_table(data->tbl_list, data->func_name);

                     //   printf("\ntbl: %s\n", data->tbl_list->lastElement->root->key);

                        if (err != E_NO_ERR)
                        {
                            free(func_name);
                            return false;
                        }

                        /* ----------- END OF SEMANTIC ----------*/

                        VALIDATE_TOKEN(data->token);
                        TEST_EOF(data->token);
                        token_type = data->token->type;

                        if (token_type == T_RIGHT_BRACKET)
                        {                            
                            next_token(data);                                        

                            if (ret_func_types(data))
                            {     
                                /* -------------- SEMANTIC --------------*/

                                /*
                                * Check if function has declaration before definition
                                */
                                if (function_declaration_data != NULL)
                                {
                                    tree = LL_GetFirst(data->tbl_list);
                                    symData_t* func_def = symTableSearch(tree, data->func_name);                                                                        
                                    
                                    /*
                                    * Check returns lists of function declaration and definition
                                    */
                                    if (!check_function_dec_def_returns_list (function_declaration_data->returns_def_count,
                                                                              function_declaration_data->first_def_ret,
                                                                              func_def->returns_count,
                                                                              func_def->first_ret))
                                    {
                                        //printf("\nESD: %d\n", 4);
                                        err = E_SEM_DEF;
                                        free(func_name);
                                        return false;
                                    }                                                                    
                                }
                                                        
                                /* ----------- END OF SEMANTIC ----------*/

                                if (stats(data))
                                {                                    
                                    VALIDATE_TOKEN(data->token);
                                    TEST_EOF(data->token);
                                    token_type = data->token->type;                                

                                    if (token_type == T_KEYWORD && data->token->attribute.keyword == K_END)
                                    {
                                        /* -------------- SEMANTIC --------------*/
                                        
                                        // Deleting the table representing function block from the linked list
                                        LL_DeleteLast(data->tbl_list);

                                        /* ----------- END OF SEMANTIC ----------*/

                                        /* -------------- CODE GEN --------------*/
                 
                                        codeGen_function_end(func_name);

                                        /* ----------- END OF CODE GEN ----------*/

                                        next_token(data);                                
                                        
                                        if (main_b(data))
                                        {
                                            ret_val = true;
                                        }                                
                                    }
                                }                                                                                                                     
                            }                        
                        }                    
                    }                
                }            
            }  

            free(func_name);          
        }        
        /* 3. <main_b> -> global id : function (<arg_def_types>) <ret_def_types> <main_b> */
        else if (token_type == T_KEYWORD && data->token->attribute.keyword == K_GLOBAL)
        {
            next_token(data);
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;

            if (token_type == T_IDENTIFIER)
            {
                /* -------------- SEMANTIC --------------*/

                /* TODO pokud funkce jiz byla deklarovana */

                if (!check_no_multiple_function_declaration(data->tbl_list, data->token->attribute.string))
                {         
                    //printf("\nESD: %d\n", 5);           
                    err = E_SEM_DEF;
                    return false;
                }

                // Add symbol to table
                tree = LL_GetFirst(data->tbl_list);
                create_symbol(&tree, data->token->attribute.string);

                if (err != E_NO_ERR)
                {
                    return false;
                }

                // Create symbol table for function
                //create_sym_table(data->tbl_list);

                // Save function name to data->func_name

                if (data->func_name != NULL)
                {
                    free(data->func_name);
                }

                /* DONE free */
                data->func_name = (char *) malloc(strlen(data->token->attribute.string) + 1);

                if (data->func_name == NULL)
                {
                    err = E_INTERNAL;
                    return false;
                }                

                strcpy(data->func_name, data->token->attribute.string);
                
                /* ----------- END OF SEMANTIC ----------*/

                next_token(data);
                VALIDATE_TOKEN(data->token);
                TEST_EOF(data->token);
                token_type = data->token->type;

                if (token_type == T_COLON)
                {
                    next_token(data);
                    VALIDATE_TOKEN(data->token);
                    TEST_EOF(data->token);
                    token_type = data->token->type;                    

                    if (token_type == T_KEYWORD && data->token->attribute.keyword == K_FUNCTION)
                    {
                        next_token(data);
                        VALIDATE_TOKEN(data->token);
                        TEST_EOF(data->token);
                        token_type = data->token->type;

                        if (token_type == T_LEFT_BRACKET)
                        {
                            next_token(data);

                            if (arg_def_types(data))
                            {                                                                
                                VALIDATE_TOKEN(data->token);
                                TEST_EOF(data->token);
                                token_type = data->token->type;

                                if (token_type == T_RIGHT_BRACKET)
                                {
                                    next_token(data);

                                    if (ret_def_types(data))
                                    {
                                        ret_val = main_b(data);
                                    }                                
                                }                            
                            }                        
                        }                    
                    }                
                }            
            }        
        }    
        /* 4. <main_b> -> id (<args>) <main_b> */
        else if (token_type == T_IDENTIFIER)
        {
            if (data->func_name != NULL)
            {
                free(data->func_name);
            }

            /* DONE free */
            data->func_name = (char *) malloc(strlen(data->token->attribute.string) + 1);

            if (data->func_name == NULL)
            {
                err = E_INTERNAL;
                return false;
            }

            strcpy(data->func_name, data->token->attribute.string);  

            /* -------------- SEMANTIC --------------*/

            /*
             * Check if called function is declared
             */
            if (!check_function_is_declared(data->tbl_list, data->func_name))
            {
                //printf("\nESD: %d\n", 6);
                err = E_SEM_DEF;
                return false;
            }

            if (data->param != NULL)
            {
                delete_data_param(data->param);
            }            

            if ((param_val = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_type_param) != NULL)
            {
                data->param = param_val;
            }
            else
            {
                data->param = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_param;
            }                        

            /* ----------- END OF SEMANTIC ----------*/

            next_token(data);
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;

            if (token_type == T_LEFT_BRACKET)
            {
                next_token(data);

                data->write_params_cnt = 0;

                param_stack_init(data->stack);

                if (args(data))
                {
                    VALIDATE_TOKEN(data->token);
                    TEST_EOF(data->token);
                    token_type = data->token->type;

                    if (token_type == T_RIGHT_BRACKET)
                    {
                        /* -------------- CODE GEN --------------*/

                        /* Push function call params */

                        PUSH_PARAMS(data);                                                                    
                        
                        /* End of push function call params */

                        if (strcmp(data->func_name, "write") != 0)
                        {
                            func_code_gen = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name);                        
                        
                            if (func_code_gen->params_type_count >= func_code_gen->params_count)
                            {
                                params_count_code_gen = func_code_gen->params_type_count;
                            }
                            else
                            {
                                params_count_code_gen = func_code_gen->params_count;
                            }                                                
                        }
                        else
                        {
                            params_count_code_gen = data->write_params_cnt;
                        }                                        

                        // printf("\nhodnota parametru: %d\n", params_count_code_gen);

                        codeGen_function_call(data->func_name, params_count_code_gen);

                        /* ----------- END OF CODE GEN ----------*/

                        next_token(data);

                        if (main_b(data))
                        {
                            ret_val = true;
                        }                    
                    }                
                }            
            }        
        }
    }          

    return ret_val;
}

/*
 * NON-TERMINAL: <stats>
 *
 * RULES:       
 * 6. <stats> -> local id : <type> <assign> <stats>
 * 7. <stats> -> if exp then <stats> else <stats> end <stats>
 * 8. <stats> -> while exp do <stats> end <stats>
 * 9. <stats> -> return <ret_vals> <stats>
 * 10. <stats> -> id <id_func> <stats>
 * 11. <stats> -> epsilon
 */
bool stats (p_data_ptr_t data)
{        
    bool ret_val = false;
    token_type_t token_type;    
    symTree_t* tree = NULL;
    data_type_t data_type;
    char* id = NULL;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;    

    /* 6. <stats> -> local id : <type> <assign> <stats> */
    if (token_type == T_KEYWORD && data->token->attribute.keyword == K_LOCAL)
    {                                             
        next_token(data);
        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);
        token_type = data->token->type;

        if (token_type == T_IDENTIFIER)
        {            
            /* -------------- SEMANTIC --------------*/ 
            /* DONE free */
            id = (char *) malloc(strlen(data->token->attribute.string) + 1);
            strcpy(id, data->token->attribute.string);
            tree = LL_GetLast(data->tbl_list);            
            

        
            //printf("\n tree: %s \n", tree->key);
                        

            if (!check_first_definition(tree, id))
            {
                //printf("\nESD: %d\n", 7);
                err = E_SEM_DEF;
                free(id);
                return false;
            }

            if (!check_conflict_id_func(data->tbl_list, id))
            {
                //printf("\nESD: %d\n", 8);
                err = E_SEM_DEF;
                free(id);
                return false;
            }
                        
            create_symbol(&tree, id);                        

            //printf("\n tree: %s \n", tree->key);

            if (err != E_NO_ERR)
            {
                free(id);
                return false;
            }
                
            /* ----------- END OF SEMANTIC ----------*/

            /* -------------- CODE GEN --------------*/

            codeGen_new_var(id);            
            //codeGen_assign_var(id);

            /* ----------- END OF CODE GEN ----------*/

            if (data->func_name != NULL)
            {
                free(data->func_name);
            }

            /* DONE free */
            data->func_name = (char *) malloc(strlen(id) + 1);

            if (data->func_name == NULL)
            {
                err = E_INTERNAL;
                return false;
            }

            strcpy(data->func_name, id);            

            next_token(data);
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;

            if (token_type == T_COLON)
            {                                   
                next_token(data);

                if (type(data))
                {
                    /* -------------- SEMANTIC --------------*/
                    // Set identifier data type
                    symTableSearch(tree, id)->data_type = data->type;    
                
                    /* ----------- END OF SEMANTIC ----------*/

                    data->tbl_list->lastElement->root = tree;                    
                    /* TODO uncomment */
                    delete_ids_list(data->ids_list);  
                    data->ids_list = NULL;
                    
                    /* Insert id to ids_list */
                    //printf("\ndata func name: %s\n", data->func_name);
                    /* TODO uncomment */
                    idInsert(&(data->ids_list), data->type, data->func_name);                    
                    
                    if (assign(data))
                    {
                        /* -------------- SEMANTIC --------------*/

                        data_type = symTableSearch(tree, id)->data_type;

                        //printf("\n psa_data_type: %d\n", data->psa_data_type);

                        if (data_type != data->psa_data_type)
                        {
                            if (data->psa_data_type == NIL || 
                                (data_type == NUMBER && data->psa_data_type == INT))
                            {
                                // VALID                                
                            }
                            else
                            {                          
                                //printf("\ndata_type: %d, psa_data_type: %d\n", data_type, data->psa_data_type);                                                                                            
                                err = E_SEM_ASSIGN;
                                free(id);
                                return false;
                            }                                                        
                        }                                                

                        symTableSearch(tree, id)->defined = true;                          

                        /* ----------- END OF SEMANTIC ----------*/

                        if (stats(data))
                        {                            
                            ret_val = true;    
                        }                        
                    }                    
                }                            
            }

            free(id);         
        } // if (token_type == T_IDENTIFIER)       
    }    
    /* 7. <stats> -> if exp then <stats> else <stats> end <stats> */
    else if (token_type == T_KEYWORD && data->token->attribute.keyword == K_IF)
    {        
        next_token(data);
        
        if (expression(data))
        {
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;            

            if (token_type == T_KEYWORD && data->token->attribute.keyword == K_THEN)
            {                
                /* -------------- SEMANTIC --------------*/                    
        
                // Create symbol table for if block
                create_sym_table(data->tbl_list);   

                /* ----------- END OF SEMANTIC ----------*/

                /* -------------- CODE GEN --------------*/
                 
                codeGen_if_start();

                /* ----------- END OF CODE GEN ----------*/

                next_token(data);

                if (stats(data))
                {
                    VALIDATE_TOKEN(data->token);
                    TEST_EOF(data->token);
                    token_type = data->token->type;                    

                    if (token_type == T_KEYWORD && data->token->attribute.keyword == K_ELSE)
                    {                        
                        /* -------------- SEMANTIC --------------*/
                                    
                        // Deleting the table representing if block
                        LL_DeleteLast(data->tbl_list);

                        // Create symbol table for else block
                        create_sym_table(data->tbl_list);   

                        /* ----------- END OF SEMANTIC ----------*/

                        /* -------------- CODE GEN --------------*/
                 
                        codeGen_if_else();

                        /* ----------- END OF CODE GEN ----------*/

                        next_token(data);

                        if (stats(data))
                        {
                            VALIDATE_TOKEN(data->token);
                            TEST_EOF(data->token);
                            token_type = data->token->type;                            

                            if (token_type == T_KEYWORD && data->token->attribute.keyword == K_END)
                            {
                                /* -------------- SEMANTIC --------------*/
                                    
                                // Deleting the table representing else block
                                LL_DeleteLast(data->tbl_list);                        

                                /* ----------- END OF SEMANTIC ----------*/

                                /* -------------- CODE GEN --------------*/
                 
                                codeGen_if_end();

                                /* ----------- END OF CODE GEN ----------*/

                                next_token(data);

                                if (stats(data))
                                {
                                    ret_val = true;
                                }                                
                            }
                        }                        
                    }                    
                }                
            }            
        }        
    }    
    /* 8. <stats> -> while exp do <stats> end <stats> */
    else if (token_type == T_KEYWORD && data->token->attribute.keyword == K_WHILE)
    {        
        /* -------------- CODE GEN --------------*/
                 
        codeGen_while_body_start();

        /* ----------- END OF CODE GEN ----------*/

        next_token(data);

        if (expression(data))
        {
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;              

            if (token_type == T_KEYWORD && data->token->attribute.keyword == K_DO)
            {
                /* -------------- SEMANTIC --------------*/                    
        
                // Create symbol table for while block
                create_sym_table(data->tbl_list);   

                /* ----------- END OF SEMANTIC ----------*/

                /* -------------- CODE GEN --------------*/
                 
                codeGen_while_start();

                /* ----------- END OF CODE GEN ----------*/

                next_token(data);

                if (stats(data))
                {
                    VALIDATE_TOKEN(data->token);
                    TEST_EOF(data->token);
                    token_type = data->token->type;                       

                    if (token_type == T_KEYWORD && data->token->attribute.keyword == K_END)
                    {
                        /* -------------- SEMANTIC --------------*/
                                    
                        // Deleting the table representing while block
                        LL_DeleteLast(data->tbl_list);                        

                        /* ----------- END OF SEMANTIC ----------*/

                        /* -------------- CODE GEN --------------*/
                 
                        codeGen_while_end();

                        /* ----------- END OF CODE GEN ----------*/

                        next_token(data);
                        
                        if (stats(data))
                        {
                            ret_val = true;
                        }                        
                    }                    
                }                
            }            
        }        
    }    
    /* 9. <stats> -> return <ret_vals> <stats> */
    else if (token_type == T_KEYWORD && data->token->attribute.keyword == K_RETURN)
    {        
        next_token(data);

        if (ret_vals(data))
        {            
            ret_val = stats(data);
        }        
    }    
    /* 10. <stats> -> id <id_func> <stats> */
    else if (token_type == T_IDENTIFIER)
    {        
        if (data->func_name != NULL)
        {
            free(data->func_name);
        }

        /* DONE free */
        data->func_name = (char *) malloc(strlen(data->token->attribute.string) + 1);

        if (data->func_name == NULL)
        {
            err = E_INTERNAL;
            return false;
        }

        strcpy(data->func_name, data->token->attribute.string);        

        next_token(data);  

        /* -------------- SEMANTIC --------------*/

        /*
         * Check if called function/identifier is declared
         */

        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);
        token_type = data->token->type;

        if (token_type == T_LEFT_BRACKET)
        {
            if (!check_function_is_declared(data->tbl_list, data->func_name))
            {
                //printf("\nESD: %d\n", 9);
                err = E_SEM_DEF;
                return false;
            }      
        }
        else if (token_type == T_COMMA || token_type == T_ASSIGN)
        {     
            //printf("\nhello\n");
            //printf("\ns: %s\n", data->tbl_list->lastElement->nextElement->root->key);
            if (!check_identifier_is_declared(data->tbl_list, data->func_name))
            {                
                //printf("\nESD: %d\n", 9);
                err = E_SEM_DEF;
                return false;
            }                          
            
            delete_ids_list(data->ids_list);  
            data->ids_list = NULL;

            // printf("\ninserting id : %s\n", data->func_name);

            idInsert(&(data->ids_list), identifier_type(data->tbl_list, data->func_name), data->func_name);                                    
            //printf("\ndata ids list: %s\n", data->ids_list->id);
        }
        /*else
        {
            return false;
        } */                       

        if (err != E_NO_ERR)
        {
            return false;
        }        

        /* ----------- END OF SEMANTIC ----------*/                

        //printf("\ndata ids list: %s\n", data->ids_list->id);

        if (id_func(data))
        {                        
            ret_val = stats(data);
        }
    }    
    /* 11. <stats> -> epsilon */
    else if (token_type == T_KEYWORD)
    {
        if (data->token->attribute.keyword == K_END ||
            data->token->attribute.keyword == K_ELSE)
        {
            ret_val = true;
        }                
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <id_func>
 *
 * RULES:       
 * 12. <id_func> -> <n_ids> = <as_vals>
 * 13. <id_func> -> (<args>)
 */
bool id_func (p_data_ptr_t data)
{                        
    bool ret_val = false;
    token_type_t token_type;
    symData_t* func_code_gen = NULL;
    function_params_t* param_val = NULL;
    unsigned params_count_code_gen = 0;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;
      
    /* 13. <id_func> -> (<args>) */
    if (token_type == T_LEFT_BRACKET)
    {     
        /* -------------- SEMANTIC --------------*/           
        
        if (data->param != NULL)
        {
            delete_data_param(data->param);
        }

        //data->param = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_param;
        if ((param_val = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_type_param) != NULL)
        {
            data->param = param_val;
        }
        else
        {
            data->param = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_param;
        }         

        /* ----------- END OF SEMANTIC ----------*/

        next_token(data);

        data->write_params_cnt = 0;

        param_stack_init(data->stack);

        if (args(data))
        {              
            VALIDATE_TOKEN(data->token); 
            TEST_EOF(data->token); 
            token_type = data->token->type;

            if (token_type == T_RIGHT_BRACKET)
            {
                /* -------------- CODE GEN --------------*/

                /* Push function call params */

                PUSH_PARAMS(data);                                                                    
                        
                /* End of push function call params */

                if (strcmp(data->func_name, "write") != 0)
                {
                    func_code_gen = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name);                        
                
                    if (func_code_gen->params_type_count >= func_code_gen->params_count)
                    {
                        params_count_code_gen = func_code_gen->params_type_count;
                    }
                    else
                    {
                        params_count_code_gen = func_code_gen->params_count;
                    }                                                
                }                
                else
                {
                    params_count_code_gen = data->write_params_cnt;
                }

                //printf("\nhodnota parametru: %d\n", params_count_code_gen);
                codeGen_function_call(data->func_name, params_count_code_gen);

                /* ----------- END OF CODE GEN ----------*/

                ret_val = true;
                next_token(data);
            }                
        }            
    }
    /* 12. <id_func> -> <n_ids> = <as_vals> */
    else
    {        
        /* -------------- CODE GEN --------------*/

        //codeGen_assign_var(data->func_name);        

        /* ----------- END OF CODE GEN ----------*/

        if (n_ids(data))
        {            
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;

            if (token_type == T_ASSIGN)
            {
                next_token(data);
   
                ret_val = as_vals(data);
            }        
        }           
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <params>
 *
 * RULES:        
 * 14. <params> -> id : <type> <n_params>
 * 15. <params> -> epsilon
 */
bool params (p_data_ptr_t data)
{    
    bool ret_val = false;    
    token_type_t token_type;
    char* id = NULL;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 14. <params> -> id : <type> <n_params> */
    if (token_type == T_IDENTIFIER)
    {
        // Ulozeni jmena parametru
        /* DONE free */
        id = (char*) malloc(strlen(data->token->attribute.string) + 1);
        strcpy(id, data->token->attribute.string);        

        next_token(data);
        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);
        token_type = data->token->type;

        if (token_type == T_COLON)
        {
            next_token(data);
            
            if (type(data))
            {   
                /* -------------- SEMANTIC --------------*/

                // Vlozeni noveho parametru funkce    
               // printf("\nfunc_name: %s, id: %s, type: %d\n", data->func_name, id, data->type);                                           
                insert_parameter(data->tbl_list, data->func_name, id, data->type);

                if (err != E_NO_ERR)
                {
                    free(id);
                    return false;
                }                

                /* ----------- END OF SEMANTIC ----------*/            

                /* -------------- CODE GEN --------------*/

                codeGen_new_var(id);
                codeGen_assign_var(id);

                /* ----------- END OF CODE GEN ----------*/

                ret_val = n_params(data);
            }            
        }        
    }    
    /* 15. <params> -> epsilon */
    else if (token_type == T_RIGHT_BRACKET)
    {
        ret_val = true;
    }    

    free(id);

    return ret_val;
}

/*
 * NON-TERMINAL: <n_params>
 *
 * RULES:     
 * 16. <n_params> -> , id : <type> <n_params>
 * 17. <n_params> -> epsilon
 */
bool n_params (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;
    char* id = NULL;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 16. <n_params> -> , id : <type> <n_params> */
    if (token_type == T_COMMA)
    {
        next_token(data);
        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);

        token_type = data->token->type;

        if (token_type == T_IDENTIFIER)
        {
            // Ulozeni jmena parametru
            /* DONE free */
            id = (char*) malloc(strlen(data->token->attribute.string) + 1);
            strcpy(id, data->token->attribute.string);    

            next_token(data);
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;

            if (token_type == T_COLON)
            {
                next_token(data);

                if (type(data))
                {            
                    /* -------------- SEMANTIC --------------*/

                    // Vlozeni noveho parametru funkce 
                  //  printf("\nfunc_name: %s, id: %s, type: %d\n", data->func_name, id, data->type);                                                                
                    insert_parameter(data->tbl_list, data->func_name, id, data->type);

                    if (err != E_NO_ERR)
                    {
                        free(id);
                        return false;
                    }                

                    /* ----------- END OF SEMANTIC ----------*/    

                    /* -------------- CODE GEN --------------*/

                    codeGen_new_var(id);
                    codeGen_assign_var(id);

                    /* ----------- END OF CODE GEN ----------*/

                    ret_val = n_params(data);
                } 
            } 

            free(id);              
        } // if (token_type == T_IDENTIFIER)                     
    }    
    /* 17. <n_params> -> epsilon */
    else if (token_type == T_RIGHT_BRACKET)
    {
        ret_val = true;
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <n_ids>
 *
 * RULES:       
 * 18. <n_ids> -> , id <n_ids>
 * 19. <n_ids> -> epsilon
 */
bool n_ids (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 18. <n_ids> -> , id <n_ids> */
    if (token_type == T_COMMA)
    {
        next_token(data);
        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);

        token_type = data->token->type;

        if (token_type == T_IDENTIFIER)
        {            
            /* -------------- SEMANTIC --------------*/

            /*
             * Check if identifier is declared
             */
            if (!check_identifier_is_declared(data->tbl_list, data->token->attribute.string))
            {
                //printf("\nESD: %d\n", 10);
                err = E_SEM_DEF;
                return false;
            }

            // printf("\ninserting id : %s\n", data->token->attribute.string);

            //printf("\nfirst id: %s\n", data->ids_list->id);

            idInsert(&(data->ids_list), identifier_type(data->tbl_list, data->token->attribute.string), data->token->attribute.string);            

            if (err != E_NO_ERR)
            {
                return false;
            }

            /* ----------- END OF SEMANTIC ----------*/

            /* -------------- CODE GEN --------------*/

            //codeGen_assign_var(data->token->attribute.string);

            /* ----------- END OF CODE GEN ----------*/

            next_token(data);
            ret_val = n_ids(data);
        }                
    }
    /* 19. <n_ids> -> epsilon */
    else if (token_type == T_ASSIGN)
    {
        ret_val = true;
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <vals>
 *
 * RULES:       
 * 20. <vals> -> exp <n_vals>
 */
bool vals (p_data_ptr_t data)
{
    bool ret_val = false;

    /* 20. <vals> -> exp <n_vals> */
    if (expression(data))
    {        
        /* -------------- SEMANTIC --------------*/    
        
        if (data->ids_list != NULL)
        {
            if (data->psa_data_type != data->ids_list->type)
            {
                if (data->psa_data_type == NIL ||
                    (data->ids_list->type == NUMBER && data->psa_data_type == INT))
                {
                    // VALID                    
                }
                else
                {                                        
                    err = E_SEM_ASSIGN;
                    return false;
                }
            }

            set_identifier_defined(data->tbl_list, data->ids_list->id);
            //symTableSearch(LL_GetLast(data->tbl_list), data->ids_list->id)->defined = true;

            /* -------------- CODE GEN --------------*/

            codeGen_assign_var(data->ids_list->id);

            /* ----------- END OF CODE GEN ----------*/

            data->ids_list = data->ids_list->next;
        }                        
        else
        {                      
            err = E_SEM_ASSIGN;
            return false;
        }        
        
        /* ----------- END OF SEMANTIC ----------*/        

        ret_val = n_vals(data);
    }        

    return ret_val;
}

bool r_vals (p_data_ptr_t data)
{
    bool ret_val = false;
    symTree_t* glb_tbl;
    symData_t* func_data;

    /* 20. <vals> -> exp <n_vals> */
    if (expression(data))
    {
        /* -------------- SEMANTIC --------------*/
        
        glb_tbl = LL_GetFirst(data->tbl_list);
        func_data = symTableSearch(glb_tbl, data->body_func_name);

        //printf("\ndata func name: %s\n", data->body_func_name);

        if (data->ret != NULL)
        {
            delete_data_ret(data->ret);
        }

        data->ret = func_data->first_ret;

        if (data->ret != NULL)
        {            
            if (data->psa_data_type != data->ret->return_type)
            {           
                if (data->psa_data_type == NIL || 
                    (data->ret->return_type == NUMBER && data->psa_data_type == INT))
                {
                    // VALID
                }
                else
                {                                                
                    err = E_SEM_PARAM;
                    return false;             
                }                       
            }   

            data->ret = data->ret->ret_next;
        }
        else
        {
            // data->param == NULL
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);

            /*
             * Excess count of return values
             */
            if (data->token->type == T_COMMA)
            {                                
                err = E_SEM_PARAM;
                return false;
            }
        }
              
        /* ----------- END OF SEMANTIC ----------*/

        ret_val = r_n_vals(data);
    }    
    else
    {
        if (err == E_NO_ERR)
        {
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);

            if (data->token->type == T_ASSIGN)
            {
                next_token(data);

                ret_val = as_vals(data);
            }      
        }
        else
        {
            err = E_NO_ERR;
        }   
    }

    return ret_val;
}

/*
 * NON-TERMINAL: <n_vals>
 *
 * RULES:     
 * 21. <n_vals> -> , exp <n_vals>
 * 22. <n_vals> -> epsilon
 */
bool n_vals (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;    

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 22. <n_vals> -> epsilon */
    if ((token_type == T_KEYWORD) && 
        (data->token->attribute.keyword == K_ELSE))
    {
        ret_val = true;
    }
    else if (stats(data))
    {
        ret_val = true;
    }    
    else
    {        
        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);

        token_type = data->token->type;

        /* 21. <n_vals> -> , exp <n_vals> */    
        if (token_type == T_COMMA)
        {
            next_token(data);        

            if (expression(data))
            {
                /* -------------- SEMANTIC --------------*/    
                if (data->ids_list != NULL)
                {
                    if (data->psa_data_type != data->ids_list->type)
                    {
                        if (data->psa_data_type == NIL ||
                            (data->ids_list->type == NUMBER && data->psa_data_type == INT))
                        {
                            // VALID
                        }
                        else
                        {                                                       
                            err = E_SEM_ASSIGN;
                            return false;
                        }
                    }

                    set_identifier_defined(data->tbl_list, data->ids_list->id);

                    /* -------------- CODE GEN --------------*/

                    codeGen_assign_var(data->ids_list->id);

                    /* ----------- END OF CODE GEN ----------*/

                    data->ids_list = data->ids_list->next;
                }                        
                else
                {     
                    //printf("\nhere error 4\n");                  
                    err = E_SEM_ASSIGN;
                    return false;
                }        
                
                /* ----------- END OF SEMANTIC ----------*/

                ret_val = n_vals(data);
            }                   
        }           
    }
    
    return ret_val;
}

bool r_n_vals (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;    

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);
    
    token_type = data->token->type;

    /* 21. <n_vals> -> , exp <n_vals> */    
    if (token_type == T_COMMA)
    {
        next_token(data);        

        if (expression(data))
        {
            /* -------------- SEMANTIC --------------*/                   

            if (data->ret != NULL)
            {
                if (data->psa_data_type != data->ret->return_type)
                {
                    if (data->psa_data_type == NIL || 
                        (data->ret->return_type == NUMBER && data->psa_data_type == INT))
                    {
                        // VALID
                    }
                    else
                    {                                                          
                        err = E_SEM_PARAM;
                        return false;             
                    }                           
                }   

                data->ret  = data->ret->ret_next;
            }             
            else
            {
                // data->param == NULL
                VALIDATE_TOKEN(data->token);
                TEST_EOF(data->token);

                /*
                    * Excess count of return values
                    */
                if (data->token->type == T_COMMA)
                {                                              
                    err = E_SEM_PARAM;
                    return false;
                }   
            }                                            

            /* ----------- END OF SEMANTIC ----------*/

            ret_val = r_n_vals(data);
        }      
        else
        {
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);

            if (data->token->type == T_ASSIGN)
            {
                next_token(data);    
                         
                ret_val = as_vals(data);
            }        
        }  
    } 
    /* 22. <n_vals> -> epsilon */
    else
    {
        /* -------------- CODE GEN --------------*/

        codeGen_function_return();

        /* ----------- END OF CODE GEN ----------*/
       
        if ((token_type == T_KEYWORD) && 
            (data->token->attribute.keyword == K_ELSE))
        {                
            ret_val = true;
        }            
        else if (stats(data))
        {
            ret_val = true;
        }                    
    }     
    
    return ret_val;
}

/*
 * NON-TERMINAL: <as_vals>
 *
 * RULES:       
 * 23. <as_vals> -> <vals>
 * 24. <as_vals> -> id (<args>)
 */
bool as_vals (p_data_ptr_t data)
{                
    bool ret_val = false;
    token_type_t token_type;
    symData_t* func_code_gen = NULL;
    unsigned params_count_code_gen = 0;
    ids_list_t* ids_list_copy = NULL;
    function_params_t* param_val = NULL;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);
    token_type = data->token->type;

    /* 24. <as_vals> -> id (<args>) */
    if (token_type == T_IDENTIFIER)
    {
        if (data->func_name != NULL)
        {
            free(data->func_name);
        }

        /* DONE free */
        data->func_name = (char *) malloc(strlen(data->token->attribute.string) + 1);

        if (data->func_name == NULL)
        {
            err = E_INTERNAL;
            return false;
        }

        strcpy(data->func_name, data->token->attribute.string);
        
        if (!is_func(data->tbl_list, data->func_name))
        {
            /* Identifier is not function name and is a part of expression */
            if (vals(data))
            {
                ret_val = true;
            }
        }                
        else
        {            
            /* -------------- SEMANTIC --------------*/ 
            /*
             * Check if called function is declared
             */       
            if (!check_function_is_declared(data->tbl_list, data->func_name))
            {
                //printf("\nESD: %d\n", 11);
                err = E_SEM_DEF;
                return false;
            }

            if (data->param != NULL)
            {
                delete_data_param(data->param);
            }

            /* For args */
            //data->param = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_param;
            if ((param_val = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_type_param) != NULL)
            {
                data->param = param_val;
            }
            else
            {
                data->param = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_param;
            }   

            /* Saving ids list */
            
            save_ids_list(data->ids_list, &ids_list_copy);

            /* End of saving ids list */

            /* For assign to identifiers */
            if (!check_func_assign(data))
            {                                   
                err = E_SEM_PARAM;
                return false;
            }        

            /* ----------- END OF SEMANTIC ----------*/

            /* Is added */
            next_token(data);
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;                
            
            if (token_type == T_LEFT_BRACKET)
            {
                next_token(data);

                data->write_params_cnt = 0;

                param_stack_init(data->stack);

                if (args(data))
                {                                   
                    VALIDATE_TOKEN(data->token);
                    TEST_EOF(data->token);
                    token_type = data->token->type;

                    if (token_type == T_RIGHT_BRACKET)
                    {                        
                        /* -------------- CODE GEN --------------*/

                        /* Push function call params */

                        PUSH_PARAMS(data);                                                                    
                        
                        /* End of push function call params */

                        if (strcmp(data->func_name, "write") != 0)
                        {
                            func_code_gen = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name);                        
                        
                            if (func_code_gen->params_type_count >= func_code_gen->params_count)
                            {
                                params_count_code_gen = func_code_gen->params_type_count;
                            }
                            else
                            {
                                params_count_code_gen = func_code_gen->params_count;
                            }        
                        }
                        else
                        {
                            params_count_code_gen = data->write_params_cnt;
                        }                                                                                    
                        
                        codeGen_function_call(data->func_name, params_count_code_gen);                                                                                                
                        
                        while (ids_list_copy != NULL)
                        {                            
                            codeGen_assign_var(ids_list_copy->id);
                            ids_list_copy = ids_list_copy->next;
                        }       
                        
                        /* ----------- END OF CODE GEN ----------*/

                        ret_val = true;
                        next_token(data);
                    }                
                }            
            }                        
        }                                
    }            
    /* 23. <as_vals> -> <vals> */
    else if (vals(data))
    {
        /* -------------- SEMANTIC --------------*/ 
        
        if (data->ids_list != NULL)
        {            
            err = E_SEM_ASSIGN;
            return false;
        }
        
        /* ----------- END OF SEMANTIC ----------*/
        ret_val = true;
    }

    return ret_val;
}

/*
 * NON-TERMINAL: <ret_vals>
 *
 * RULES:       
 * 25. <ret_vals> -> <vals>
 * 26. <ret_vals> -> epsilon
 */
bool ret_vals (p_data_ptr_t data)
{
    bool ret_val = false;            
    token_type_t token_type;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);    
    
    token_type = data->token->type;

    /* 25. <ret_vals> -> <vals> */ 
    if (r_vals(data))
    {        
        ret_val = true;
    }
    /* 26. <ret_vals> -> epsilon */
    else
    {
        if (err == E_NO_ERR)
        {
            /* -------------- CODE GEN --------------*/

            codeGen_function_return();

            /* ----------- END OF CODE GEN ----------*/

            if ((token_type == T_KEYWORD) && 
                (data->token->attribute.keyword == K_ELSE))
            {                
                ret_val = true;
            }            
            else if (stats(data))
            {
                ret_val = true;
            }        
        }                
    }              

    return ret_val;
}

/*
 * NON-TERMINAL: <assign>
 *
 * RULES:       
 * 27. <assign> -> = <assign_val>
 * 28. <assign> -> epsilon
 */
bool assign (p_data_ptr_t data)
{        
    bool ret_val = false;
    token_type_t token_type;    

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    //printf("\nassign key: %s\n", data->tbl_list->lastElement->root->key);

    /* 28. <assign> -> epsilon */
    if ((token_type == T_KEYWORD) && 
        (data->token->attribute.keyword == K_ELSE))
    {
        data->psa_data_type = NIL;                
        ret_val = true;
    }    
    else if (stats(data))
    {    
        data->psa_data_type = NIL;                
        ret_val = true;
    }
    else
    {              
        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);     

        token_type = data->token->type;

        /* 27. <assign> -> = <assign_val> */
        if (token_type == T_ASSIGN)
        {
            next_token(data);            
            ret_val = assign_val(data);            
        }                   
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <assign_val>
 *
 * RULES:       
 * 29. <assign_val> -> exp
 * 30. <assign_val> -> id (<args>)
 */
bool assign_val (p_data_ptr_t data)
{    
    bool ret_val = false;
    token_type_t token_type;
    symData_t* func_data;
    symData_t* func_code_gen = NULL;
    char* func_name = NULL;
    function_params_t* param_val = NULL;
    unsigned params_count_code_gen = 0;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);
    token_type = data->token->type;

    /* 30. <assign_val> -> id (<args>) */    
    if (token_type == T_IDENTIFIER)
    {    
        /*
        if (data->func_name != NULL)
        {
            free(data->func_name);
        }
        */
        /* DONE free */
        func_name = (char *) malloc(strlen(data->token->attribute.string) + 1);
        strcpy(func_name, data->token->attribute.string);

        if (!is_func(data->tbl_list, func_name))
        {
            if (expression(data))
            {
                /* -------------- CODE GEN --------------*/

                codeGen_assign_var(data->func_name);

                /* ----------- END OF CODE GEN ----------*/

                ret_val = true;
            }
        }                
        else
        {   
            /* Is added */
            next_token(data);         
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;            

            if (token_type != T_LEFT_BRACKET)
            {
                /* Not function call */
                /* TODO mozna smazat */
                if (err == E_INTERNAL)
                {                                                                                
                    err = E_SYNTAX;
                }
                                
                free(func_name);
                return false;
            }
            else
            {                 
                /* TODO mozna smazat */               
                err = E_NO_ERR;
            }            
             
            /* -------------- SEMANTIC --------------*/ 
            /*
             * Check if called function is declared
             */       
            if (!check_function_is_declared(data->tbl_list, func_name))
            {
                //printf("\nESD: %d\n", 12);
                err = E_SEM_DEF;
                free(func_name);
                return false;
            }
        
            if (data->param != NULL)
            {
                delete_data_param(data->param);
            }                        

            func_data = symTableSearch(LL_GetFirst(data->tbl_list), func_name);
            //data->param = func_data->first_param;    

            if ((param_val = func_data->first_type_param) != NULL)
            {
                data->param = param_val;
            }
            else
            {
                data->param = func_data->first_param;
            }    

            if (func_data->first_ret != NULL)
            {
                data->psa_data_type = func_data->first_ret->return_type;                
            }
            else
            {        
                if (func_data->first_def_ret != NULL)
                {
                    data->psa_data_type = func_data->first_def_ret->return_type;                
                }
                else
                {
                    //printf("here E_SEM_PARAM");     
                    err = E_SEM_PARAM;
                    free(func_name);
                    return false;
                }                
            }                        

            data->func_name = (char*) malloc(strlen(func_name) + 1);

            if (data->func_name == NULL)
            {
                err = E_INTERNAL;
                free(func_name);
                return false;
            }            

            strcpy(data->func_name, func_name);                
            
            /* ----------- END OF SEMANTIC ----------*/

            //VALIDATE_TOKEN(data->token);
            //TEST_EOF(data->token);
            //token_type = data->token->type;

            //if (token_type == T_LEFT_BRACKET)
            //{
            next_token(data);

            data->write_params_cnt = 0;

            param_stack_init(data->stack);

            if (args(data))
            {           
                VALIDATE_TOKEN(data->token); 
                TEST_EOF(data->token);    
                token_type = data->token->type;

                if (token_type == T_RIGHT_BRACKET)
                {
                    /* -------------- CODE GEN --------------*/

                    /* Push function call params */

                    PUSH_PARAMS(data);                                                                    
                       
                    /* End of push function call params */

                    if (strcmp(data->func_name, "write") != 0)
                    {
                        func_code_gen = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name);                        
                    
                        if (func_code_gen->params_type_count >= func_code_gen->params_count)
                        {
                            params_count_code_gen = func_code_gen->params_type_count;
                        }
                        else
                        {
                            params_count_code_gen = func_code_gen->params_count;
                        }                                                
                    }
                    else
                    {
                        params_count_code_gen = data->write_params_cnt;
                    }

                    codeGen_function_call(data->func_name, params_count_code_gen);
                            
                    //printf("\nto pop: %s\n", data->ids_list->id);                                                           
                    codeGen_assign_var(data->ids_list->id);

                    data->ids_list = data->ids_list->next;
                                            
                    /* ----------- END OF CODE GEN ----------*/

                    ret_val = true;
                    next_token(data);
                }                
            }            
            //}
        }                        
    }    
    /* 29. <assign_val> -> exp */
    else if (expression(data))
    {     
        /* -------------- CODE GEN --------------*/

        codeGen_assign_var(data->func_name);

        /* ----------- END OF CODE GEN ----------*/

        ret_val = true;
    }        

    free(func_name);

    return ret_val;
}

/*
 * NON-TERMINAL: <term>
 *
 * RULES:        
 * 31. <term> -> id
 * 32. <term> -> <const>
 */
bool term (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;
    param_attribute_t* attribute = NULL;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 31. <term> -> id */
    if (token_type == T_IDENTIFIER)
    {        
        /* -------------- SEMANTIC --------------*/        
        if (!check_identifier_is_defined(data->tbl_list, data->token->attribute.string))
        {            

            //printf("\nESD: %d\n", 13);
            err = E_SEM_DEF;
            return false;
        }
        
        data->type = identifier_type(data->tbl_list, data->token->attribute.string);
        
        /* ----------- END OF SEMANTIC ----------*/

        /* -------------- CODE GEN --------------*/

        //printf("\npushing: %s\n", data->token->attribute.string);

        //codeGen_push_var(data->token->attribute.string);
        
        attribute = (param_attribute_t*) malloc(sizeof(param_attribute_t));

        if (attribute == NULL)
        {
            err = E_INTERNAL;
            return false;
        }
        
        attribute->id = data->token->attribute.string;

        param_stack_push(data->stack, P_ID, *attribute);

        free(attribute);

        /* ----------- END OF CODE GEN ----------*/

        ret_val = true;
        next_token(data);
    }
    /* 32. <term> -> <const> */
    else if (constant(data))
    {
        /* -------------- CODE GEN --------------*/

        attribute = (param_attribute_t*) malloc(sizeof(param_attribute_t));

        if (attribute == NULL)
        {
            err = E_INTERNAL;
            return false;
        }
                        
        switch (data->type)
        {
        case INT:
            attribute->integer = data->token->attribute.integer;
            param_stack_push(data->stack, P_INT, *attribute);

            break;
        
        case NUMBER:
            attribute->number = data->token->attribute.decimal;
            param_stack_push(data->stack, P_NUMBER, *attribute);

            break;

        case STR:
            attribute->str = data->token->attribute.string;
            param_stack_push(data->stack, P_STR, *attribute);

            break;

        default:            
            break;
        }

        free(attribute);

        /* ----------- END OF CODE GEN ----------*/

        next_token(data);
        ret_val = true;                
    }           

    return ret_val;
}

/*
 * NON-TERMINAL: <args>
 *
 * RULES:       
 * 33. <args> -> <term> <n_args>
 * 34. <args> -> epsilon
 */
bool args (p_data_ptr_t data)
{        
    bool ret_val = false;
    token_type_t token_type;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 34. <args> -> epsilon */
    if (token_type == T_RIGHT_BRACKET)
    {
        /* -------------- SEMANTIC --------------*/        
        if (data->param != NULL)
        {                                
            err = E_SEM_PARAM;
            return false;
        }        
        
        /* ----------- END OF SEMANTIC ----------*/

        ret_val = true;
    }                
    /* 33. <args> -> <term> <n_args> */    
    else if (term(data))
    {             
        //printf("\nfunc name: %s\n", data->func_name);
        /* -------------- SEMANTIC --------------*/
        if (strcmp(data->func_name, "write") != 0)
        {
            if (data->param != NULL)
            {
                if (data->param->param_type != data->type)
                {
                    if (data->type == NIL ||
                        (data->param->param_type == NUMBER && data->type == INT))
                    {
                        // VALID
                    }
                    else
                    {                                                                           
                        err = E_SEM_PARAM;
                        return false;
                    }                                
                }
                
                data->param = data->param->param_next;        
            }
            else
            {                                                
                //printf("\nhere\n"); 
                return false;
            }
        }   
        else
        {
            (data->write_params_cnt)++;
        }                             
        
        /* ----------- END OF SEMANTIC ----------*/        

        ret_val = n_args(data);
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <n_args>
 *
 * RULES:     
 * 35. <n_args> -> , <term> <n_args>
 * 36. <n_args> -> epsilon
 */
bool n_args (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 35. <n_args> -> , <term> <n_args> */ 
    if (token_type == T_COMMA)
    {
        next_token(data);

        if (term(data))
        {
            /* -------------- SEMANTIC --------------*/            
            if (strcmp(data->func_name, "write") != 0)
            {                
                if (data->param != NULL)
                {
                    if (data->param->param_type != data->type)
                    {
                        if (data->type == NIL ||
                            (data->param->param_type == NUMBER && data->type == INT))
                        {
                            // VALID
                        }
                        else
                        {                            
                            err = E_SEM_PARAM;
                            return false;
                        }                       
                    }
                    
                    data->param = data->param->param_next;        
                }
                else
                {                    
                    err = E_SEM_PARAM;
                    return false;
                }
            }
            else
            {
                (data->write_params_cnt)++;
            }                                                            
            
            /* ----------- END OF SEMANTIC ----------*/

            ret_val = n_args(data);
        }        
    }
    /* 36. <n_args> -> epsilon */
    else if (token_type == T_RIGHT_BRACKET)
    {        
        /* -------------- SEMANTIC --------------*/        
        if (data->param != NULL)
        {                 
            err = E_SEM_PARAM;
            return false;
        }        
        
        /* ----------- END OF SEMANTIC ----------*/

        ret_val = true;
    }               

    return ret_val;
}

/*
 * NON-TERMINAL: <arg_def_types>
 *
 * RULES:      
 * 37. <arg_def_types> -> <func_def_types>
 * 38. <arg_def_types> -> epsilon
 */
bool arg_def_types (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;
    
    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    data->arg_ret = ARG_DEF_TYPE;

    token_type = data->token->type;

    /* 38. <arg_def_types> -> epsilon*/  
    if (token_type == T_RIGHT_BRACKET)
    {
        ret_val = true;
    }   
    /* 37. <arg_def_types> -> <func_def_types> */       
    else if (func_def_types(data))
    {
        ret_val = true;
    }

    return ret_val;
}

/*
 * NON-TERMINAL: <ret_func_types>
 * 
 * RULES:       
 * 39. <ret_func_types> -> : <func_types>
 * 40. <ret_func_types> -> epsilon
 */
bool ret_func_types (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;    

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    /* 40. <ret_func_types> -> epsilon */
    if (stats(data))
    {
        ret_val = true;
    }
    else
    {
        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);

        token_type = data->token->type;

        /* 39. <ret_func_types> -> : <func_types> */
        if (token_type == T_COLON)
        {                
            next_token(data);
            ret_val = func_types(data);
        }                    
    }    
    
    return ret_val;
}

/*
 * NON-TERMINAL: <ret_def_types>
 *
 * RULES:       
 * 41. <ret_def_types> -> : <func_def_types>
 * 42. <ret_def_types> -> epsilon
 */
bool ret_def_types (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;    

    VALIDATE_TOKEN(data->token);    

    /* 42. <ret_def_types> -> epsilon */   
    if (main_b(data))
    {
       ret_val = true;
    }
    else
    {     
        if (err == E_NO_ERR)
        {
            token_type = data->token->type;

            /* 41. <ret_def_types> -> : <func_def_types> */ 
            if (token_type == T_COLON)
            {
                next_token(data);

                data->arg_ret = RET_DEF_TYPE;

                ret_val = func_def_types(data);
            }   
        }                   
    }

    return ret_val;
}

/*
 * NON-TERMINAL: <func_types>
 *
 * RULES:       
 * 43. <func_types> -> <type>  <n_func_types>
 */
bool func_types (p_data_ptr_t data)
{
    bool ret_val = false;

    if (type(data))
    {        
        /* -------------- SEMANTIC --------------*/

        // Vlozeni noveho parametru funkce                                                       
        insert_return(data->tbl_list, data->func_name, data->type);

        if (err != E_NO_ERR)
        {
            return false;
        }
        
        /* ----------- END OF SEMANTIC ----------*/            


        ret_val = n_func_types(data);
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <n_func_types>
 *
 * RULES:      
 * 44. <n_func_types> -> , <type>  <n_func_types>
 * 45. <n_func_types> -> epsilon
 */
bool n_func_types (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;    

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    /* 45. <n_func_types> -> epsilon */  
    if (stats(data))
    {
        ret_val = true;
    }
    else
    {
        VALIDATE_TOKEN(data->token);
        TEST_EOF(data->token);

        token_type = data->token->type;

        /* 44. <n_func_types> -> , <type>  <n_func_types> */ 
        if (token_type == T_COMMA)
        {
            next_token(data);        
            
            if (type(data))
            {            

            /* -------------- SEMANTIC --------------*/

            // Vlozeni noveho parametru funkce                                                       
            insert_return(data->tbl_list, data->func_name, data->type);

            if (err != E_NO_ERR)
            {
                return false;
            }

            /* ----------- END OF SEMANTIC ----------*/ 

                ret_val = n_func_types(data);
            } 
        }            
    }    
    
    return ret_val;
}

/*
 * NON-TERMINAL: <func_def_types>
 *
 * RULES: 
 * 46. <func_def_types> -> <type>  <n_func_def_types>
 */
bool func_def_types (p_data_ptr_t data)
{    
    bool ret_val = false;    
                           
    if (type(data))
    {                
        /* -------------- SEMANTIC --------------*/
        
        if (data->arg_ret == ARG_DEF_TYPE)
        {
            // Vlozeni noveho parametru funkce                                               
            insert_parameter_type(data->tbl_list, data->func_name, data->type);

            if (err != E_NO_ERR)
            {
                return false;
            }

            ret_val = a_n_func_def_types(data);
            
        }
        else
        {
            // Vlozeni noveho parametru funkce                                                       
            insert_def_return(data->tbl_list, data->func_name, data->type);

            if (err != E_NO_ERR)
            {
                return false;
            }

            ret_val = r_n_func_def_types(data);
        }

        /* ----------- END OF SEMANTIC ----------*/        
    }            

    return ret_val;            
}

/*
 * NON-TERMINAL: <n_func_def_types>
 *
 * RULES:
 * 47. <n_func_def_types> -> , <type>  <n_func_def_types>
 * 48. <n_func_def_types> -> epsilon
 */
bool a_n_func_def_types (p_data_ptr_t data)
{
    bool ret_val = false;    
    token_type_t token_type;    

    VALIDATE_TOKEN(data->token);

    token_type = data->token->type;

    /* 48. <n_func_def_types> -> epsilon */
    if (token_type == T_RIGHT_BRACKET)
    {
        ret_val = true;
    }
    else
    {
        /* 47. <n_func_def_types> -> , <type>  <n_func_def_types> */
        if (token_type == T_COMMA)
        {            
            next_token(data);        
            
            if (type(data))
            {                  
                /* -------------- SEMANTIC --------------*/        
                
                // Vlozeni noveho parametru funkce                                               
                insert_parameter_type(data->tbl_list, data->func_name, data->type);

                if (err != E_NO_ERR)
                {
                    return false;
                }
                                 
                /* ----------- END OF SEMANTIC ----------*/

                ret_val = a_n_func_def_types(data);
            }                 
        }            
    }
        
    return ret_val;        
}

/*
 * NON-TERMINAL: <n_func_def_types>
 *
 * RULES:
 * 47. <n_func_def_types> -> , <type>  <n_func_def_types>
 * 48. <n_func_def_types> -> epsilon
 */
bool r_n_func_def_types (p_data_ptr_t data)
{
    bool ret_val = false;    
    token_type_t token_type;    

    VALIDATE_TOKEN(data->token);

    /* 48. <n_func_def_types> -> epsilon */
    if (main_b(data))
    {
        ret_val = true;
    }
    else
    {
        if (err == E_NO_ERR)
        {
            token_type = data->token->type;

            /* 47. <n_func_def_types> -> , <type>  <n_func_def_types> */
            if (token_type == T_COMMA)
            {            
                next_token(data);        
                
                if (type(data))
                {                  
                    /* -------------- SEMANTIC --------------*/        
                    
                    // Vlozeni noveho parametru funkce                                                       
                    insert_def_return(data->tbl_list, data->func_name, data->type);

                    if (err != E_NO_ERR)
                    {
                        return false;
                    }               
    
                    /* ----------- END OF SEMANTIC ----------*/

                    ret_val = r_n_func_def_types(data);
                }                 
            }   
        }                                    
    }
        
    return ret_val;        
}

/*
 * NON-TERMINAL: <type>
 * 
 * RULES: 
 * 49. <type> -> integer
 * 50. <type> -> number
 * 51. <type> -> string
 */
bool type (p_data_ptr_t data)
{
    bool ret_val = false;    
    token_type_t token_type;
    keyword_t keyword;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    if (token_type == T_KEYWORD)
    {        
        keyword = data->token->attribute.keyword;

        if (keyword == K_INTEGER ||
            keyword == K_NUMBER ||
            keyword == K_STRING)
        {                  
            switch (keyword)
            {
            case K_INTEGER:
                data->type = INT;
                break;

            case K_NUMBER:
                data->type = NUMBER;
                break;

            case K_STRING:
                data->type = STR;
                break;

            default:                
                break;
            }

            ret_val = true;
            next_token(data);
        }        
    }
    
    return ret_val;
}

/*
 * NON-TERMINAL: <const>
 * 
 * RULES:       
 * 52. <const> -> int_value
 * 53. <const> -> double_value
 * 54. <const> -> string_value
 * 55. <const> -> nil
 */
bool constant (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    if (token_type == T_INT ||
        token_type == T_DECIMAL ||
        token_type == T_DECIMAL_W_EXP ||
        token_type == T_STRING ||
        (token_type == T_KEYWORD && 
         data->token->attribute.keyword == K_NIL))
    {
        /* -------------- SEMANTIC --------------*/
        switch (token_type)
        {
        case T_INT:
            data->type = INT;
            break;
        
        case T_DECIMAL:
            data->type = NUMBER;
            break;

        case T_DECIMAL_W_EXP:
            data->type = NUMBER;
            break;

        case T_STRING:
            data->type = STR;
            break;    

        case T_KEYWORD:
            if (data->token->attribute.keyword == K_NIL)
            {
                data->type = NIL;
            }
            
            break;    

        default:
            break;
        }
        /* ----------- END OF SEMANTIC ----------*/

        ret_val = true;        
    }
    
    return ret_val;
}
