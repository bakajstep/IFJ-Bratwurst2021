/**
 * Project: Compiler for IFJ21 language
 * 
 * Brief:   Interface of error handler
 * 
 * Author:  David Chocholaty <xchoch09@stud.fit.vutbr.cz>
 * 
 * Date:    28-10-2021
 */

#ifndef IFJ_BRATWURST2021_ERROR_H
#define IFJ_BRATWURST2021_ERROR_H

#include <stdint.h>

enum error {
    E_NO_ERR   = 0,
    E_LEX      = 1,
    E_INTERNAL = 99    
};

extern uint8_t err = E_NO_ERR;

void print_err (uint8_t);

#endif //IFJ_BRATWURST2021_ERROR_H