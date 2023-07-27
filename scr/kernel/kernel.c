#include "arch/i386/tty.h"
#include "arch/i386/tty.c"
#include "arch/i386/vga.h"

void kmain(void) {
	terminal_initialize();
	
	terminal_set_color(VGA_COLOR_WHITE);
	print("NESU KERNEL 0.1 TEST\n\n");
	terminal_set_color(VGA_COLOR_LIGHT_GREEN);
	print("\tCLEAR SCREEN: Successfully.\n");
	print("\tOUTPUT STR: Successfully.\n");
	print("\tNEW LINE: Successfully.\n");
	print("\tTAB: Successfully.");
}
