#include <kernel/display/tty.h>
#include <kernel/memory/frame_allocator.h>
#include <kernel/memory/paging.h>

#include <stdio.h>

#include <multiboot.h>

int
kernel_init(const multiboot_info_t* multiboot_info) {
	tty_initialize();
	printf("[INFO] TTY initialized.\n");

	printf("[INFO] Initialize frame allocator.\n");
	if (frame_allocator_init(multiboot_info) == -1) {
		printf("[ERR ] Can't initialize the frame allocator.\n");
		return -1;
	}
	printf("[INFO] Frame allocator initialized.\n");

	printf("[INFO] Initialize paging.\n");
	if (paging_init() == -1) {
		printf("[ERR ] Can't initialize the paging system.\n");
		return -1;
	}
	printf("[INFO] Paging initialized.\n");

	printf("[INFO] Kernel initialized.\n");
	return 0;
}

void
kernel_main(void) {
	printf("[INFO] Kerner started.\n");
	printf("[INFO] Hello, kernel World!\n");
	printf("[INFO] Kernel stopped.\n");
}
