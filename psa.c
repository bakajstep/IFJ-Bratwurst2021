#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "psa.h"
#include "symstack.h"


#define P_TAB_SIZE 18

static char prec_table[P_TAB_SIZE][P_TAB_SIZE] = {
/*    *//* #   +   -   *   /   //  ..  <   >   <=  >=  ~=  ==  (   )   i   s   $*/
/* #  */ {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','<','>','=','=',' '},
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
                || token->attribute.keyword == K_WHILE || token->attribute.keyword == K_RETURN) {
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
        case CHAR_CNT:
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
        case STR:
            return 16;
        case DOUBLE_NUMBER:
            return 15;
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
            if (op1->symbol == IDENTIFIER || op1->symbol == INT_NUMBER || op1->symbol == DOUBLE_NUMBER || op1->symbol == STR)
                return OPERAND;

            return NOT_A_RULE;
        case 2:
            // rule E -> #E
            if (op1->symbol == HASHTAG && op2->symbol == NON_TERM)
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
        case T_ASSIGN:
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
            return STR;
        default:
            return DOLLAR;
    }
}

psa_error_t psa (p_data_ptr_t data)
{

    sym_stack stack;
    sym_stack_init(&stack);
    symbol_stack_push(&stack,DOLLAR);

    int ind_a;
    int ind_b;
    psa_table_symbol_enum b;
    sym_stack_item* a;
    bool end_while = false;
    do{
        //token na zásobníku a vstupní token
        a = symbol_stack_top_terminal(&stack);
        
        //indexy tokenů v tabulce
        ind_a = get_index_enum(a->symbol);

        ind_b = get_index_token(data->token);
        b= get_symbol_from_token(data->token);

        //data z tabulky
        char tbl_data = prec_table[ind_a][ind_b];

        switch (tbl_data) {
            case '=': ;
                symbol_stack_push(&stack, get_symbol_from_token(data->token));
                next_token(data);
                break;
            case '<': ;
                //insert after top terminal
                if(!symbol_stack_insert_after_top_terminal(&stack,STOP)){
                    return PSA_ERR;
                }
                if(!symbol_stack_push(&stack, get_symbol_from_token(data->token)))
                    return PSA_ERR;
                next_token(data);
                break;
            case '>': ;
                //zjistím kolik mám symbolů na stack do <
                sym_stack_item symbol1;
                sym_stack_item symbol2;
                sym_stack_item symbol3;
                int num=0;
                if(symbol_stack_top(&stack)->symbol != STOP){
                    symbol1 = *(symbol_stack_top(&stack));
                    symbol_stack_pop(&stack);
                    num++;
                    if(symbol_stack_top(&stack)->symbol != STOP){
                        symbol2 = *(symbol_stack_top(&stack));
                        symbol_stack_pop(&stack);
                        num++;
                        if(symbol_stack_top(&stack)->symbol != STOP){
                            symbol3 = *(symbol_stack_top(&stack));
                            symbol_stack_pop(&stack);
                            num++;
                            if(symbol_stack_top(&stack)->symbol != STOP)
                                return PSA_ERR;
                        }
                    }
                }
                if(symbol_stack_top(&stack)->symbol == STOP){
                    symbol_stack_pop(&stack);
                }
                //zjistím jestli jse pro tohle nějaký pravidlo

                psa_rules_enum rule = test_rule(num,&symbol1,&symbol2,&symbol3);

                //podle pravidla zpustím redukci

                switch (rule) {
                    case OPERAND:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_HASHTAG:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case LBR_NT_RBR:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_CONCAT_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_PLUS_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_MINUS_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_MUL_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_DIV_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_IDIV_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_EQ_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_NEQ_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_LEQ_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_GEQ_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_LTN_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NT_GTN_NT:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        break;
                    case NOT_A_RULE:
                        if(!symbol_stack_push(&stack,NON_TERM)){
                            return PSA_ERR;
                        }
                        return PSA_ERR;
                        break;
                }
                break;

            default:
                if(b == DOLLAR && a->symbol == DOLLAR){
                    end_while = true;
                }else{
                    return PSA_ERR;
                }
        }

    }while(!end_while);

    if(symbol_stack_top(&stack)->symbol == NON_TERM)
        return PSA_NO_ERR;
    return  PSA_ERR;
}

