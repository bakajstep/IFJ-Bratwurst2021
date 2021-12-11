/**
 * Project: IFJ21 imperative language compiler  
 * 
 * Brief:   Error codes for IFJ2021 compiler project
 * 
 * Author:  David Chocholaty <xchoch09>
 *  
 */

#ifndef IFJ_BRATWURST2021_ERROR_H
#define IFJ_BRATWURST2021_ERROR_H

#include <stdint.h>

/* Error codes */
typedef enum error {
    E_NO_ERR     = 0,
    E_LEX        = 1,
    E_SYNTAX     = 2,
    E_SEM_DEF    = 3,
    E_SEM_ASSIGN = 4,
    E_SEM_PARAM  = 5,
    E_SEM_INCOMPATIBLE  = 6,
    E_INTERNAL   = 99
} error_t;

extern error_t err;

void print_err (error_t err);

#endif //IFJ_BRATWURST2021_ERROR_H
