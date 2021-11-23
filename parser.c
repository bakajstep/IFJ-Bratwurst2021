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

void create_tbl_list (DLList* tbl_list)
{
    DLL_Init(tbl_list);
}

void create_sym_table (DLList* tbl_list)
{
    symTree_t** tree;

    symTableInit(tree);
    DLL_InsertLast(tbl_list, tree);    
}

void create_symbol (symTree_t** tree, char* key)
{
    symData_t* data;
    symDataInit(data);
    symTableInsert(tree, key, data);
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

    VALIDATE_TOKEN(data->token);

    /* 5. <main_b> -> epsilon */
    if (data->token == NULL)
    {
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

                // Add symbol to table
                (*tree) = DLL_GetLast(data->tbl_list);
                create_symbol(tree, data->token->attribute.string);

                // Set function as defined
                symTableSearch(*tree, data->token->attribute.string)->defined = true;

                // Create symbol table for function
                create_sym_table(data->tbl_list);
                
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
                                    DLL_DeleteLast(data->tbl_list);

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
            next_token(data);
            VALIDATE_TOKEN(data->token);
            TEST_EOF(data->token);
            token_type = data->token->type;

            if (token_type == T_COLON)
            {                                   
                next_token(data);

                if (type(data) &&
                    assign(data) &&
                    stats(data))
                {                                                            
                    ret_val = true;                              
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
                next_token(data);

                if (stats(data))
                {
                    VALIDATE_TOKEN(data->token);
                    TEST_EOF(data->token);
                    token_type = data->token->type;                    

                    if (token_type == T_KEYWORD && data->token->attribute.keyword == K_ELSE)
                    {
                        next_token(data);

                        if (stats(data))
                        {
                            VALIDATE_TOKEN(data->token);
                            TEST_EOF(data->token);
                            token_type = data->token->type;                            

                            if (token_type == T_KEYWORD && data->token->attribute.keyword == K_END)
                            {
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
                next_token(data);

                if (stats(data))
                {
                    VALIDATE_TOKEN(data->token);
                    TEST_EOF(data->token);
                    token_type = data->token->type;                       

                    if (token_type == T_KEYWORD && data->token->attribute.keyword == K_END)
                    {
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
                /* TODO */
                paramInsert(TODO, data->type, id);

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

        ret_val = n_ids(data);
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
        ret_val = n_vals(data);
    }        

    return ret_val;
}

bool r_vals (p_data_ptr_t data)
{
    bool ret_val = false;

    /* 20. <vals> -> exp <n_vals> */
    if (expression(data))
    {
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
        if (vals(data))
        {
            ret_val = true;
        }
        else
        {
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

    VALIDATE_TOKEN(data->token);
    TEST_EOF(data->token);
    token_type = data->token->type;

    /* 30. <assign_val> -> id (<args>) */    
    if (token_type == T_IDENTIFIER)
    {    
        if (expression(data))
        {
            ret_val = true;
        }
        else
        {
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
        ret_val = true;
    }                
    /* 33. <args> -> <term> <n_args> */    
    else if (term(data))
    {            
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
        ret_val = true;
        next_token(data);
    }
    
    return ret_val;
}