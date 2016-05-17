#pragma once

//! paging_init
//!   init paging by setting up a blank page directory
//!   thus store this blank directory in the CR3 register, thus effectively enabling paging
//!
//! Input:
//!   None
//!
//! Output:
//!   0 on success, -1 otherwise
//!   Error occurs when a frame can't be allocated from the frame allocator
int paging_init(void);
