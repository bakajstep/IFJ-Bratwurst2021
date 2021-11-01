//
// Created by Stepan Bakaj on 01.11.2021.
//

#include <stdlib.h>
#include <stdio.h>

#include "scanner.h"


int main() {
    token_t* token = get_next_token();

    printf("%d",token->attribute.integer);

    return EXIT_SUCCESS;
}