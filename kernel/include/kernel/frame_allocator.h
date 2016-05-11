#pragma once

#include <stdint.h>

//! Typedef for convenience
typedef void* frame_t;

//! Address the variable is the address of the end of kernel space
//! Serves as starting point for frame allocation
//! This had been defined in kernel/arch/XXX/linker.ld
//!
//! start_frame simply stores the address of end_kernel and makes code clearer
extern uint32_t end_kernel;
extern frame_t start_frame;

//! Simple macro to define how free and used states are represented
#define FRAME_ALLOC_FREE 1
#define FRAME_ALLOC_USED 0

//! Set the size of allocated frames
#define FRAME_ALLOC_FRAME_SIZE 4096

//! bitmap that references the different frames and their states
//! very small: only support 32 frames
extern uint32_t frame_alloc_map;

//! kalloc_frame
//!   Very simple frame allocator: allocates and return the first free frame.
//!   Allocation is not optimized and is O(n).
//!   Frames are FRAME_ALLOC_FRAME_SIZE wide.
//!
//! Input:
//!   None
//!
//! Output:
//!   Address of the allocated frame, NULL otherwise
frame_t kalloc_frame(void);

//! kalloc_frame
//!  Free the given frame such that it can be reallocated later
//!
//! Input:
//!   Address of the allocated frame to free
//!
//! Output:
//!   None
void kfree_frame(frame_t frame);
