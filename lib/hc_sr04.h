#ifndef HC_SR04_H
#define HC_SR04_H

#include <stdint.h>

#define HC_SR04_ECHO_PORT  PINB
#define HC_SR04_ECHO_DDR   DDRB
#define HC_SR04_ECHO_PIN   PB0

#define HC_SR04_TRIG_PORT  PORTD
#define HC_SR04_TRIG_DDR   DDRD
#define HC_SR04_TRIG_PIN   PD0

void hc_sr04_init(void);
uint16_t hc_sr04_read_cm(void);

#endif
