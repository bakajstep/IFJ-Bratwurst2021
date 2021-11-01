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


typedef struct string {
    char* string;
    unsigned alloc_lenght;
    unsigned lenght;
} *string_ptr_t;


/**
 * Inicialization of string.
 *
 * @param string Pointer to string.
 * @return True if inicialization was successful, false otherwise.
 */
bool string_init(string_ptr_t string);


/**
 * Release alocate string memory.
 *
 * @param string Pointer to string.
 */
void string_free(string_ptr_t string);


/**
 * Append string of char.
 *
 * @param string Pointer to string.
 * @param a Character that we append.
 * @return True if append was successful, false otherwise.
 *
 */
bool string_append_character(string_ptr_t string, char a);

/**
 * Get parametr of struct and returned pointer of char.
 *
 * @param string Pointer to string.
 * @return Pointer to string.
 *
 */
char* get_char_arr(string_ptr_t string);

/**
 * String from struct parse to int.
 *
 * @param string Pointer to string.
 * @return Parse string to int value.
 *
 */
int string_to_int (string_ptr_t string);

/**
 * String from struct parse to double.
 *
 * @param string Pointer to string.
 * @return Parse string to double value.
 *
 */
double string_to_dec (string_ptr_t string);

#endif //IFJ_BRATWURST2021_STRING_H
