/**
 * Project: IFJ21 imperative language compiler  
 * 
 * Brief:   Testing Lexical Analysis
 *  
 * Author:  Stepan Bakaj     <xbakaj00> 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "error.h"


int main() {

    token_t* token;

    while ((token = get_next_token()) != NULL){
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
    if (err == E_LEX){
        printf("E_LEX\n");

    } else if (err == E_NO_ERR) {
        printf("E_NO_ERR\n");
    } else if (err == E_INTERNAL){
        printf("E_INTERNAL\n");
    }
    return EXIT_SUCCESS;
}