#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "scanner.h"
#include "error.h"

#define PROLOG "ifj21"
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

/*
 * Parser main function
 */
int parser (/* TODO */)
{
    /* TODO */
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
    bool ret_val = true;
    token_type_t token_type = data->token->type;
    keyword_t keyword = data->token->attribute.keyword;    

    if (token_type == T_KEYWORD && keyword == K_REQUIRE)
    {
        next_token(data);
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
    token_type_t token_type = data->token->type;
    keyword_t keyword = data->token->attribute.keyword;

    /* 2. <main_b> -> function id (<params>) <ret_func_types> <stats> end <main_b> */
    if (token_type == T_KEYWORD && keyword == K_FUNCTION)
    {
        next_token(data);
        token_type = data->token->type;

        if (token_type == T_IDENTIFIER)
        {
            next_token(data);
            token_type = data->token->type;

            if (token_type == T_LEFT_BRACKET)
            {
                next_token(data);

                if (params(data))
                {
                    token_type = data->token->type;

                    if (token_type == T_RIGHT_BRACKET)
                    {
                        next_token(data);

                        if (ret_func_types(data) && stats(data))
                        {
                            token_type = data->token->type;
                            keyword = data->token->attribute.keyword;

                            if (token_type == T_KEYWORD && keyword == K_END)
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
        }        
    }        
    /* 3. <main_b> -> global id : function (<arg_def_types>) <ret_def_types> <main_b> */
    else if (token_type == T_KEYWORD && keyword == K_GLOBAL)
    {
        next_token(data);
        token_type = data->token->type;

        if (token_type == T_IDENTIFIER)
        {
            next_token(data);
            token_type = data->token->type;

            if (token_type == T_COLON)
            {
                next_token(data);
                token_type = data->token->type;
                keyword = data->token->attribute.keyword;

                if (token_type == T_KEYWORD && keyword == K_FUNCTION)
                {
                    next_token(data);
                    token_type = data->token->type;

                    if (token_type == T_LEFT_BRACKET)
                    {
                        next_token(data);

                        if (arg_def_types(data))
                        {
                            token_type = data->token->type;

                            if (token_type == T_RIGHT_BRACKET)
                            {
                                next_token(data);

                                if (ret_def_types(data) && main_b(data))
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
    /* 4. <main_b> -> id (<args>) <main_b> */
    else if (token_type == T_IDENTIFIER)
    {
        next_token(data);
        token_type = data->token->type;

        if (token_type == T_LEFT_BRACKET)
        {
            next_token(data);

            if (args(data))
            {
                token_type = data->token->type;

                if (token_type = T_RIGHT_BRACKET)
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
    /* 5. <main_b> -> epsilon */
    else if (data->token == NULL && err == E_NO_ERR)
    {
        /* EOF */
        ret_val = true;
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <stats>
 *
 * RULES:       
 * 6. <stats> -> local id : <type> <assign> <stats>
 * 7. <stats> -> if <exp> then <stats> else <stats> end <stats>
 * 8. <stats> -> while <exp> do <stats> end <stats>
 * 9. <stats> -> return <ret_vals> <stats>
 * 10. <stats> -> id <id_func> <stats>
 * 11. <stats> -> epsilon
 */
bool stats (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type = data->token->type;
    keyword_t keyword = data->token->attribute.keyword;

    /* 6. <stats> -> local id : <type> <assign> <stats> */
    if (token_type == T_KEYWORD && keyword == K_LOCAL)
    {
        next_token(data);
        token_type = data->token->type;

        if (token_type == T_IDENTIFIER)
        {
            next_token(data);
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
    /* 7. <stats> -> if <exp> then <stats> else <stats> end <stats> */
    else if (token_type == T_KEYWORD && keyword == K_IF)
    {
        next_token(data);

        if (exp(data))
        {
            token_type = data->token->type;
            keyword = data->token->attribute.keyword;

            if (token_type == T_KEYWORD && keyword == K_THEN)
            {
                next_token(data);

                if (stats(data))
                {
                    token_type = data->token->type;
                    keyword = data->token->attribute.keyword;

                    if (token_type == T_KEYWORD && keyword == K_ELSE)
                    {
                        next_token(data);

                        if (stats(data))
                        {
                            token_type = data->token->type;
                            keyword = data->token->attribute.keyword;

                            if (token_type == T_KEYWORD && keyword == K_END)
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
    /* 8. <stats> -> while <exp> do <stats> end <stats> */
    else if (token_type == T_KEYWORD && keyword == K_WHILE)
    {
        next_token(data);

        if (exp(data))
        {
            token_type = data->token->type;
            keyword = data->token->attribute.keyword;     

            if (token_type == T_KEYWORD && keyword == K_DO)
            {
                next_token(data);

                if (stats(data))
                {
                    token_type = data->token->type;
                    keyword = data->token->attribute.keyword;    

                    if (token_type == T_KEYWORD && keyword == K_END)
                    {
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
    else if (token_type == T_KEYWORD && keyword == K_RETURN)
    {
        next_token(data);

        if (ret_vals(data) && stats(data))
        {
            ret_val = true;
        }        
    }    
    /* 10. <stats> -> id <id_func> <stats> */
    else if (token_type == T_IDENTIFIER)
    {
        next_token(data);

        if (id_func(data) && stats(data))
        {
            ret_val = true;
        }        
    }    
    /* 11. <stats> -> epsilon */
    else if (token_type == T_KEYWORD)
    {
        if (keyword == K_END ||
            keyword == K_ELSE)
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
      
    /* 13. <id_func> -> (<args>) */
    if (token_type == T_LEFT_BRACKET)
    {
        next_token(data);

        if (args(data))
        {                
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
    token_type_t token_type = data->token->type;

    /* 14. <params> -> id : <type> <n_params> */
    if (token_type == T_IDENTIFIER)
    {
        next_token(data);
        token_type = data->token->type;

        if (token_type == T_COLON)
        {
            if (type(data))
            {                
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
    token_type_t token_type = data->token->type;

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
    token_type_t token_type = data->token->type;

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
 * 20. <vals> -> <exp> <n_vals>
 */
bool vals (p_data_ptr_t data)
{
    bool ret_val = false;

    /* 20. <vals> -> <exp> <n_vals> */
    if (exp(data) && n_vals(data))
    {
        ret_val = true;
    }    

    return ret_val;
}

/*
 * NON-TERMINAL: <n_vals>
 *
 * RULES:     
 * 21. <n_vals> -> , <exp> <n_vals>
 * 22. <n_vals> -> epsilon
 */
bool n_vals (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type = data->token->type;
    keyword_t keyword;

    /* 21. <n_vals> -> , <exp> <n_vals> */    
    if (token_type == T_COMMA)
    {
        next_token(data);        

        if (exp(data) && n_vals(data))
        {
            ret_val = true;
        }        
    }
    /* 22. <n_vals> -> epsilon */
    else if (token_type == T_KEYWORD)
    {
        keyword = data->token->attribute.keyword;

        if (keyword == K_LOCAL ||
            keyword == K_IF ||
            keyword == K_WHILE ||
            keyword == K_RETURN)
        {
            ret_val = true;
        }
        
    }        
    else if (token_type == T_IDENTIFIER)
    {
        ret_val = true;
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
    token_type_t token_type = data->token->type;

    /* 24. <as_vals> -> id (<args>) */
    if (token_type == T_IDENTIFIER)
    {
        next_token(data);
        token_type = data->token->type;

        if (token_type == T_LEFT_BRACKET)
        {
            next_token(data);

            if (args(data))
            {                
                token_type = data->token->type;

                if (token_type == T_RIGHT_BRACKET)
                {
                    ret_val = true;
                    next_token(data);
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
    token_type_t token_type = data->token->type;
    keyword_t keyword;

    /* 26. <ret_vals> -> epsilon */
    if(token_type == T_KEYWORD)
    {
        keyword = data->token->attribute.keyword;

        if (keyword == K_LOCAL ||
            keyword == K_IF ||
            keyword == K_WHILE ||
            keyword == K_RETURN)
        {
            ret_val = true;            
        }        
    }    
    else if (token_type == T_IDENTIFIER)
    {
        ret_val = true;        
    }   
    /* 25. <ret_vals> -> <vals> */ 
    else if (vals(data))
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
    token_type_t token_type = data->token->type;
    keyword_t keyword;

    /* 27. <assign> -> = <assign_val> */
    if (token_type == T_ASSIGN)
    {
        next_token(data);

        ret_val = assign_val(data);
    }
    /* 28. <assign> -> epsilon */
    else if (token_type == T_KEYWORD)
    {
        keyword = data->token->attribute.keyword;

        if (keyword == K_LOCAL ||
            keyword == K_IF ||
            keyword == K_WHILE ||
            keyword == K_RETURN)
        {
            ret_val = true;            
        }                
    }
    else if (token_type == T_IDENTIFIER)
    {
        ret_val = true;        
    }            

    return ret_val;
}

/*
 * NON-TERMINAL: <assign_val>
 *
 * RULES:       
 * 29. <assign_val> -> <exp>
 * 30. <assign_val> -> id (<args>)
 */
bool assign_val (p_data_ptr_t data)
{
    bool ret_val = false;
    token_type_t token_type = data->token->type;

    /* 29. <assign_val> -> <exp> */
    if (exp(data))
    {
        ret_val = true;
    }    
    /* 30. <assign_val> -> id (<args>) */    
    else if (token_type == T_IDENTIFIER)
    {
        next_token(data);
        token_type = data->token->type;

        if (token_type == T_LEFT_BRACKET)
        {
            next_token(data);

            if (args(data))
            {                
                token_type = data->token->type;

                if (token_type == T_RIGHT_BRACKET)
                {
                    ret_val = true;
                    next_token(data);
                }                
            }            
        }        
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
    token_type_t token_type = data->token->type;

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
    token_type_t token_type = data->token->type;

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
    token_type_t token_type = data->token->type;

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
    token_type_t token_type = data->token->type;
    
    /* 38. <arg_def_types> -> epsilon*/  
    if (token_type = T_RIGHT_BRACKET)
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
    token_type_t token_type = data->token->type;
    keyword_t keyword;

    /* 39. <ret_func_types> -> : <func_types> */
    if (token_type == T_COLON)
    {
        next_token(data);
        ret_val = func_types(data);
    }    
    /* 40. <ret_func_types> -> epsilon */
    else if (token_type = T_KEYWORD)
    {
        keyword = data->token->attribute.keyword;
    
        if (keyword == K_LOCAL ||
            keyword == K_IF ||
            keyword == K_WHILE ||
            keyword == K_RETURN)
        {
            ret_val = true;
        }
        
    }
    else if (token_type = T_IDENTIFIER)
    {
        ret_val = true;
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
    token_type_t token_type = data->token->type;
    keyword_t keyword;

    /* 41. <ret_def_types> -> : <func_def_types> */ 
    if (token_type == T_COLON)
    {
        next_token(data);
        ret_val = func_def_types(data);
    }    
    /* 42. <ret_def_types> -> epsilon */   
    else if (token_type == T_KEYWORD)
    {
        keyword = data->token->attribute.keyword;

        if (keyword == K_FUNCTION ||
            keyword == K_GLOBAL)
        {
            ret_val = true;
        }        
    }
    else if (token_type == T_IDENTIFIER)
    {
        ret_val = true;
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
    token_type_t token_type = data->token->type;
    keyword_t keyword;

    /* 44. <n_func_types> -> , <type>  <n_func_types> */ 
    if (token_type == T_COMMA)
    {
        next_token(data);        
        
        if (type(data))
        {            
            ret_val = n_func_types(data);
        } 
    }    
    /* 45. <n_func_types> -> epsilon */  
    else if (token_type == T_KEYWORD)
    {        
        keyword = data->token->attribute.keyword;

        if (keyword == K_LOCAL ||
            keyword == K_IF ||
            keyword == K_WHILE ||
            keyword == K_RETURN)
        {
            ret_val = true;
        }
        
    }
    else if (token_type == T_IDENTIFIER)
    {
        ret_val = true;
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
    keyword_t keyword;
                           
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
    token_type_t token_type = data->token->type;
    keyword_t keyword;

    /* 47. <n_func_def_types> -> , <type>  <n_func_def_types> */
    if (token_type == T_COMMA)
    {
        next_token(data);        
        
        if (type(data))
        {            
            ret_val = n_func_def_types(data);
        }                 
    }    
    /* 48. <n_func_def_types> -> epsilon */
    else if (token_type == T_KEYWORD)
    {
        keyword = data->token->attribute.keyword;

        if (keyword == K_FUNCTION ||
            keyword == K_GLOBAL)
        {
            ret_val = true;            
        }        
    }
    else if (token_type == T_IDENTIFIER ||
             token_type == T_RIGHT_BRACKET)
    {
        ret_val = true;        
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
    token_type_t token_type = data->token->type;
    keyword_t keyword;

    if (token_type == T_KEYWORD)
    {
        keyword = data->token->attribute.keyword;

        if (keyword == K_INTEGER ||
            keyword == K_NUMBER ||
            keyword == K_STRING)
        {
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
    token_type_t token_type = data->token->type;

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

void next_token(p_data_ptr_t data)
{
    delete_token(data->token);
    data->token = get_next_token();
}

bool exp (p_data_ptr_t data)
{
    // TODO
}