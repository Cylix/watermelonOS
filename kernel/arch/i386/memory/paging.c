#include <kernel/memory/paging.h>
#include <kernel/memory/frame_allocator.h>

#include <i386/memory/paging.h>

#include <stdio.h>
#include <stdlib.h>

page_dir_t paging_page_directory = NULL;

uint32_t first_page_table[1024] __attribute__((aligned(4096)));

unsigned int get_dir();

int
paging_init(void) {
  //! allocate frame to store the page directory
  paging_page_directory = frame_allocator_alloc();

  if (paging_page_directory == NULL) {
    printf("[ERR ] Can't allocate frame for the page directory.\n");
    return -1;
  }

  //! initialize the table with empty entries
  for (unsigned int i = 0; i < 1024; ++i)
    paging_page_directory[i] = PAGING_PAGE_DIR_EMPTY_ENTRY;

  //! First page table, providing identity mapping for kernel space
  page_tab_t page_directory_entry = frame_allocator_alloc();

  if (page_directory_entry == NULL) {
    printf("[ERR ] Can't allocate frame for page directory enry #0.\n");
    return -1;
  }

  //! Identity mapping of kernel space (TODO: clean & use defines)
  for (unsigned int j = 0; j < 1024; ++j)
    page_directory_entry[j] = (j * 0x1000) | 3;

  //! Store mapping as RD/Supervisor/Present (TODO: clean & use defines)
  paging_page_directory[0] = (unsigned int)page_directory_entry | 3;

  //! load the directory and enable paging
  paging_load_page_directory(paging_page_directory);
  paging_enable();

  return 0;
}
