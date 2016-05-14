#include <kernel/memory/frame_allocator.h>
#include <stdlib.h>
#include <stdio.h>

void* const end_kernel_addr = &end_kernel;
frame_allocator_free_segment_t* _free_segments_stack = NULL;

static void
_store_segment(void* segment, uint32_t size) {
  frame_allocator_free_segment_t* free_segment = (frame_allocator_free_segment_t*)segment;

  free_segment->size = size;
  free_segment->next = _free_segments_stack;
  _free_segments_stack = free_segment;
}

static void
_analyze_segment(const memory_map_t* map) {
  //! Skip reserved segments of memory
  if (map->type != MULTIBOOT_INFO_USABLE_SEGMENT)
    return;

  //! If base_addr_high is nonzero, then the given segment could not be handled by our 32bits architecture
  //! Thus, we skip that kind of segments
  if (map->base_addr_high > 0)
    return;

  //! Determine the start of the segment
  //! Ensure that segment always starts after the kernel address space
  void* segment_start;
  if (map->base_addr_low < (uint32_t)end_kernel_addr)
    segment_start = end_kernel_addr;
  else
    segment_start = (void*)map->base_addr_low;

  //! Determine the end of the segment
  //! Ensure that there is no overflow when adding the length to the base_addr
  //! Since our architecture is 32bits, we have to make sure to truncate unadressable segments
  void* segment_end;
  if (map->length_high || 0xFFFFFFFF - map->length_low > 0xFFFFFFFF - map->base_addr_low)
    segment_end = (void*)0xFFFFFFFF;
  else
    segment_end = (void*)map->base_addr_low + map->length_low;

  //! If segment is entirely located before the kernel address space, skip it
  if (segment_end < end_kernel_addr)
    return;

  printf("[INFO] Usable memory segment from %p to %p (%X bytes)\n",
         segment_start, segment_end, (unsigned int)(segment_end - segment_start));

  _store_segment(segment_start, segment_end - segment_start);
}

int
frame_allocator_init(const multiboot_info_t* multiboot_info) {
  if (MULTIBOOT_INFO_GET_FLAG(multiboot_info->flags, MULTIBOOT_INFO_MEM_MAP) == 0) {
    printf("[ERR ] Memory map has not been initialized by the bootloader.\n");
    return -1;
  }

  //! iterate over the memory map
  //! for more information about memory mapping storage, see multiboot specifications
	for (memory_map_t* map = (memory_map_t*)multiboot_info->mmap_addr;
       (uint32_t)map < multiboot_info->mmap_addr + multiboot_info->mmap_length;
       map = (void*)map + map->size + sizeof(unsigned long))
  {
    _analyze_segment(map);
	}

  return 0;
}

frame_t
frame_allocator_alloc(void) {
  if (_free_segments_stack == NULL)
    return NULL;

  frame_t frame = (frame_t)_free_segments_stack;

  //! if segment is larger than frame size, split it to use the remainder later
  //! otherwise, jump to the next free segment
  if (_free_segments_stack->size > FRAME_ALLOC_FRAME_SIZE) {
    frame_allocator_free_segment_t* remainder = (void*)_free_segments_stack + FRAME_ALLOC_FRAME_SIZE;

    remainder->size = _free_segments_stack->size - FRAME_ALLOC_FRAME_SIZE;
    remainder->next = _free_segments_stack->next;
    _free_segments_stack = remainder;
  }
  else
    _free_segments_stack = _free_segments_stack->next;

  return frame;;
}

void
frame_allocator_free(frame_t frame) {
  _store_segment(frame, FRAME_ALLOC_FRAME_SIZE);
}
