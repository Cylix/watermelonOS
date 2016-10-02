#include <kernel/memory/paging.h>
#include <kernel/memory/frame_allocator.h>

#include <i386/memory/paging.h>

#include <stdio.h>
#include <stdlib.h>

page_tab_t paging_page_directory[PAGING_PAGE_DIR_NB_ENTRIES];
page_tab_t paging_virtual_page_tables[PAGING_PAGE_DIR_NB_ENTRIES];
page_tab_t paging_page_tables[PAGING_PAGE_DIR_NB_ENTRIES];

int
paging_init(void) {
  //! initialize the directory with newly allocated page tables
  for (unsigned int i = 0; i < PAGING_PAGE_DIR_NB_ENTRIES; ++i) {
    paging_page_tables[i] = frame_allocator_alloc();

    if (paging_page_tables[i] == NULL) {
      printf("[ERR ] Can't allocate frame for page directory entry #%d.\n", i);
      return -1;
    }

    //! Store mapping as RD/Supervisor/Present
    paging_page_directory[i] = (page_tab_t)((uint32_t)paging_page_tables[i] | PAGING_PAGE_FLAG_RDWR | PAGING_PAGE_FLAG_PRESENT);
  }

  //! Fill in page tables
  unsigned int k = 0;
  for (unsigned int i = 0; i < PAGING_PAGE_DIR_NB_ENTRIES; ++i) {
    for (unsigned int j = 0; j < PAGING_PAGE_TAB_NB_ENTRIES; ++j) {
      page_tab_t addr = (page_tab_t)(i * PAGING_PAGE_TAB_NB_ENTRIES * FRAME_ALLOC_FRAME_SIZE + j * FRAME_ALLOC_FRAME_SIZE);

      //! Identity mapping of kernel space
      if ((void*)addr < end_kernel_addr)
        paging_page_tables[i][j] = (uint32_t)addr | PAGING_PAGE_FLAG_RDWR | PAGING_PAGE_FLAG_PRESENT;
      //! Virtual addressing for page tables addresses
      else if (k < PAGING_PAGE_DIR_NB_ENTRIES) {
        paging_page_tables[i][j] = (uint32_t)paging_page_tables[k] | PAGING_PAGE_FLAG_RDWR | PAGING_PAGE_FLAG_PRESENT;
        paging_virtual_page_tables[k] = addr;
        ++k;
      }
      //! Avoid identity mapping addresses located after the kernel space
      else
        paging_page_tables[i][j] = PAGING_PAGE_TAB_EMPTY_ENTRY;
    }
  }

  //! load the directory and enable paging
  paging_load_page_directory(paging_page_directory);
  paging_enable();

  return 0;
}
