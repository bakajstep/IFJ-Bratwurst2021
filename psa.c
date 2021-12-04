#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "psa.h"
#include "symstack.h"
#include "data_types.h"
#include "error.h"
#include "code_generator.h"
/* TODO smazat */
#include <stdio.h>

#define P_TAB_SIZE 18

static char prec_table[P_TAB_SIZE][P_TAB_SIZE] = {
/*    *//* #   +   -   *   /   //  ..  <   >   <=  >=  ~=  ==  (   )   i   s   $*/
/* #  */ {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','<','>','<','<','>'},
/* +  */ {'<','>','>','<','<','<',' ','>','>','>','>','>','>','<','>','<',' ','>'},
/* -  */ {'<','>','>','<','<','<',' ','>','>','>','>','>','>','<','>','<',' ','>'},
/* *  */ {'<','>','>','>','>','>',' ','>','>','>','>','>','>','<','>','<',' ','>'},
/* /  */ {'<','>','>','>','>','>',' ','>','>','>','>','>','>','<','>','<',' ','>'},
/* // */ {'<','>','>','>','>','>',' ','>','>','>','>','>','>','<','>','<',' ','>'},
/* .. */ {' ',' ',' ',' ',' ',' ','>',' ',' ',' ',' ',' ','>','<','>','<','<','>'},
/* <  */ {'<','<','<','<','<','<',' ','>','>','>','>','>','>','<','>','<','<','>'},
/* >  */ {'<','<','<','<','<','<',' ','>','>','>','>','>','>','<','>','<','<','>'},
/* <= */ {'<','<','<','<','<','<',' ','>','>','>','>','>','>','<','>','<','<','>'},
/* >= */ {'<','<','<','<','<','<',' ','>','>','>','>','>','>','<','>','<','<','>'},
/* ~= */ {'<','<','<','<','<','<',' ','>','>','>','>','>','>','<','>','<','<','>'},
/* == */ {'<','<','<','<','<','<','<','>','>','>','>','>','>','<','>','<','<','>'},
/* (  */ {'<','<','<','<','<','<','<','<','<','<','<','<','<','<','=','<','<',' '},
/* )  */ {' ','>','>','>','>','>','>','>','>','>','>','>','>',' ','>',' ',' ','>'},
/* i  */ {' ','>','>','>','>','>','>','>','>','>','>','>','>',' ','>',' ',' ','>'},
/* s  */ {' ',' ',' ',' ',' ',' ','>','>','>','>','>','>','>',' ','>',' ',' ','>'},
/* $  */ {'<','<','<','<','<','<','<','<','<','<','<','<','<','<',' ','<','<',' '},

};



int get_index_token(token_t* token){
    switch (token->type) {
        case T_MUL:
            return 3;
        case T_DIV:
            return 4;
        case T_INT_DIV:
            return 5;
        case T_PLUS:
            return 1;
        case T_MINUS:
            return 2;
        case T_CHAR_CNT:
            return 0;
        case T_CONCAT:
            return 6;
        case T_LESS_THAN:
            return 7;
        case T_LESS_EQ:
            return 9;
        case T_GTR_THAN:
            return 8;
        case T_GTR_EQ:
            return 10;
        case T_NOT_EQ:
            return 11;
        case T_EQ:
            return 12;
        case T_LEFT_BRACKET:
            return 13;
        case T_RIGHT_BRACKET:
            return 14;
        case T_IDENTIFIER:
            return 15;
        case T_COMMA:
            return 17;
        case T_DECIMAL:
            return 15;
        case T_INT:
            return 15;
        case T_STRING:
            return 16;
        case T_DECIMAL_W_EXP:
            return 15;
        case T_KEYWORD:
            if(token->attribute.keyword == K_THEN || token->attribute.keyword == K_DO
                || token->attribute.keyword == K_LOCAL || token->attribute.keyword == K_IF
                || token->attribute.keyword == K_WHILE || token->attribute.keyword == K_RETURN
                || token->attribute.keyword == K_END || token->attribute.keyword == K_ELSE) {
                return 17;//continue to case $
            }
            else if(token->attribute.keyword == K_NIL){
                return 15;
            }
            else{
                break;
            }
        default:
            return -1;
    }
    return -1;
}

int get_index_enum(psa_table_symbol_enum e){
    switch (e) {
        case MUL:
            return 3;
        case DIV:
            return 4;
        case INT_DIV:
            return 5;
        case PLUS:
            return 1;
        case MINUS:
            return 2;
        case HASHTAG:
            return 0;
        case CONCAT:
            return 6;
        case LESS_THAN:
            return 7;
        case LESS_EQ:
            return 9;
        case GTR_THAN:
            return 8;
        case GTR_EQ:
            return 10;
        case NOT_EQ:
            return 11;
        case EQ:
            return 12;
        case LEFT_BRACKET:
            return 13;
        case RIGHT_BRACKET:
            return 14;
        case IDENTIFIER:
            return 15;
        case INT_NUMBER:
            return 15;
        case STRN:
            return 16;
        case DOUBLE_NUMBER:
            return 15;
        case DOLLAR:
            return 17;
        default:
            return -1;
    }
    return -1;
}

/**
 * Function tests if symbols in parameters are valid according to rules.
 *
 * @param num Number of valid symbols in parameter.
 * @param op1 Symbol 1.
 * @param op2 Symbol 2.
 * @param op3 Symbol 3.
 * @return NOT_A_RULE if no rule is found or returns rule which is valid.
 */
static psa_rules_enum test_rule(int num, sym_stack_item* op1, sym_stack_item* op2, sym_stack_item* op3)
{
    switch (num)
    {
        case 1:
            // rule E -> i
            if (op1->symbol == IDENTIFIER || op1->symbol == INT_NUMBER || op1->symbol == DOUBLE_NUMBER || op1->symbol == STRN)
                return OPERAND;

            return NOT_A_RULE;
        case 2:
            // rule E -> #E
            if (op2->symbol == HASHTAG && op1->symbol == NON_TERM)
                return NT_HASHTAG;
            return NOT_A_RULE;
        case 3:
            // rule E -> (E)
            if (op1->symbol == LEFT_BRACKET && op2->symbol == NON_TERM && op3->symbol == RIGHT_BRACKET)
                return LBR_NT_RBR;

            if (op1->symbol == NON_TERM && op3->symbol == NON_TERM)
            {
                switch (op2->symbol)
                {
                    // rule E -> E + E
                    case PLUS:
                        return NT_PLUS_NT;
                    // rule E -> E - E
                    case MINUS:
                        return NT_MINUS_NT;
                    // rule E -> E .. E
                    case CONCAT:
                        return NT_CONCAT_NT;
                    // rule E -> E * E
                    case MUL:
                        return NT_MUL_NT;
                    // rule E -> E / E
                    case DIV:
                        return NT_DIV_NT;
                    // rule E -> E // E
                    case INT_DIV:
                        return NT_IDIV_NT;
                    // rule E -> E = E
                    case EQ:
                        return NT_EQ_NT;
                    // rule E -> E ~= E
                    case NOT_EQ:
                        return NT_NEQ_NT;
                    // rule E -> E <= E
                    case LESS_EQ:
                        return NT_LEQ_NT;
                    // rule E -> E < E
                    case LESS_THAN:
                        return NT_LTN_NT;
                    // rule E -> E >= E
                    case GTR_EQ:
                        return NT_GEQ_NT;
                    // rule E -> E > E
                    case GTR_THAN:
                        return NT_GTN_NT;
                    // invalid operator
                    default:
                        return NOT_A_RULE;
                }
            }
            return NOT_A_RULE;
    }
    return NOT_A_RULE;
}

/**
 * Function converts token type to symbol.
 *
 * @param token Pointer to token.
 * @return Returns dollar if symbol is not supported or converted symbol if symbol is supported.
 */
static psa_table_symbol_enum get_symbol_from_token(token_t *token)
{
    switch (token->type)
    {
        case T_CHAR_CNT:
            return HASHTAG;
        case T_PLUS:
            return PLUS;
        case T_MINUS:
            return MINUS;
        case T_MUL:
            return MUL;
        case T_DIV:
            return DIV;
        case T_INT_DIV:
            return INT_DIV;
        case T_EQ:
            return EQ;
        case T_NOT_EQ:
            return NOT_EQ;
        case T_LESS_EQ:
            return LESS_EQ;
        case T_LESS_THAN:
            return LESS_THAN;
        case T_GTR_EQ:
            return GTR_EQ;
        case T_GTR_THAN:
            return GTR_THAN;
        case T_LEFT_BRACKET:
            return LEFT_BRACKET;
        case T_RIGHT_BRACKET:
            return RIGHT_BRACKET;
        case T_IDENTIFIER:
            return IDENTIFIER;
        case T_INT:
            return INT_NUMBER;
        case T_DECIMAL:
            return DOUBLE_NUMBER;
        case T_DECIMAL_W_EXP:
            return DOUBLE_NUMBER;
        case T_STRING:
            return STRN;
        case T_KEYWORD:
            if(token->attribute.keyword == K_NIL){
                return IDENTIFIER;
            }else{
                return DOLLAR;
            }
        default:
            return DOLLAR;
    }
}

data_type_t get_type(p_data_ptr_t data){
    switch(data->token->type){
        case T_MUL:
            return OP;
        case T_DIV:
            return OP;
        case T_INT_DIV:
            return OP;
        case T_PLUS:
            return OP;
        case T_MINUS:
            return OP;
        case T_CHAR_CNT:
            return OP;
        case T_CONCAT:
            return OP;
        case T_LESS_THAN:
            return OP;
        case T_LESS_EQ:
            return OP;
        case T_GTR_THAN:
            return OP;
        case T_GTR_EQ:
            return OP;
        case T_NOT_EQ:
            return OP;
        case T_ASSIGN:
            return OP;
        case T_EQ:
            return OP;
        case T_COLON:
            return ELSE;
        case T_LEFT_BRACKET:
            return OP;
        case T_RIGHT_BRACKET:
            return OP;
        case T_COMMA:
            return ELSE;
        case T_INT:
            return INT;
        case T_DECIMAL:
            return NUMBER;
        case T_DECIMAL_W_EXP:
            return NUMBER;
        case T_IDENTIFIER:
            //TODO
            //je potřeba z listu identifikátorů zjistit jestli je platně deklarovasnaý a jaký má typ
            //idk ještě jak vracet když to bude špatně            
            if(!check_identifier_is_defined(data->tbl_list,data->token->attribute.string)){                
                return DERR;
            }
            return identifier_type(data->tbl_list,data->token->attribute.string);
        case T_KEYWORD:
            if(data->token->attribute.keyword == K_NIL){ //TODO ERR
                return NIL;
            }else{
                return ELSE;
            }
        case T_STRING:
            return STR;
        default:
            return ELSE;
    }
}

static bool check_semantic(psa_rules_enum rule, sym_stack_item* op1, sym_stack_item* op2, sym_stack_item* op3, data_type_t* final_type){

    //bool op1_to_number = false;
    //bool op3_to_number = false;

    switch (rule) {
        //TODO - asi nepotrebuju
        case OPERAND:;

            break;
        case LBR_NT_RBR: ;

            break;

        // podsud
        case NT_HASHTAG: ;
            if (op2->data != STR){
                err = E_SEM_INCOMPATIBLE;
                return false;
            }
            *final_type = INT;
            break;
        case NT_CONCAT_NT: ;
            if (op1->data != STR || op3->data != STR){
                err = E_SEM_INCOMPATIBLE;
                return false;
            }
            *final_type = STR;
            break;
        case NT_PLUS_NT: ;
        case NT_MINUS_NT: ;
        case NT_MUL_NT: ;
            //chyba
            if (op1->data == STR || op3->data == STR){
                err = E_SEM_INCOMPATIBLE;
                return false;
            }

            if (op1->data == INT && op3->data == INT){
                *final_type = INT;
                break;
            }
            if (op1->data == NUMBER && op3->data == NUMBER){
                *final_type = NUMBER;
                break;
            }

            //pretypovani
            if (op1->data == INT){
                //op1_to_number = true;
                *final_type = NUMBER;
            }
            if (op3->data == INT){
                //op3_to_number = true;
                *final_type = NUMBER;
            }
            break;
        case NT_DIV_NT: ;
            *final_type = NUMBER;

            //chyba
            if (op1->data == STR || op3->data == STR){
                err = E_SEM_INCOMPATIBLE;
                return false;
            }
/*
            //pretypovani
            if (op1->data == INT){
                op1_to_number = true;
            }
            if (op3->data == INT){
                op3_to_number = true;
            }
*/
            break;
        case NT_IDIV_NT: ;
            *final_type = INT;

            //chyba
            if (op1->data == STR || op3->data == STR){
                err = E_SEM_INCOMPATIBLE;
                return false;
            }

            break;
        case NT_EQ_NT: ;
        case NT_NEQ_NT: ;
            *final_type = ELSE;

            // chyby
            if (op1->data == STR && ( op3->data == INT || op3->data == NUMBER )){
                err = E_SEM_INCOMPATIBLE;
                return false;
            }
            if (( op1->data == INT || op1->data == NUMBER ) && op3->data == STR){
                err = E_SEM_INCOMPATIBLE;
                return false;
            }


            if (op1->data == STR && op3->data == STR){
                break;
            }
            if (op1->data == INT && op3->data == INT){
                break;
            }
            if (op1->data == NUMBER && op3->data == NUMBER){
                break;
            }
/*
            //pretypovani
            if (op1->data == INT){
                op1_to_number = true;
            }
            if (op3->data == INT){
                op3_to_number = true;
            }
*/          
            break;
        case NT_LEQ_NT: ;
        case NT_GEQ_NT: ;
        case NT_LTN_NT: ;
        case NT_GTN_NT: ;
            *final_type = ELSE;

            if ((op1->data == STR && (op3->data == INT || op3->data == NUMBER) ) || ( (op1->data == INT || op1->data == NUMBER) && op3->data == STR)){
                err = E_SEM_INCOMPATIBLE;
                return false;
            }

            if (op1->data == STR && op3->data == STR){
                break;
            }

            if (op1->data == INT && op3->data == INT){
                break;
            }
            if (op1->data == NUMBER && op3->data == NUMBER){
                break;
            }
/*
            //pretypovani
            if (op1->data == INT){
                op1_to_number = true;
            }
            if (op3->data == INT){
                op3_to_number = true;
            }*/
            break;
        default: ;

            break;
    }
    return true;
}


//TODO:
//vytvořit funkci, která mi z tokenu vrátí data_type_t      -   zbývá IDENTIFIER
//typ dat potom budu používat při pushování na stack
//ze stacku budu dále pomocí typů kontrolovat sémantiku
psa_error_t psa (p_data_ptr_t data)
{
    //printf("\nenter psa\n");
    sym_stack stack;
    sym_stack_init(&stack);
    symbol_stack_push(&stack,DOLLAR,ELSE);

    int ind_a;
    int ind_b;
    sym_stack_item* a;
    bool end_while = false;
    data_type_t final_type = ELSE;
    do{
        //token na zásobníku a vstupní token
        a = symbol_stack_top_terminal(&stack);
        
        //indexy tokenů v tabulce
        ind_a = get_index_enum(a->symbol);

        ind_b = get_index_token(data->token);        

        if(data->token->type == T_ASSIGN){
            err = E_INTERNAL;
            return PSA_ERR;
        }
        
        if ((ind_b == 15 )&& (ind_a == 15 || ind_a == 16 || symbol_stack_top(&stack)->symbol == NON_TERM))
        {
            ind_b = 17;
        }        


        //data z tabulky
        char tbl_data = prec_table[ind_a][ind_b];
        //printf("\n ind_a:%d ind_b:%d \n", ind_a, ind_b);

        switch (tbl_data) {
            case '=': ;
                if(get_type(data) == DERR){
                    err = E_SEM_DEF;
                    return PSA_ERR;
                }
                if(!symbol_stack_push(&stack, get_symbol_from_token(data->token),get_type(data))){
                    err = E_INTERNAL;
                    return PSA_ERR;
                }
                next_token(data);
                break;
            case '<': ;                
                //insert after top terminal
                if(!symbol_stack_insert_after_top_terminal(&stack,STOP,ELSE)){                                     
                    err = E_INTERNAL;
                    return PSA_ERR;
                }
                //printf("\nsymbol on top: %d\n",(symbol_stack_top(&stack))->symbol);
                //printf("\nsymbol to push:%d\n",get_symbol_from_token(data->token));
                if(get_type(data) == DERR){                    
                    err = E_SEM_DEF;
                    return PSA_ERR;
                }
                if(!symbol_stack_push(&stack, get_symbol_from_token(data->token), get_type(data)))
                {                    
                    err = E_INTERNAL;
                    return PSA_ERR;
                }
                //todo data
                //generování kódu
                /*switch(get_type(data)){
                    case INT:
                        codeGen_push_int(data);
                    break;
                    case NUMBER:
                        codeGen_push_float(data);
                    break;
                    case STR:
                        codeGen_push_string(data);
                    break;
                    case NIL:
                        codeGen_push_nil(data);
                    break;
                }*/

                //printf("\nsymbol on top: %d\n",(symbol_stack_top(&stack))->symbol);
                next_token(data);
                break;
            case '>': ;
                //zjistím kolik mám symbolů na stack do <
                sym_stack_item symbol1;
                sym_stack_item symbol2;
                sym_stack_item symbol3;
                int num=0;
            //printf("top stack for check rule %d",symbol_stack_top(&stack)->symbol);
                if(symbol_stack_top(&stack)->symbol != STOP){
                    symbol1 = *(symbol_stack_top(&stack));
                    symbol_stack_pop(&stack);
                    num++;
                //printf("top stack for check rule %d",symbol_stack_top(&stack)->symbol);
                    if(symbol_stack_top(&stack)->symbol != STOP){
                        symbol2 = *(symbol_stack_top(&stack));
                        symbol_stack_pop(&stack);
                        num++;
                        
                        if(symbol_stack_top(&stack)->symbol != STOP){
                            symbol3 = *(symbol_stack_top(&stack));
                            symbol_stack_pop(&stack);
                            num++;
                            
                            if(symbol_stack_top(&stack)->symbol != STOP)
                            {                                                      
                                err = E_INTERNAL;
                                return PSA_ERR;
                            }                                
                        }
                    }
                }
                if(symbol_stack_top(&stack)->symbol == STOP){
                    symbol_stack_pop(&stack);
                }
                //zjistím jestli jse pro tohle nějaký pravidlo

                psa_rules_enum rule = test_rule(num,&symbol1,&symbol2,&symbol3);
		//printf("\nnumber for testing rule: %d\n",num);
                //podle pravidla zpustím redukci

                switch (rule) {
                    case OPERAND:
                        // rule E -> i
                        if(!symbol_stack_push(&stack,NON_TERM,symbol1.data)){    
                        
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                //printf("\nredukuju identifikátor\n");                        
                        break;
                    case NT_HASHTAG:
                        // rule E -> #E
                //printf("\npushnul jsem nonterm s int\n");  
                        if(symbol1.data != STR){
                            err = E_SEM_INCOMPATIBLE;
                            printf("motherfucker here");
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,INT)){    
                        
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case LBR_NT_RBR:
                        // rule E -> (E)
                        if(!symbol_stack_push(&stack,NON_TERM,symbol2.data)){                            
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        break;
                    case NT_CONCAT_NT:
                        // rule E -> E .. E
                        if(!check_semantic(NT_CONCAT_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){                            
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_PLUS_NT:
                        // rule E -> E + E
                        if(!check_semantic(NT_PLUS_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){                            
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_MINUS_NT:
                        // rule E -> E - E
                        if(!check_semantic(NT_MINUS_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){                            
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_MUL_NT:
                        // rule E -> E * E
                        if(!check_semantic(NT_MUL_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){                            
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_DIV_NT:
                        // rule E -> E / E
                        if(!check_semantic(NT_DIV_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_IDIV_NT:
                        // rule E -> E // E
                        if(!check_semantic(NT_IDIV_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_EQ_NT:
                        // rule E -> E == E
                        if(!check_semantic(NT_EQ_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_NEQ_NT:
                        // rule E -> E ~= E
                        if(!check_semantic(NT_NEQ_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){                            
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_LEQ_NT:
                        // rule E -> E <= E
                        if(!check_semantic(NT_LEQ_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){ 
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_GEQ_NT:
                        // rule E -> E >= E
                        if(!check_semantic(NT_GEQ_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_LTN_NT:
                        // rule E -> E < E
                        if(!check_semantic(NT_LTN_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NT_GTN_NT:
                        // rule E -> E > E
                        if(!check_semantic(NT_GTN_NT,&symbol1,&symbol2,&symbol3,&final_type)){
                            return PSA_ERR;
                        }
                        if(!symbol_stack_push(&stack,NON_TERM,final_type)){
                            err = E_INTERNAL;
                            return PSA_ERR;
                        }
                        generate_operation(rule);
                        break;
                    case NOT_A_RULE:
                        err = E_SYNTAX;
                        return PSA_ERR;
                        break;
                }
                //printf("\nind_b=%d stack_term=%d\n", ind_b, symbol_stack_top_terminal(&stack)->symbol);
                if(ind_b == 17 && symbol_stack_top_terminal(&stack)->symbol == DOLLAR){                    
                    end_while = true;
                }
                break;
                
            default:
                err = E_INTERNAL;
                return PSA_ERR;                
        }

    }while(!end_while);


    if(symbol_stack_top(&stack)->symbol == NON_TERM)
    {
        //printf("\nexit psa\n");
        data->psa_data_type = symbol_stack_top(&stack)->data;
        symbol_stack_free(&stack);
        return PSA_NO_ERR;    
    }
    
    return  PSA_ERR;
}
