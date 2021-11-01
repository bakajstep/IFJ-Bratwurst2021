/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Dynamic string to store text
 *
 * Author:  Stepan Bakaj     <xbakaj00@stud.fit.vutbr.cz>
 *
 * Date:    23-10-2021
 */

#include "string.h"
#include <stdbool.h>
#include <stdlib.h>

#define ALLOCATE_LENGTH 8

bool string_init(string_ptr_t string){

    string->string = (char *) malloc(ALLOCATE_LENGTH); //we could multiply it with size of char,but it would be multiply by 1
    if (!string->string){
        return false;
    }
    string->alloc_lenght = ALLOCATE_LENGTH;
    string->lenght = 0;
    return true;
}

void string_free(string_ptr_t string){
    free(string->string);
    string->alloc_lenght = 0;
    string->lenght = 0;
}

bool string_append_character(string_ptr_t string, char a){
    if (string->lenght + 1 >= string->alloc_lenght){
        string->alloc_lenght = string->alloc_lenght + ALLOCATE_LENGTH; //add 8 bytes of memory to field
        string->string = (char *) realloc(string->string,string->alloc_lenght);
        if (!string->string){ // failed realloc
            return false;
        }
    }
    string->string[string->lenght++] = a;
    string->string[string->lenght] = '\0';
    return true;
}

char* get_char_arr(string_ptr_t string)
{
    return string->string;
}

int string_to_int (string_ptr_t string)
{
    return atoi(string->string);
}

double string_to_dec (string_ptr_t string)
{
    return atof(string->string);
}
