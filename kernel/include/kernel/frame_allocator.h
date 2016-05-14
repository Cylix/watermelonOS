#pragma once

#include <stdint.h>
#include <multiboot.h>

//! Address the variable is the address of the end of kernel space
//! Serves as starting point for frame allocation
//! This had been defined in kernel/arch/XXX/linker.ld
extern uint32_t end_kernel;
//! Convenience variable
extern void* const end_kernel_addr;

//! Set the size of allocated frames
#define FRAME_ALLOC_FRAME_SIZE 4096

//! Returns the wanted flag from multiboot_info_t.flags
#define MULTIBOOT_INFO_GET_FLAG(flags, x) (flags & (1<<x))
//! Memory map flag index in the multiboot_info_t.flags field
#define MULTIBOOT_INFO_MEM_MAP 5
//! Value of memory_map_t.type indicating that the segment of memory is usable
#define MULTIBOOT_INFO_USABLE_SEGMENT 1

//! frame_alloc_free_segment
//! free frames are stored within a stack of free segments (that can contain multiple frames)
//! this stack is initialized from the multiboot memory map at kernel initialization
//!
//! Fields:
//!   size: size of the free memory segment
//!   next: pointer to the next free memory segment
typedef struct frame_allocator_free_segment_s {
  uint32_t size;
  struct frame_allocator_free_segment_s* next;
} frame_allocator_free_segment_t;

//! Typedef for convenience
typedef void* frame_t;

//! frame_allocator_init
//!   Initialize the frame_allocator with the multiboot_info structure
//!   This has the effect to localize free memory areas
//!   If this function is not called, the frame_allocator won't be able to allocate frames
//!
//! Input:
//!   multiboot_info: pointer to the multiboot_info structure initialized by the bootloader
//!
//! Output:
//!   0 on success, -1 otherwise
//!   Error occurs when the memory map of the multiboot_info structure has not been initialized
int frame_allocator_init(const multiboot_info_t* multiboot_info);

//! frame_allocator_alloc
//!   Very simple frame allocator: allocates and return the first free frame.
//!   Allocation is O(1) as free pages are stored within a stack.
//!   Frames are FRAME_ALLOC_FRAME_SIZE wide.
//!
//! Input:
//!   None
//!
//! Output:
//!   Address of the allocated frame, NULL otherwise (no more free frames available)
frame_t frame_allocator_alloc(void);

//! frame_allocator_free
//!   Free the given frame such that it can be reallocated later
//!   The frame to be free must be a frame returned earlier by frame_allocator_alloc
//!   Moreover, freeing an already freed frame is undefined
//!   The deallocation is O(1) but does not provide any checking
//!
//! Input:
//!   Address of the allocated frame to free
//!
//! Output:
//!   None
void frame_allocator_free(frame_t frame);
