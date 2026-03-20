#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define LCD_RS_PORT PORTD
#define LCD_RS_DDR  DDRD
#define LCD_RS_PIN  PD7

#define LCD_RW_PORT PORTD
#define LCD_RW_DDR  DDRD
#define LCD_RW_PIN  PD6

#define LCD_E_PORT  PORTD
#define LCD_E_DDR   DDRD
#define LCD_E_PIN   PD5

#define LCD_DATA_PORT PORTB
#define LCD_DATA_DDR  DDRB
#define LCD_DATA_MASK 0xF0

void lcd_init(void);
void lcd_clear(void);
void lcd_home(void);
void lcd_goto(uint8_t row, uint8_t col);
void lcd_putchar(char c);
void lcd_puts(const char *s);

#endif
