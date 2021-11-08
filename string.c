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
    string = (string_ptr_t) malloc(sizeof(struct string));
    if (!string){
        return false;
    }
    string->string = NULL;
    string->alloc_lenght = 0;
    string->lenght = 0;
    return true;
}

void string_free(string_ptr_t string){
    free(string->string);
    free(string);
}

bool string_append_character(string_ptr_t string, char a){
    if (string->lenght + 1 >= string->alloc_lenght){
        string->alloc_lenght =  string->lenght == 0 ? ALLOCATE_LENGTH : string->alloc_lenght * 2; //twice much memmory
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
