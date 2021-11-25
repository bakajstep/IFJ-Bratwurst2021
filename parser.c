#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "scanner.h"
#include "error.h"
#include "psa.h"
#include "symtable.h"
#include "sym_linked_list.h"

/*TODO smazat*/
//#include <stdio.h>

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
bool n_func_def_types (p_data_ptr_t data);
bool type (p_data_ptr_t data);
bool constant (p_data_ptr_t data);

/* TODO smazat */
/*
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
*/
/***************** DATA FUNCTIONS ******************/

p_data_ptr_t create_data ()
{
    return (p_data_ptr_t) malloc(sizeof(struct p_data));
}

void delete_data (p_data_ptr_t data)
{
    delete_token(data->token);

    free(data);
    data = NULL;
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
    LL_Init(tbl_list);
}

void create_sym_table (LList* tbl_list)
{
    symTree_t** tree;

    symTableInit(tree);
    LL_InsertLast(tbl_list, tree);
}

void create_symbol (symTree_t** tree, char* key)
{
    symData_t* data;
    symDataInit(data);

    if (err == E_NO_ERR)
    {
        symTableInsert(tree, key, data);
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
 * Check that identifier is defined
 */
bool check_identifier_is_defined (LList* tbl_list, char* id)
{
    bool ret_val = false;
    LLElementPtr elem = tbl_list->lastElement;
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
            if (table_elem->defined == true)
            {
                ret_val = true;                
            }

            break;            
        }        

        elem = elem->nextElement;        
    }
        
    return ret_val;
}

data_type_t identifier_type (LList* tbl_list, char* id)
{    
    LLElementPtr elem = tbl_list->lastElement;
    symTree_t* table_elem;
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
            id_data_type = table_elem->data->data_type;           

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

void copy_params_to_func_table (LList* tbl_list, char* func_name)
{
    symTree_t* func_tbl = LL_GetLast(tbl_list);
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);    
    function_params_t* elem = symTableSearch(glb_tbl, func_name)->first_param;
    symData_t* in_tbl_param_data;

    while (elem != NULL)
    {
        /* INSERT PARAM TO FUNC TABLE */        
        
        // Add param to table
        create_symbol(&func_tbl, elem->param_name);

        if (err != E_NO_ERR)
        {
            return;
        }        

        // Get param in table data
        in_tbl_param_data = symTableSearch(func_tbl, elem->param_name);
        
        // Add data type to param in table
        in_tbl_param_data->data_type = elem->param_type;

        // Set parameter as defined in table - because have value from function call
        in_tbl_param_data->defined = true;

        /* END OF INSERT */

        elem = elem->param_next;
    }    
}

bool check_func_assign (p_data_ptr_t data)
{
    bool ret_val = true;
    function_returns_t* func_returns = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_ret;
    
    while (func_returns != NULL && data->ids_list != NULL)
    {                
        if (func_returns->return_type != data->ids_list->type)
        {
            err = E_SEM_PARAM;
            ret_val = false;
            break;
        }
        
        func_returns = func_returns->ret_next;
    }
    /* The function returns fewer values ​​than the variables expect */
    if (func_returns == NULL && data->ids_list != NULL)
    {
        err = E_SEM_PARAM;
        ret_val = false;
    }    
    
    return ret_val;
}

void idInsert(ids_list_t* ids_list, data_type_t type)
{
    ids_list_t* newId = (ids_list_t*) malloc(sizeof(ids_list_t));

    if(!newId){
        err = E_INTERNAL;
        return;
    }
    newId->type = type;

    if(ids_list == NULL){
        ids_list = newId;
        ids_list->next = NULL;
    }else{
        ids_list_t* current;
        current = ids_list;

        while(current != NULL){
            current = current->next;
        }
        current = newId;
        current->next = NULL;
    }
}

void insert_built_in_functions (LList* tbl_list)
{    
    symTree_t* glb_tbl = LL_GetFirst(tbl_list);    

    // TODO

    // function reads (): string   
    // function readi (): integer
    // function readn (): number

    // function write (term_1, term_2, ..., term_n)

    // function tointeger (f : number) : integer

    // function substr (s : string, i : number, j : number) : string
    // function ord (s : string, i : integer) : integer
    // function chr (i : integer) : string
}

/******************* PARSER MAIN *******************/
/*
 * Parser main function
 */
parser_error_t parser ()
{
    err = E_NO_ERR;
    p_data_ptr_t data;
    symTree_t** tree;

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

    // Create linked list with symbol tables
    create_tbl_list(data->tbl_list);
    // Create global symbol table
    create_sym_table(data->tbl_list);
    // Insert built in functions
    insert_built_in_functions(data->tbl_list);    

    /* ----------- END OF SEMANTIC ----------*/

    if (!prog(data))
    {
        if (err == E_NO_ERR)
        {
            err = E_SYNTAX;
        }
        
        delete_data(data);

        return PARSE_ERR;
    }
    
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

            if (main_b(data))
            {                                
                ret_val = true;
            }            
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
    symTree_t** tree;
    char* func_name;

    VALIDATE_TOKEN(data->token);

    /* 5. <main_b> -> epsilon */
    if (data->token == NULL)
    {
        /* -------------- SEMANTIC --------------*/
        
        (*tree) = LL_GetFirst(data->tbl_list);
        
        if (!func_is_not_def(*tree))
        {
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

                func_name = data->token->attribute.string;

                /*
                 * Check multiple definition of function
                 */
                if (!check_function_is_not_defined(data->tbl_list, func_name))
                {
                    err = E_SEM_DEF;
                    return false;
                }
                
                if (!check_no_multiple_function_declaration(data->tbl_list, func_name))
                {
                    err = E_SEM_DEF;
                    return false;
                }

                (*tree) = LL_GetFirst(data->tbl_list);                

                /*
                 * Function has declaration before (global id : function ...)
                 */
                if (check_function_is_declared_before (data->tbl_list, func_name))
                {
                    data->function_declaration_data = symTableSearch(*tree, func_name);
                }
                else
                {
                    data->function_declaration_data == NULL;
                }

                // Add symbol to table                
                create_symbol(tree, func_name);

                if (err != E_NO_ERR)
                {
                    return false;
                }

                // Set function as defined
                symTableSearch(*tree, func_name)->defined = true;

                // Create symbol table for function
                create_sym_table(data->tbl_list);

                // Save function name to data->func_name
                strcpy(data->func_name, func_name);
                
                /* ----------- END OF SEMANTIC ----------*/

                next_token(data);
                VALIDATE_TOKEN(data->token);
                TEST_EOF(data->token);
                token_type = data->token->type;

                if (token_type == T_LEFT_BRACKET)
                {
                    next_token(data);                

                    if (params(data))
                    {    
                        /* -------------- SEMANTIC --------------*/
                        
                        copy_params_to_func_table(data->tbl_list, func_name);

                        if (err != E_NO_ERR)
                        {
                            return false;
                        }

                        /* ----------- END OF SEMANTIC ----------*/

                        VALIDATE_TOKEN(data->token);
                        TEST_EOF(data->token);
                        token_type = data->token->type;

                        if (token_type == T_RIGHT_BRACKET)
                        {                            
                            next_token(data);                                        

                            if (ret_func_types(data) && stats(data))
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

            /* -------------- SEMANTIC --------------*/

            /*
             * Check if function has declaration before definition
             */
            if (data->function_declaration_data != NULL)
            {
                (*tree) = LL_GetFirst(data->tbl_list);
                symData_t* func_def = symTableSearch(*tree, func_name);
                
                /*
                 * Check params lists of function declaration and definition
                 */                                                                
                if (!check_function_dec_def_params_list (data->function_declaration_data->params_type_count,
                                                         data->function_declaration_data->first_type_param,
                                                         func_def->params_count,
                                                         func_def->first_param))
                {
                    err = E_SEM_DEF;
                    return false;
                }

                /*
                 * Check returns lists of function declaration and definition
                 */
                if (!check_function_dec_def_returns_list (data->function_declaration_data->returns_count,
                                                          data->function_declaration_data->first_ret,
                                                          func_def->returns_count,
                                                          func_def->first_ret))
                {
                    err = E_SEM_DEF;
                    return false;
                }                                

                data->function_declaration_data = NULL;   
            }
                                     
            /* ----------- END OF SEMANTIC ----------*/
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

                // Add symbol to table
                (*tree) = LL_GetFirst(data->tbl_list);
                create_symbol(tree, data->token->attribute.string);

                if (err != E_NO_ERR)
                {
                    return false;
                }

                // Create symbol table for function
                create_sym_table(data->tbl_list);

                // Save function name to data->func_name
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
            /* -------------- SEMANTIC --------------*/

            /*
             * Check if called function is declared
             */
            if (!check_function_is_declared(data->tbl_list, data->token->attribute.string))
            {
                err = E_SEM_DEF;
                return false;
            }

            data->param = symTableSearch(LL_GetFirst(data->tbl_list), data->token->attribute.string)->first_param;

            /* ----------- END OF SEMANTIC ----------*/

            next_token(data);
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;

            if (token_type == T_LEFT_BRACKET)
            {
                next_token(data);

                if (args(data))
                {
                    VALIDATE_TOKEN(data->token);
                    TEST_EOF(data->token);
                    token_type = data->token->type;

                    if (token_type == T_RIGHT_BRACKET)
                    {
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
    symTree_t** tree;
    symData_t* data_type;
    char* id;

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
            strcpy(id, data->token->attribute.string);
            (*tree) = LL_GetLast(data->tbl_list);

            if (!check_first_definition(*tree, id))
            {
                err = E_SEM_DEF;
                return false;
            }

            if (!check_conflict_id_func(data->tbl_list, id))
            {
                err = E_SEM_DEF;
                return false;
            }
            
            
            create_symbol(tree, id);

            if (err != E_NO_ERR)
            {
                return false;
            }
                
            /* ----------- END OF SEMANTIC ----------*/

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
                    symTableSearch(*tree, id)->data_type = data->type;    
                
                    /* ----------- END OF SEMANTIC ----------*/

                    if (assign(data))
                    {
                        /* -------------- SEMANTIC --------------*/

                        data_type = symTableSearch(*tree, id)->data_type;

                        if (data_type != data->psa_data_type)
                        {
                            if (data->psa_data_type == NIL || 
                                (data_type == NUMBER && data->psa_data_type == INT))
                            {
                                // VALID
                            }
                            else
                            {
                                err = E_SEM_ASSIGN;
                                return false;
                            }                                                        
                        }                        

                        /* ----------- END OF SEMANTIC ----------*/

                        if (stats(data))
                        {
                            ret_val = true;    
                        }                        
                    }                    
                }                            
            }            
        }        
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
        strcpy(data->func_name, data->token->attribute.string);

        /* -------------- SEMANTIC --------------*/

        /*
         * Check if called function/identifier is declared
         */     
        if (!check_function_is_declared(data->tbl_list, data->func_name))
        {
            err = E_SEM_DEF;
            return false;
        }

        idInsert(data->ids_list, data->func_name);

        if (err != E_NO_ERR)
        {
            return false;
        }        

        /* ----------- END OF SEMANTIC ----------*/

        next_token(data);  

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

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;
      
    /* 13. <id_func> -> (<args>) */
    if (token_type == T_LEFT_BRACKET)
    {     
        /* -------------- SEMANTIC --------------*/           
        
        data->param = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_param;

        /* ----------- END OF SEMANTIC ----------*/

        next_token(data);

        if (args(data))
        {              
            VALIDATE_TOKEN(data->token); 
            TEST_EOF(data->token); 
            token_type = data->token->type;

            if (token_type == T_RIGHT_BRACKET)
            {
                ret_val = true;
                next_token(data);
            }                
        }            
    }
    /* 12. <id_func> -> <n_ids> = <as_vals> */
    else if (n_ids(data))
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
    char* id;

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 14. <params> -> id : <type> <n_params> */
    if (token_type == T_IDENTIFIER)
    {
        // Ulozeni jmena parametru
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
                insert_parameter(data->tbl_list, data->func_name, id, data->type);

                if (err != E_NO_ERR)
                {
                    return false;
                }                

                /* ----------- END OF SEMANTIC ----------*/            

                ret_val = n_params(data);
            }            
        }        
    }    
    /* 15. <params> -> epsilon */
    else if (token_type == T_RIGHT_BRACKET)
    {
        ret_val = true;
    }    

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

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 16. <n_params> -> , id : <type> <n_params> */
    if (token_type == T_COMMA)
    {
        next_token(data);

        if (type(data))
        {            
            ret_val = n_params(data);
        }        
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
            if (!check_function_is_declared(data->tbl_list, data->token->attribute.string))
            {
                err = E_SEM_DEF;
                return false;
            }

            idInsert(data->ids_list, data->token->attribute.string);

            if (err != E_NO_ERR)
            {
                return false;
            }

            /* ----------- END OF SEMANTIC ----------*/

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

            data->ids_list->next;
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
        func_data = symTableSearch(glb_tbl, data->func_name);

        data->param = func_data->first_param;

        if (data->param != NULL)
        {
            if (data->psa_data_type != data->param->param_type)
            {
                err = E_SEM_PARAM;
                return false;
            }   

            data->param  = data->param->param_next;
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

    /* 22. <n_vals> -> epsilon */
    if (stats(data))
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

                    data->ids_list->next;
                }                        
                else
                {
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

    /* 22. <n_vals> -> epsilon */
    if (stats(data))
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

                if (data->param != NULL)
                {
                    if (data->psa_data_type != data->param->param_type)
                    {
                        err = E_SEM_PARAM;
                        return false;
                    }   

                    data->param  = data->param->param_next;
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

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);
    token_type = data->token->type;

    /* 24. <as_vals> -> id (<args>) */
    if (token_type == T_IDENTIFIER)
    {
        strcpy(data->func_name, data->token->attribute.string);

        if (vals(data))
        {
            ret_val = true;
        }
        else
        {
            /* -------------- SEMANTIC --------------*/ 
            /*
             * Check if called function is declared
             */       
            if (!check_function_is_declared(data->tbl_list, data->func_name))
            {
                err = E_SEM_DEF;
                return false;
            }

            /* For args */
            data->param = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_param;

            /* For assign to identifiers */
            if (!check_func_assign(data))
            {
                err = E_SEM_PARAM;
                return false;
            }        

            /* ----------- END OF SEMANTIC ----------*/

            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;                
            
            if (token_type == T_LEFT_BRACKET)
            {
                next_token(data);

                if (args(data))
                {                
                    VALIDATE_TOKEN(data->token);
                    TEST_EOF(data->token);
                    token_type = data->token->type;

                    if (token_type == T_RIGHT_BRACKET)
                    {
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

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    /* 25. <ret_vals> -> <vals> */ 
    if (r_vals(data))
    {
        ret_val = true;
    }
    /* 26. <ret_vals> -> epsilon */
    else if (stats(data))
    {
        ret_val = true;
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

    /* 28. <assign> -> epsilon */
    if (stats(data))
    {                    
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

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);
    token_type = data->token->type;

    /* 30. <assign_val> -> id (<args>) */    
    if (token_type == T_IDENTIFIER)
    {    
        strcpy(data->func_name, data->token->attribute.string);

        if (expression(data))
        {
            ret_val = true;
        }
        else
        {
            /* -------------- SEMANTIC --------------*/ 
            /*
             * Check if called function is declared
             */       
            if (!check_function_is_declared(data->tbl_list, data->func_name))
            {
                err = E_SEM_DEF;
                return false;
            }
        
            data->param = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name)->first_param;

            func_data = symTableSearch(LL_GetFirst(data->tbl_list), data->func_name);

            if (func_data->first_ret != NULL)
            {
                data->psa_data_type = func_data->first_ret->return_type;
            }
            else
            {
                err = E_SEM_PARAM;
                return false;
            }                        

            /* ----------- END OF SEMANTIC ----------*/

            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;

            if (token_type == T_LEFT_BRACKET)
            {
                next_token(data);

                if (args(data))
                {           
                    VALIDATE_TOKEN(data->token); 
                    TEST_EOF(data->token);    
                    token_type = data->token->type;

                    if (token_type == T_RIGHT_BRACKET)
                    {
                        ret_val = true;
                        next_token(data);
                    }                
                }            
            }
        }                        
    }    
    /* 29. <assign_val> -> exp */
    else if (expression(data))
    {        
        ret_val = true;
    }        

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

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);

    token_type = data->token->type;

    /* 31. <term> -> id */
    if (token_type == T_IDENTIFIER)
    {
        /* -------------- SEMANTIC --------------*/
        if (!check_identifier_is_defined(data->tbl_list, data->token->attribute.string))
        {
            err = E_SEM_DEF;
            return false;
        }
        
        data->type = identifier_type(data->tbl_list, data->token->attribute.string);
        
        /* ----------- END OF SEMANTIC ----------*/

        ret_val = true;
        next_token(data);
    }
    /* 32. <term> -> <const> */
    else if (constant(data))
    {
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
        /* -------------- SEMANTIC --------------*/
        if (data->param != NULL)
        {
            if (data->param->param_type != data->type)
            {
                err = E_SEM_PARAM;
                return false;
            }
            
            data->param = data->param->param_next;        
        }
        else
        {
            err = E_SEM_PARAM;
            return false;
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
            if (data->param != NULL)
            {
                if (data->param->param_type != data->type)
                {
                    err = E_SEM_PARAM;
                    return false;
                }
                
                data->param = data->param->param_next;        
            }
            else
            {
                err = E_SEM_PARAM;
                return false;
            }
            
            /* ----------- END OF SEMANTIC ----------*/

            ret_val = n_args(data);
        }        
    }
    /* 36. <n_args> -> epsilon */
    else if (token_type == T_RIGHT_BRACKET)
    {
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
        token_type = data->token->type;

        /* 41. <ret_def_types> -> : <func_def_types> */ 
        if (token_type == T_COLON)
        {
            next_token(data);

            data->arg_ret = RET_DEF_TYPE;

            ret_val = func_def_types(data);
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
            
        }
        else
        {
            // Vlozeni noveho parametru funkce                                                       
            insert_return(data->tbl_list, data->func_name, data->type);

            if (err != E_NO_ERR)
            {
                return false;
            }
        }

        /* ----------- END OF SEMANTIC ----------*/

        ret_val = n_func_def_types(data);
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
bool n_func_def_types (p_data_ptr_t data)
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
        token_type = data->token->type;

        /* 47. <n_func_def_types> -> , <type>  <n_func_def_types> */
        if (token_type == T_COMMA)
        {
            next_token(data);        
            
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
                }
                else
                {
                    // Vlozeni noveho parametru funkce                                                       
                    insert_return(data->tbl_list, data->func_name, data->type);

                    if (err != E_NO_ERR)
                    {
                        return false;
                    }
                }

                /* ----------- END OF SEMANTIC ----------*/

                ret_val = n_func_def_types(data);
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
            data->type = NIL;
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
        next_token(data);
    }
    
    return ret_val;
}