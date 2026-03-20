MCU      = atmega8
F_CPU    = 1000000UL
PROG     = usbasp

LIBDIR   = lib
BUILDDIR = build

TARGET   = main
SRC      = $(TARGET).c $(LIBDIR)/lcd.c $(LIBDIR)/hc_sr04.c $(LIBDIR)/lm35.c
OBJ      = $(BUILDDIR)/$(TARGET).o $(BUILDDIR)/lcd.o $(BUILDDIR)/hc_sr04.o $(BUILDDIR)/lm35.o
ELF      = $(BUILDDIR)/$(TARGET).elf
HEX      = $(BUILDDIR)/$(TARGET).hex

CC       = avr-gcc
OBJCOPY  = avr-objcopy
AVRDUDE  = avrdude

CFLAGS   = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra
LDFLAGS  = -mmcu=$(MCU)
AVRFLAGS = -p $(MCU) -c $(PROG)

.PHONY: all flash clean

all: $(HEX)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(ELF): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/$(TARGET).o: $(TARGET).c $(LIBDIR)/lcd.h $(LIBDIR)/hc_sr04.h $(LIBDIR)/lm35.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/lcd.o: $(LIBDIR)/lcd.c $(LIBDIR)/lcd.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/hc_sr04.o: $(LIBDIR)/hc_sr04.c $(LIBDIR)/hc_sr04.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/lm35.o: $(LIBDIR)/lm35.c $(LIBDIR)/lm35.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: $(HEX)
	$(AVRDUDE) $(AVRFLAGS) -U flash:w:$(HEX):i

clean:
	rm -rf $(BUILDDIR)
