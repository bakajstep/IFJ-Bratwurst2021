/**
 * Project: Compiler for IFJ21 language
 * 
 * Brief:   Error handler for IFJ2021 compiler project
 * 
 * Author:  David Chocholaty <xchoch09@stud.fit.vutbr.cz>
 * 
 * Date:    28-10-2021
 */

#include <stdio.h>

#include "error.h"

#define INTERNAL_ERR_IDX 10

void print_err (error_t err)
{        
    const char *error_msg[] =
    {
        "No error",                                                    //0
        "Lexical analysis error - wrong structure of current lexeme",  //1
        ""                                                             //2
        ""                                                             //3
        ""                                                             //4
        ""                                                             //5
        ""                                                             //6
        ""                                                             //7
        ""                                                             //8
        ""                                                             //9
        "Internal compiler error"                                      //10
    };

       
    if(err >= INTERNAL_ERR_IDX)
    {
        err = INTERNAL_ERR_IDX;
    }

    fprintf(stderr, "Error: %s\n", error_msg[err]); 
}