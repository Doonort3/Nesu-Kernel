#ifndef ARCH_I386_TTY_H
#define ARCH_I386_TTY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void reset_caret(void);
void terminal_set_color(uint8_t color);
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void set_cursor_pos (uint16_t rows, uint16_t cols);
void disable_cursor(void);
void print(const char* data);

#endif