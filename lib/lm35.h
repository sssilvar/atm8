#ifndef LM35_H
#define LM35_H

#include <stdint.h>

#ifndef LM35_AREF_MV
#define LM35_AREF_MV 5000U
#endif

#define LM35_DDR   DDRC
#define LM35_PORT  PORTC
#define LM35_PIN   PC0
#define LM35_MUX   0

void lm35_init(void);
int16_t lm35_read_celsius(void);

#endif
