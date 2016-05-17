#include <kernel/display/tty.h>
#include <kernel/memory/frame_allocator.h>
#include <kernel/memory/paging.h>

#include <stdio.h>

#include <multiboot.h>

int
kernel_init(const multiboot_info_t* multiboot_info) {
	tty_initialize();

	if (frame_allocator_init(multiboot_info) == -1) {
		printf("[ERR ] Can't initialize the frame allocator.\n");
		return -1;
	}

	if (paging_init() == -1) {
		printf("[ERR ] Can't initialize the paging system.\n");
		return -1;
	}

	return 0;
}

void
kernel_main(void) {
	printf("[INFO] Hello, kernel World!\n");
}
