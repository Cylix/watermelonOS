#include <kernel/memory/paging.h>
#include <kernel/memory/frame_allocator.h>

#include <i386/memory/paging.h>

#include <stdio.h>
#include <stdlib.h>

page_dir_t paging_page_directory = NULL;
page_tab_t paging_system_page_table = NULL;

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
  for (unsigned int i = 0; i < PAGING_PAGE_DIR_NB_ENTRIES; ++i)
    paging_page_directory[i] = PAGING_PAGE_DIR_EMPTY_ENTRY;

  //! First page table, providing identity mapping for kernel space
  paging_system_page_table = frame_allocator_alloc();

  if (paging_system_page_table == NULL) {
    printf("[ERR ] Can't allocate frame for page directory enry #0.\n");
    return -1;
  }

  //! Identity mapping of kernel space
  //! Avoid identity mapping addresses located after the kernel space
  for (unsigned int i = 0; i < PAGING_PAGE_TAB_NB_ENTRIES; ++i) {
    uint32_t addr = i * FRAME_ALLOC_FRAME_SIZE;
    if ((void*)addr < end_kernel_addr)
      paging_system_page_table[i] = addr | PAGING_PAGE_FLAG_RDWR | PAGING_PAGE_FLAG_PRESENT;
    else
      paging_system_page_table[i] = PAGING_PAGE_TAB_EMPTY_ENTRY;
  }
  //! Identity map the system page table
  paging_system_page_table[(uint32_t)paging_system_page_table / 4096] = (uint32_t)paging_system_page_table | PAGING_PAGE_FLAG_RDWR | PAGING_PAGE_FLAG_PRESENT;

  //! Store mapping as RD/Supervisor/Present
  paging_page_directory[0] = (unsigned int)paging_system_page_table | PAGING_PAGE_FLAG_RDWR | PAGING_PAGE_FLAG_PRESENT;

  //! load the directory and enable paging
  paging_load_page_directory(paging_page_directory);
  paging_enable();

  return 0;
}
