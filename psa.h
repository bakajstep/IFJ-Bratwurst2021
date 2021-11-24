#ifndef IFJ_BRATWURST2021_PSA_H
#define IFJ_BRATWURST2021_PSA_H

#include <stdbool.h>

#include "parser.h"

typedef bool psa_error_t;

psa_error_t psa (p_data_ptr_t data);
#define PSA_NO_ERR true

#define PSA_ERR false


/**
 * @enum Rules used for parsing.
 */
typedef enum
{
    OPERAND,		// E -> i
    NT_HASHTAG,     // E -> #E
    LBR_NT_RBR,		// E -> (E)
    NT_CONCAT_NT,   // E -> E .. E
    NT_PLUS_NT,		// E -> E + E
    NT_MINUS_NT,	// E -> E - E
    NT_MUL_NT,		// E -> E * E
    NT_DIV_NT,		// E -> E / E
    NT_IDIV_NT,		// E -> E // E
    NT_EQ_NT,		// E -> E = E
    NT_NEQ_NT,		// E -> E ~= E
    NT_LEQ_NT,		// E -> E <= E
    NT_GEQ_NT,		// E -> E >= E
    NT_LTN_NT,		// E -> E < E
    NT_GTN_NT,		// E -> E > E
    NOT_A_RULE		// rule doesn't exist
} psa_rules_enum;

/**
 * @enum Symbols used for precednece analysis.
 */
typedef enum
{
    HASHTAG,        // #
    PLUS,			// +
    MINUS,			// -
    MUL,			// *
    DIV,			// /
    INT_DIV,	    // //
    CONCAT,         // ..
    LESS_THAN,		// <
    GTR_THAN,		// >
    LESS_EQ,		// <=
    GTR_EQ,			// >=
    NOT_EQ,			// ~=
    EQ,				// ==
    LEFT_BRACKET,	// (
    RIGHT_BRACKET,	// )
    IDENTIFIER,		// ID
    INT_NUMBER,		// int
    DOUBLE_NUMBER,	// double
    STR,			// string
    DOLLAR,			// $
    STOP,			// stop symbol used when reducing
    NON_TERM		// non-terminal
} psa_table_symbol_enum;

#endif //IFJ_BRATWURST2021_PSA_H