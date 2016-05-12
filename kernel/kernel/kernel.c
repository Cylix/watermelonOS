#include <kernel/tty.h>
#include <stdio.h>
#include <multiboot.h>

void kernel_init(multiboot_info_t* multiboot_info) {
	tty_initialize();

	if (multiboot_info->flags & (1<<0)) {
		printf("mem_lower: %X\nmem_upper: %X\n\n",
					 multiboot_info->mem_lower * 1024,
					 multiboot_info->mem_upper * 1024);
	}

	if (multiboot_info->flags & (1<<5)) {
		memory_map_t* map = (memory_map_t*)multiboot_info->mmap_addr;

		while (map < multiboot_info->mmap_addr + multiboot_info->mmap_length) {
			printf("(MAP) [%u] %X %X (%X %X)\n",
						 map->type,
				 	 	 map->base_addr_high, map->base_addr_low,
						 map->length_high, map->length_low);

			map = (void*)map + map->size + sizeof(unsigned long);
		}
	}
}

void
kernel_main(void) {
	printf("\nHello, kernel World!\n");
}
