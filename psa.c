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

psa_error_t psa (p_data_ptr_t data)
{
    /* TODO smazat */
    sym_stack stack;
    sym_stack_init(&stack);
    do{
        //token na zásobníku a vstupní token
        token_t* a;//pop ze zásobníku
        token_t* b = data->token;

        //indexy tokenů v tabulce
        int ind_a = getIndex(*a);
        int ind_b = getIndex(*b);

        //data z tabulky
        char tbl_data = prec_table(ind_a, ind_b);

        switch (tbl_data) {
            case '=':

                break;
            case '<':

                break;
            case '>':

                break;
            default:
                return PSA_ERR;
                break;
        }

    }while(/*podmínka*/)


    /* TODO smazat */
    return PSA_NO_ERR;
}