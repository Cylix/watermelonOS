#include <kernel/tty.h>
#include <kernel/frame_allocator.h>
#include <stdio.h>
#include <multiboot.h>

int
kernel_init(multiboot_info_t* multiboot_info) {
	tty_initialize();

	if (frame_allocator_init(multiboot_info) == -1) {
		printf("[ERR] Can't initialize the frame allocator.\n");
		return -1;
	}

	return 0;
}

void
kernel_main(void) {
	printf("[LOG] Hello, kernel World!\n");
}
