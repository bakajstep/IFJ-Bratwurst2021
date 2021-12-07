/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Semantic tester
 *
 * Author:  Adam Kankovsky   <xkanko00@stud.fit.vutbr.cz>
 *
 * Date:    25-11-2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "error.h"

int main()
{
    if (parser() != E_NO_ERR)
    {
        printf("SEMANTIC ERROR\n");
        printf("Err code: %d\n", err);
    }
    else
    {
        printf("SEMANTIC SUCCESS\n");
        printf("Err code: %d\n", err);
    }

    return EXIT_SUCCESS;
}