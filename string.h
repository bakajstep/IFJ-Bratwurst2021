/**
 * Project: Compiler for IFJ21 language
 *
 * Brief:   Dynamic string to store text
 *
 * Author:  Stepan Bakaj     <xbakaj00@stud.fit.vutbr.cz>
 *
 * Date:    23-10-2021
 */

#ifndef IFJ_BRATWURST2021_STRING_H
#define IFJ_BRATWURST2021_STRING_H

#include <stdbool.h>

// kdyz budete chtit nejakou funkci napisteto sem do todo
// nebo me na fb
//TODO

typedef struct String {
    char* string;
    unsigned alloc_lenght;
    unsigned lenght;
} *StringPtr;


/**
 * Inicialization of string.
 *
 * @param string Pointer to string.
 * @return True if inicialization was successful, false otherwise.
 */
bool String_Init(StringPtr string);


/**
 * Release alocate string memory.
 *
 * @param string Pointer to string.
 */
void String_Free(StringPtr string);


/**
 * Append string of char.
 *
 * @param string Pointer to string.
 * @param a Character that we append.
 * @return True if append was successful, false otherwise.
 *
 */
bool String_Append_Character(StringPtr string, char a);



#endif //IFJ_BRATWURST2021_STRING_H
