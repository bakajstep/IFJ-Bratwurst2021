//
// Created by adam on 25.11.21.
//

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "error.h"

int main()
{
    if (parser() == false)
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