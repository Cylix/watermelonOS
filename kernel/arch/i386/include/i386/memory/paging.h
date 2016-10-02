#pragma once

//! typedef for convenience
typedef uint32_t* page_dir_t;
typedef uint32_t* page_tab_t;

extern page_dir_t paging_page_directory;

//! Page directory and page table configuration: flags bits positions
#define PAGING_PAGE_FLAG_GLOBAL_BIT_POS          8
#define PAGING_PAGE_FLAG_SIZE_BIT_POS            7
#define PAGING_PAGE_FLAG_DIRTY_BIT_POS           6
#define PAGING_PAGE_FLAG_ACCESSED_BIT_POS        5
#define PAGING_PAGE_FLAG_CACHE_DISABLED_BIT_POS  4
#define PAGING_PAGE_FLAG_WR_THROUGH_BIT_POS      3
#define PAGING_PAGE_FLAG_USER_BIT_POS            2
#define PAGING_PAGE_FLAG_RDWR_BIT_POS            1
#define PAGING_PAGE_FLAG_PRESENT_BIT_POS         0

//! Page directory and page table configuration: flags bits values
#define PAGING_PAGE_FLAG_GLOBAL                 (1 << PAGING_PAGE_FLAG_GLOBAL_BIT_POS)
#define PAGING_PAGE_FLAG_SIZE                   (1 << PAGING_PAGE_FLAG_SIZE_BIT_POS)
#define PAGING_PAGE_FLAG_DIRTY                  (1 << PAGING_PAGE_FLAG_DIRTY_BIT_POS)
#define PAGING_PAGE_FLAG_ACCESSED               (1 << PAGING_PAGE_FLAG_ACCESSED_BIT_POS)
#define PAGING_PAGE_FLAG_CACHE_DISABLED         (1 << PAGING_PAGE_FLAG_CACHE_DISABLED_BIT_POS)
#define PAGING_PAGE_FLAG_WR_THROUGH             (1 << PAGING_PAGE_FLAG_WR_THROUGH_BIT_POS)
#define PAGING_PAGE_FLAG_USER                   (1 << PAGING_PAGE_FLAG_USER_BIT_POS)
#define PAGING_PAGE_FLAG_RDWR                   (1 << PAGING_PAGE_FLAG_RDWR_BIT_POS)
#define PAGING_PAGE_FLAG_PRESENT                (1 << PAGING_PAGE_FLAG_PRESENT_BIT_POS)

//! Defines for convenience and code clarity
#define PAGING_PAGE_DIR_EMPTY_ENTRY     0x00000000
#define PAGING_PAGE_TAB_EMPTY_ENTRY     0x00000000

//! Size of page directory and page table
#define PAGING_PAGE_DIR_NB_ENTRIES      1024
#define PAGING_PAGE_TAB_NB_ENTRIES      1024

//! paging_load_page_directory
//!   load the given page directory so that it can be used by the CPU for address translation
//!   enable_paging() must also be called at least once to enable paging
//!
//! Input:
//!   directory: page directory (that is, array of page tables)
//!
//! Output:
//!   None, the operation is always successful
void paging_load_page_directory(frame_t directory);

//! paging_enable
//!   Enable hardware paging.
//!   Once enabled, the loaded page directory (load_page_directory()) will be used for address translation
//!
//! Input:
//!   None
//!
//! Output:
//!   None, the operation is always successful
void paging_enable(void);
