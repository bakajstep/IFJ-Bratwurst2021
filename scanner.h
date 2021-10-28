/**
 * Project: Compiler for IFJ21 language
 * 
 * Brief:   Interface of scanner
 * 
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 * Author:  Stepan Bakaj     <xbakaj00@stud.fit.vutbr.cz>
 * Author:  Radek Serejch    <xserej00@stud.fit.vutbr.cz>
 * Author:  David Chocholaty <xchoch09@stud.fit.vutbr.cz>
 * 
 * Date:    23-10-2021
 */

#ifndef IFJ_BRATWURST2021_SCANNER_H
#define IFJ_BRATWURST2021_SCANNER_H

#include <stdint.h>

typedef struct struct_token
{
    uint8_t val;
    char* atribut;
} token_t;

enum state {
    S_INIT,    
    S_CHAR_CNT,
    S_MUL,
    S_DIV,
    S_INT_DIV,
    S_PLUS,
    S_MINUS,
    S_ONE_LINE_COMMENT,
    S_BLOCK_COMMENT,
    S_ONE_LINE_COMMENT_EOL,
    S_CONCAT,
    S_LESS_THAN,
    S_LESS_EQ,
    S_GTR_THAN,
    S_GTR_EQ,
    S_NOT_EQ,
    S_ASSIGN,
    S_EQ,
    S_COLON,
    S_LEFT_BRACKET,
    S_RIGHT_BRACKET,
    S_COMMA,
    S_INT,
    S_DECIMAL,
    S_IDENTIFIER_KEYWORD,
    S_DECIMAL_W_EXP,
    S_STRING,

    S_ONE_LINE_COMMENT_CONTENT,
    S_LEFT_SQUARE_BRACKET,
    S_BLOCK_COMMENT_CONTENT,
    S_RIGHT_SQUARE_BRACKET,
    S_DOT,
    S_TILDE,
    S_DECIMAL_POINT,
    S_EXP,
    S_DECIMAL_PLUS_MINUS,
    S_STRING_CONTENT,
    S_ESC_SEQ_BACKSLASH,
    S_ESC_SEQ_ZERO,
    S_ESC_SEQ_DOUBLE_ZERO,
    S_ESC_SEQ_ONE,
    S_ESC_SEQ_X_X,
    S_ESC_SEQ_TWO,
    S_ESC_SEQ_TWO_FIVE,
    S_ONE_LINE_COMMENT
};

enum keyword{
    K_DO,
    K_ELSE,
    K_END,
    K_FUNCTION,
    K_GLOBAL,
    K_IF,
    K_INTEGER,
    K_LOCAL,
    K_NIL,
    K_NUMBER,
    K_REQUIRE,
    K_RETURN,
    K_STRING,
    K_THEN,
    K_WHILE
};

enum token{
    T_MUL, // Multiply *
    T_DIV,  // Divided /
    T_INT_DIV, // Integer divided //
    T_PLUS, // Plus +
    T_MINUS, // Minus -

    T_CHAR_CNT, // Length of char #

    T_CONCAT, // Concatenation ..
    T_LESS_THAN, // Less than <
    T_LESS_EQ,  // Less than equal <=
    T_GTR_THAN, // Greater than >
    T_GTR_EQ, // Greater than equal >=
    T_NOT_EQ, // Not equal ~=
    T_ASSIGN, // Assignment =
    T_EQ, // Equal ==

    T_COLON, // Data type init :
    T_LEFT_BRACKET, // Left bracket (
    T_RIGHT_BRACKET, // Right bracket )
    T_COMMA, // Comma ,
    T_INT, // Integer number
    T_DECIMAL, // Double number
    T_IDENTIFIER_KEYWORD, // Identifier or keyword
    T_DECIMAL_W_EXP, // Decimal with exponent
    T_STRING, // String

};

#endif //IFJ_BRATWURST2021_SCANNER_H
