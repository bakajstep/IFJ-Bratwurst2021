/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Testing Syntax Analysis
 *
 * Author:  David Chocholaty     <xchoch09@stud.fit.vutbr.cz>
 *
 * Date:    13-11-2021
 */

#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "error.h"

int main() 
{
    if (parser() == PARSE_ERR)
    {
        printf("SYNTAX ERROR\n");
        printf("Err code: %d\n", err);        
    }
    else
    {
        printf("SYNTAX SUCCESS\n");
        printf("Err code: %d\n", err);
    }    

    return EXIT_SUCCESS;
}