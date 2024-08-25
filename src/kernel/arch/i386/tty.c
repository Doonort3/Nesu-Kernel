#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "tty.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
uint8_t terminal_row = 0;
uint8_t terminal_column = 0;
uint8_t terminal_color = 0x0F;

// IO port asm
void outb(unsigned short port, unsigned char val) {
	asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) );
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

// Cursor
uint16_t get_cursor_position(void) {
    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    return pos;
}

void set_cursor_pos(uint16_t rows, uint16_t cols) {
	uint16_t pos = rows * VGA_WIDTH + cols;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void disable_cursor() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void reset_caret() {
	terminal_row = 0;
	terminal_column = 0;
	set_cursor_pos(0, 0);
}

// VGA Output
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len]) {
		len++;
	}

	return len;
}

void terminal_set_color(uint8_t color) {
    terminal_color = color;
}


void terminal_putentryat(char c, uint8_t color, size_t rows, size_t cols) {
	size_t index = rows * VGA_WIDTH + cols;
	vga_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	if (c == '\n') {
		terminal_row += 1;
		terminal_column = 0;
		set_cursor_pos(terminal_row, terminal_column);
	} else if (c == '\t') {
		terminal_column += 4;
	}
	else {
		terminal_putentryat(c, terminal_color, terminal_row, terminal_column);

		if (++terminal_column == VGA_WIDTH) {
			terminal_column++;

			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = VGA_HEIGHT - 1;
			}
		}
	}
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		terminal_putchar(data[i]);
	}
	set_cursor_pos(terminal_row, terminal_column);
}

void print(const char* data) {
	terminal_write(data, strlen(data));
}

void clean_screen() {
	for (size_t x = 0; x < VGA_WIDTH; x++) {
		for (size_t y = 0; y < VGA_HEIGHT; y++) {
			const size_t index = y * VGA_WIDTH + x;
			vga_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_initialize() {
	reset_caret();
	clean_screen();
}