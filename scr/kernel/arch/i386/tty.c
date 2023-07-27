#include <stdbool.h>
#include <stddef.h>
 
#include "vga.h"
#include "tty.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

/**
 * @brief Получить длину строки
 * 
 * @param str 
 * @return size_t 
 */
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;                                     // Ширина экрана
static const size_t VGA_HEIGHT = 25;                                    // Высока экрана

void terminal_initialize()
{
    terminal_row = 0;                                                   // Строки
	terminal_column = 0;                                                // Столбцы 
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK); // Установка цвета vga
    terminal_buffer = (uint16_t*) 0xB8000;                              // Видеопамять

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}

	
}

/// @brief Установка цвета
/// @param color 
void terminal_set_color(uint8_t color)
{
    terminal_color = color;
}

/// @brief 
/// @param c 
/// @param color 
/// @param x 
/// @param y 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
 void terminal_delete_last_line() {
	int x, *ptr;
 
	for(x = 0; x < VGA_WIDTH * 2; x++) {
		ptr = 0xB8000 + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x;
		*ptr = 0;
	}
}
void terminal_putchar(char c) 
{
	if (c == '\n') 
	{
		terminal_row = terminal_row + 1;
		terminal_column = 0;
	} else if (c == '\t') 
	{
		terminal_column = terminal_column + 4;
	}
	else 
	{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column++;
			if (++terminal_row == VGA_HEIGHT)
				terminal_delete_last_line();
				terminal_row = VGA_HEIGHT - 1;
		}
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void print(const char* data) 
{
	terminal_write(data, strlen(data));
}
