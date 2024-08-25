#include "arch/i386/tty.c"

void kmain(void) {
	disable_cursor();
	terminal_initialize();

	print("NESU KERNEL 0.1 TEST\n");
	terminal_set_color(VGA_COLOR_LIGHT_GREEN);

	print("\n\tASCII: \n\t!\"#$%&'()*+,-./0123456789:;<=>?@"
		"\n\tABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"\n\t[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\n");

	terminal_set_color(VGA_COLOR_WHITE);
	print("\nWelcome!");
}
