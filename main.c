#include "lib/lcd.h"
#include "lib/hc_sr04.h"
#include "lib/lm35.h"
#include <util/delay.h>

static void put_i16_temp(int16_t t)
{
	uint16_t u;

	if (t < 0) {
		lcd_putchar('-');
		u = (uint16_t)(-(t + 1)) + 1u;
	} else {
		u = (uint16_t)t;
	}
	if (u >= 100u)
		lcd_putchar('0' + (char)(u / 100u));
	if (u >= 10u)
		lcd_putchar('0' + (char)((u / 10u) % 10u));
	lcd_putchar('0' + (char)(u % 10u));
}

static void show_data(uint16_t cm, int16_t celsius)
{
	uint8_t m = cm / 100;
	uint8_t f = cm % 100;
	char dbuf[6];

	dbuf[0] = '0' + m;
	dbuf[1] = '.';
	dbuf[2] = '0' + f / 10;
	dbuf[3] = '0' + f % 10;
	dbuf[4] = 'm';
	dbuf[5] = '\0';
	lcd_clear();
	lcd_puts("Dist.: ");
	lcd_puts(dbuf);
	lcd_goto(1, 0);
	lcd_puts("Temp: ");
	put_i16_temp(celsius);
	lcd_putchar('C');
}

int main(void)
{
	lcd_init();
	hc_sr04_init();
	lm35_init();

	for (;;) {
		show_data(hc_sr04_read_cm(), lm35_read_celsius());
		_delay_ms(700);
	}
}
