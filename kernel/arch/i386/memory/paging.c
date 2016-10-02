#include <kernel/memory/paging.h>
#include <kernel/memory/frame_allocator.h>

#include <i386/memory/paging.h>

#include <stdio.h>
#include <stdlib.h>

page_dir_t paging_page_directory = NULL;
page_dir_t paging_page_tables[PAGING_PAGE_DIR_NB_ENTRIES] __attribute__((aligned(FRAME_ALLOC_FRAME_SIZE)));

unsigned int get_dir();

int
paging_init(void) {
  //! allocate frame to store the page directory
  paging_page_directory = frame_allocator_alloc();

  if (paging_page_directory == NULL) {
    printf("[ERR ] Can't allocate frame for the page directory.\n");
    return -1;
  }

  //! initialize the directory with newly allocated page tables
  for (unsigned int i = 0; i < PAGING_PAGE_DIR_NB_ENTRIES; ++i) {
    paging_page_tables[i] = frame_allocator_alloc();

    if (paging_page_tables[i] == NULL) {
      printf("[ERR ] Can't allocate frame for page directory entry #%d.\n", i);
      return -1;
    }

    //! Store mapping as RD/Supervisor/Present
    paging_page_directory[i] = (uint32_t)paging_page_tables[i] | PAGING_PAGE_FLAG_RDWR | PAGING_PAGE_FLAG_PRESENT;
  }

  //! Identity mapping of kernel space
  //! Avoid identity mapping addresses located after the kernel space
  for (unsigned int i = 0; i < PAGING_PAGE_DIR_NB_ENTRIES; ++i) {
    for (unsigned int j = 0; j < PAGING_PAGE_TAB_NB_ENTRIES; ++j) {
      uint32_t addr = i * PAGING_PAGE_TAB_NB_ENTRIES * FRAME_ALLOC_FRAME_SIZE + j * FRAME_ALLOC_FRAME_SIZE;

      if ((void*)addr < end_kernel_addr)
        paging_page_tables[i][j] = addr | PAGING_PAGE_FLAG_RDWR | PAGING_PAGE_FLAG_PRESENT;
      else
        paging_page_tables[i][j] = PAGING_PAGE_TAB_EMPTY_ENTRY;
    }
  }

  //! Identity map the system page table
  for (unsigned int i = 0; i < PAGING_PAGE_DIR_NB_ENTRIES; ++i) {
    unsigned int page_dir_idx = (uint32_t)paging_page_tables[i] / (PAGING_PAGE_TAB_NB_ENTRIES * FRAME_ALLOC_FRAME_SIZE);
    unsigned int page_tab_idx = (uint32_t)paging_page_tables[i] % (PAGING_PAGE_TAB_NB_ENTRIES * FRAME_ALLOC_FRAME_SIZE) / FRAME_ALLOC_FRAME_SIZE;

    paging_page_tables[page_dir_idx][page_tab_idx] = (uint32_t)paging_page_tables[i] | PAGING_PAGE_FLAG_RDWR | PAGING_PAGE_FLAG_PRESENT;
  }

  //! load the directory and enable paging
  paging_load_page_directory(paging_page_directory);
  paging_enable();

  return 0;
}
