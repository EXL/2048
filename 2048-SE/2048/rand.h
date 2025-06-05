#ifndef _RAND_H
#define _RAND_H

#include "stdint.h"

void srand(uint32_t newseed);
uint32_t rand(void);
void randomize(void);

#endif
