# atm8

ATmega8A playground (AVR-GCC, USBasp).

## Layout

| Path | Role |
|------|------|
| `main.c` | App entry (`#include "lib/foo.h"`) |
| `lib/` | Drivers: paired `.h` + `.c` (local `#include "foo.h"`) |
| `build/` | Objects, ELF, HEX |

No extra `-I`: paths are explicit from the project root or same-directory in `lib/`.

## Targets

- `make` / `make flash`
