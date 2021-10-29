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

typedef union attribute
{
    int integer;
    double decimal;
    char* string;
    keyword_t keyword;
} attribute_t;

typedef struct struct_token
{
    token_type_t type;
    attribute_t attribute;
} token_t;

typedef enum state {
    S_INIT,            
    S_DIV,        
    S_MINUS,                
    S_LESS_THAN,    
    S_GTR_THAN,        
    S_ASSIGN,                    
    S_INT,
    S_DECIMAL,
    S_DECIMAL_W_EXP,  
    S_IDENTIFIER_KEYWORD,      

    S_ONE_LINE_COMMENT,
    S_ONE_LINE_COMMENT_CONTENT,
    S_LEFT_SQUARE_BRACKET,
    S_BLOCK_COMMENT_CONTENT,
    S_RIGHT_SQUARE_BRACKET,
    S_DOT,
    S_TILDE,
    S_DECIMAL_POINT,
    S_EXP,
    S_EXP_PLUS_MINUS,
    S_STRING_CONTENT,
    S_ESC_SEQ_BACKSLASH,
    S_ESC_SEQ_ZERO,
    S_ESC_SEQ_DOUBLE_ZERO,
    S_ESC_SEQ_ONE,
    S_ESC_SEQ_X_X,
    S_ESC_SEQ_TWO,
    S_ESC_SEQ_TWO_FIVE    
} state_t;

typedef enum keyword{
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
} keyword_t;

typedef enum token{
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
    T_DECIMAL_W_EXP, // Decimal with exponent
    T_IDENTIFIER, // Identifier
    T_KEYWORD, // Keyword    
    T_STRING, // String
} token_type_t;

#endif //IFJ_BRATWURST2021_SCANNER_H
