#ifndef IFJ_BRATWURST2021_PSA_H
#define IFJ_BRATWURST2021_PSA_H

#include <stdbool.h>

#include "parser.h"

bool psa (p_data_ptr_t data);

#define PSA_NO_ERR false
#define PSA_ERR true

typedef bool psa_error_t;

#endif //IFJ_BRATWURST2021_PSA_H