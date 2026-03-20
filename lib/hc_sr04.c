#include "hc_sr04.h"
#include <avr/io.h>
#include <util/delay.h>

#define ECHO_HI() (HC_SR04_ECHO_PORT & (1 << HC_SR04_ECHO_PIN))

#define TIMEOUT_US 30000

void hc_sr04_init(void)
{
	HC_SR04_ECHO_DDR &= ~(1 << HC_SR04_ECHO_PIN);
	HC_SR04_TRIG_DDR |= (1 << HC_SR04_TRIG_PIN);
	HC_SR04_TRIG_PORT &= ~(1 << HC_SR04_TRIG_PIN);
}

uint16_t hc_sr04_read_cm(void)
{
	uint16_t t;
	TCNT1 = 0;
	TCCR1B = (1 << CS10);

	HC_SR04_TRIG_PORT |= (1 << HC_SR04_TRIG_PIN);
	_delay_us(10);
	HC_SR04_TRIG_PORT &= ~(1 << HC_SR04_TRIG_PIN);

	while (!ECHO_HI()) {
		if (TCNT1 >= TIMEOUT_US) { TCCR1B = 0; return 0; }
	}
	TCNT1 = 0;

	while (ECHO_HI()) {
		if (TCNT1 >= TIMEOUT_US) {
			TCCR1B = 0;
			return 0;
		}
	}
	t = TCNT1;
	TCCR1B = 0;

	return (uint16_t)(t / 58);
}
