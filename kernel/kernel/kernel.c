#include <kernel/tty.h>
#include <stdio.h>

void kernel_init(void) {
	tty_initialize();
}

void
kernel_main(void) {
	printf("Hello, kernel World!\n");
}
