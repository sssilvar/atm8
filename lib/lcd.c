#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

#define LCD_RS_HI() (LCD_RS_PORT |=  (1 << LCD_RS_PIN))
#define LCD_RS_LO() (LCD_RS_PORT &= ~(1 << LCD_RS_PIN))
#define LCD_RW_HI() (LCD_RW_PORT |=  (1 << LCD_RW_PIN))
#define LCD_RW_LO() (LCD_RW_PORT &= ~(1 << LCD_RW_PIN))
#define LCD_E_HI()  (LCD_E_PORT |=  (1 << LCD_E_PIN))
#define LCD_E_LO()  (LCD_E_PORT &= ~(1 << LCD_E_PIN))

#define LCD_NIBBLE_OUT(n) (LCD_DATA_PORT = (LCD_DATA_PORT & ~LCD_DATA_MASK) | (((n) & 0x0F) << 4))

static void lcd_pulse(void)
{
	LCD_E_HI();
	_delay_us(1);
	LCD_E_LO();
	_delay_us(1);
}

static void lcd_write_byte(uint8_t byte)
{
	LCD_RW_LO();
	LCD_NIBBLE_OUT(byte >> 4);
	lcd_pulse();
	LCD_NIBBLE_OUT(byte & 0x0F);
	lcd_pulse();
	_delay_us(50);
}

static void lcd_cmd(uint8_t cmd)
{
	LCD_RS_LO();
	lcd_write_byte(cmd);
}

static void lcd_send_nibble(uint8_t n)
{
	LCD_NIBBLE_OUT(n);
	lcd_pulse();
}

void lcd_init(void)
{
	LCD_RS_DDR |= (1 << LCD_RS_PIN) | (1 << LCD_RW_PIN) | (1 << LCD_E_PIN);
	LCD_DATA_DDR |= LCD_DATA_MASK;

	_delay_ms(50);
	LCD_RS_LO();
	LCD_RW_LO();
	lcd_send_nibble(0x03);
	_delay_ms(5);
	lcd_send_nibble(0x03);
	_delay_us(100);
	lcd_send_nibble(0x03);
	lcd_send_nibble(0x02);

	lcd_cmd(0x28);
	_delay_us(50);
	lcd_cmd(0x28);

	lcd_cmd(0x0C);
	lcd_cmd(0x06);
	lcd_clear();
}

void lcd_clear(void)
{
	lcd_cmd(0x01);
	_delay_ms(2);
}

void lcd_home(void)
{
	lcd_cmd(0x02);
	_delay_ms(2);
}

void lcd_goto(uint8_t row, uint8_t col)
{
	uint8_t addr = (row == 0) ? 0x00 : 0x40;
	lcd_cmd(0x80 | (addr + col));
}

void lcd_putchar(char c)
{
	LCD_RS_HI();
	lcd_write_byte((uint8_t)c);
}

void lcd_puts(const char *s)
{
	while (*s) lcd_putchar(*s++);
}
