/**
 * Project: Compiler for IFJ21 language
 * 
 * Brief:   Lexical Analysis for IFJ21 compiler
 * 
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 * Author:  Stepan Bakaj     <xbakaj00@stud.fit.vutbr.cz>
 * Author:  Radek Serejch    <xserej00@stud.fit.vutbr.cz>
 * Author:  David Chocholaty <xchoch09@stud.fit.vutbr.cz>
 * 
 * Date:    23-10-2021
 */
#include <ctype.h>

#include "scanner.h"
#include <string.h>

#define ASCII_PRINTABLE 32
#define ASCII_NUMS_START 48

void get_identifier(token_t* Token, char* str){
    if(strcmp(str,"do")==0){
        //    K_DO
    }else if(strcmp(str,"else")==0){
        //    K_ELSE
    }else if(strcmp(str,"end")==0){
        //    K_END
    }else if(strcmp(str,"function")==0){
        //    K_FUNCTION
    }else if(strcmp(str,"global")==0){
        //    K_GLOBAL
    }else if(strcmp(str,"if")==0){
        //    K_IF
    }else if(strcmp(str,"integer")==0){
        //    K_INTEGER
    }else if(strcmp(str,"local")==0){
        //    K_LOCAL
    }else if(strcmp(str,"nil")==0){
        //    K_NIL
    }else if(strcmp(str,"number")==0){
        //    K_NUMBER
    }else if(strcmp(str,"require")==0){
        //    K_REQUIRE
    }else if(strcmp(str,"return")==0){
        //    K_RETURN
    }else if(strcmp(str,"string")==0){
        //    K_STRING
    }else if(strcmp(str,"then")==0){
        //    K_THEN
    }else if(strcmp(str,"while")==0){
        //    K_WHILE
    }else{
        //Token->val=identifier
        // TODO pořešit stav identifier
    }
}

token_t get_next_token ()
{
    token_t token;

    int state = S_INIT;

    while (true)
    {
        // TODO cteni znaku

        switch (state)
        {
            // INIT state
            case (S_INIT):
                if (symbol == '#')
                {
                    state = S_CHAR_CNT;
                }
                else if (symbol == '*')
                {
                    state = S_MUL;
                }
                else if (symbol == '/')
                {
                    state = S_DIV;
                }
                else if (symbol == '+')
                {
                    state = S_PLUS;
                }
                else if (symbol == '-')
                {
                    state = S_MINUS;
                }
                else if (symbol == '.')
                {
                    state = S_DOT;
                }
                else if (symbol == '<')
                {
                    state = S_LESS_THAN;
                }
                else if (symbol == '>')
                {
                    state = S_GTR_THAN;
                }
                else if (symbol == '~')
                {
                    state = S_TILDE;
                }
                else if (symbol == '=')
                {
                    state = S_ASSIGN;
                }
                else if (symbol == ':')
                {
                    state = S_COLON;
                }
                else if (symbol == '(')
                {
                    state = S_LEFT_BRACKET;
                }
                else if (symbol == ')')
                {
                    state = S_RIGHT_BRACKET;
                }
                else if (symbol == ',')
                {
                    state = S_COMMA;
                }
                else if (isdigit(symbol))
                {
                    state = S_INT;
                }
                else if (isalpha(symbol) || symbol == '_')
                {
                    state = S_IDENTIFIER_KEYWORD;
                }
                else if (symbol == '"')
                {
                    state = S_STRING_CONTENT;
                }                
                else if (symbol != '\n' && symbol != ' ')
                {
                    //TODO error
                }

                break;
    //------------------------------------------------------------------------------------------
            // q states            
            case (S_ONE_LINE_COMMENT_CONTENT):                                   
                if (symbol == '\n')
                {
                    state = S_INIT;
                }                

                break; 

            case (S_LEFT_SQUARE_BRACKET): 
                if (symbol == '[')
                {
                    state = S_BLOCK_COMMENT_CONTENT;
                }   
                else
                {
                    state = S_ONE_LINE_COMMENT_CONTENT;
                }

                break;

            case (S_BLOCK_COMMENT_CONTENT):
                if (symbol == ']')
                {
                    state = S_RIGHT_SQUARE_BRACKET;
                }

                break;

            case (S_RIGHT_SQUARE_BRACKET):
                if (symbol == ']')
                {
                    state = S_INIT;
                }
                else
                {
                    state = S_BLOCK_COMMENT_CONTENT;
                }

                break;

            case (S_DOT):
                if (symbol == '.')
                {
                    state = S_CONCAT;
                }
                else
                {
                    //TODO chyba
                }

                break;

            case (S_TILDE):
                if (symbol == '=')
                {
                    token.val = T_NOT_EQ;
                }
                else
                {
                    //TODO error
                }  

                break;

            case (S_DECIMAL_POINT):     
                if (isdigit(symbol))
                {
                    state = S_DECIMAL;
                }
                else
                {
                    //TODO error
                }

                break;

            case (S_EXP):
                if (symbol == '+' || symbol == '-')
                {
                    state = S_DECIMAL_PLUS_MINUS;
                }
                else if(isdigit(symbol))
                {
                    state = S_DECIMAL_W_EXP;
                }
                else
                {
                    //TODO error
                }

                break;

            case (S_DECIMAL_PLUS_MINUS):
                if (isdigit(symbol))
                {
                    state = S_DECIMAL_W_EXP;
                }
                else
                {
                    //TODO error
                }

                break;

            case (S_STRING_CONTENT):            
                if (symbol == '"')
                {
                    //TODO vytvareni stringu a token string
                }
                else if (symbol == '\\')
                {
                    state = S_ESC_SEQ_BACKSLASH;
                }
                else if((int)symbol < ASCII_PRINTABLE)
                {
                    // TODO error
                } 

                break;

            case (S_ESC_SEQ_BACKSLASH):
                if (symbol == '0')
                {
                    state = S_ESC_SEQ_ZERO;
                }
                else if (symbol == '1')
                {
                    state = S_ESC_SEQ_ONE;
                }
                else if (symbol == '2')
                {
                    state = S_ESC_SEQ_TWO;
                }
                else
                {
                    // TODO error
                }

                break;

            case (S_ESC_SEQ_ZERO):
                if (symbol == '0')
                {
                    state = S_ESC_SEQ_DOUBLE_ZERO;
                }
                else if (isdigit(symbol))
                {
                    state = S_ESC_SEQ_X_X;
                }
                else
                {
                    //TODO error
                }

                break;

            case (S_ESC_SEQ_DOUBLE_ZERO):
                if (isdigit(symbol) && symbol != '0')
                {
                    state = S_STRING_CONTENT;
                }
                else
                {
                    //TODO error
                }

                break;

            case (S_ESC_SEQ_ONE):
                if (isdigit(symbol))
                {
                    state = S_ESC_SEQ_X_X;
                }
                else
                {
                    //TODO error
                }

                break;

            case (S_ESC_SEQ_X_X):
                if (isdigit(symbol))
                {
                    state = S_STRING_CONTENT;
                }
                else
                {
                    //TODO error
                }

                break;

            case (S_ESC_SEQ_TWO):
                if (symbol == '5')
                {
                    state = S_ESC_SEQ_TWO_FIVE;
                }
                else if (isdigit(symbol) && 
                         ((int)symbol - ASCII_NUMS_START) < 5)
                {
                    state = S_ESC_SEQ_X_X;
                }
                else
                {
                    //TODO error
                }

                break;

            case (S_ESC_SEQ_TWO_FIVE):
                if (isdigit(symbol) && 
                    ((int)symbol - ASCII_NUMS_START) <= 5)
                {
                    state = S_STRING_CONTENT;
                }
                
                break;
    //-------------------------------------------------------------------
            //f states        
            case (S_CHAR_CNT):
                token.val = T_CHAR_CNT;
                
                break;

            case (S_MUL):
                token.val = T_MUL;
                
                break;

            case (S_DIV):
                token.val = T_DIV;
                
                break;

            case (S_INT_DIV):
                token.val = T_INT_DIV;
                
                break;

            case (S_PLUS):
                token.val = T_PLUS;
                
                break;

            case (S_MINUS):
                token.val = T_MINUS;
                
                break;        
                
            case (S_CONCAT):                
                token.val = T_CONCAT;

                break;

            case (S_LESS_THAN):
                if (symbol == '=')
                {
                    token.val = T_LESS_EQ;
                }
                else
                {
                    //TODO ungetchar symbol
                    token.val = T_LESS_THAN;
                }

                break;        

            case (S_GTR_THAN):
                if (symbol == '=')
                {
                    token.val = T_GTR_EQ;
                }
                else
                {
                    //TODO ungetchar symbol
                    token.val = T_GTR_THAN;
                }

                break;                

            case (S_ASSIGN):
                if (symbol == '=')
                {
                    token.val = T_EQ;
                }
                else
                {
                    //TODO ungetchar symbol
                    token.val = T_ASSIGN;
                }

                break;        

            case (S_COLON):
                token.val = T_COLON;
                
                break;

            case (S_LEFT_BRACKET):
                token.val = T_LEFT_BACKET;
                
                break;
                
            case (S_RIGHT_BRACKET):
                token.val = T_RIGHT_BRACKET;
                
                break;

            case (S_COMMA):
                token.val = T_COMMA;
                
                break;                

            // TODO cisla    
            //case (S_INT):
            //    break;
            //case (S_DECIMAL):
            //    break;
            //case (S_IDENTIFIER_KEYWORD):
            //    break;
            //case (S_DECIMAL_W_EXP):
            //    break;                   
            // end TODO
        }
    }    
}