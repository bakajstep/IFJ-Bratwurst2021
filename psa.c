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



int getIndex(token_t token){
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
            if(strcmp(token.data.s, "then") == 0 || strcmp(token.data.s, "do") == 0
                || strcmp(token.data.s, "local") == 0 || strcmp(token.data.s, "if") == 0
                || strcmp(token.data.s, "while") == 0 || strcmp(token.data.s, "return") == 0) {
                return 17;//continue to case $
            }
            else if(strcmp(token.data.s, "nil") == 0){
                return 15;
            }
            else{
                break;
            }
        default:
            return -1;
    }
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
                    case IDIV:
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
static prec_table_symbol_enum get_symbol_from_token(token_t *token)
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
    /* TODO smazat */
    sym_stack stack;
    sym_stack_init(&stack);
    symbol_stack_push(&stack,DOLLAR);

    do{
        //token na zásobníku a vstupní token
        sym_stack_item* a = symbol_stack_top(&stack);

        //indexy tokenů v tabulce
        int ind_a = a->symbol;
        int ind_b = get_symbol_from_token(data->token);

        //data z tabulky
        char tbl_data = prec_table(ind_a, ind_b);

        switch (tbl_data) {
            case '=':
                symbol_stack_push(&stack,ind_b);
                next_token(data);
                break;
            case '<':
                symbol_stack_push(&stack,STOP);
                symbol_stack_push(&stack,ind_b);
                next_token(data);
                break;
            case '>':
                //zjistím kolik mám symbolů na stack do <
                //zjistím jestli jse pro tohle nějaký pravidlo
                //podle pravidla zpustím redukci
                break;
            default:
                return PSA_ERR;
                break;
        }

    }while(b != DOLLAR && a != DOLLAR);

    /* TODO smazat */
    return PSA_NO_ERR;
}

