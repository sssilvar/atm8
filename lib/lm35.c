#include "lm35.h"
#include <avr/io.h>

static uint16_t adc_sample(void)
{
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC)) { }
	return ADC;
}

void lm35_init(void)
{
	LM35_DDR &= ~(1 << LM35_PIN);
	LM35_PORT &= ~(1 << LM35_PIN);
	ADMUX = (uint8_t)((1 << REFS0) | (LM35_MUX & 0x0F));
	ADCSRA = (uint8_t)((1 << ADEN) | (1 << ADPS1) | (1 << ADPS0));

	(void)adc_sample();
}

int16_t lm35_read_celsius(void)
{
	uint16_t v = adc_sample();

	return (int16_t)(((uint32_t)v * LM35_AREF_MV) / 1023U / 10U);
}
