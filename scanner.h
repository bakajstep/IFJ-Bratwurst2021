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

enum state {
    S_APOSTROPHE,
    S_CHAR_NUMBER,
    S_MUL,
    S_DIV,
    S_INT_DIV,
    S_PLUS,
    S_MINUS,
    S_ONE_LINE_COMMENT,
    S_BLOCK_COMMENT,
    S_BLOCK_COMMENT_EOL,
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
    S_ESC_SEQ_TWO_FIVE
};

#endif //IFJ_BRATWURST2021_SCANNER_H
