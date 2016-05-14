#include <kernel/frame_allocator.h>
#include <stdlib.h>
#include <stdio.h>

void* end_kernel_addr = &end_kernel;
frame_allocator_free_segment_t* _free_frames_stack = NULL;

void
_store_segment(void* segment, uint32_t size) {
  frame_allocator_free_segment_t* free_segment = (frame_allocator_free_segment_t*)segment;

  free_segment->size = size;
  free_segment->next = _free_frames_stack;
  _free_frames_stack = free_segment;
}

int
frame_allocator_init(multiboot_info_t* multiboot_info) {
  if (MULTIBOOT_INFO_GET_FLAG(multiboot_info->flags, MULTIBOOT_INFO_MEM_MAP) == 0) {
    printf("[ERR] Memory map has not been initialized by the bootloader.\n");
    return -1;
  }

	for (memory_map_t* map = (memory_map_t*)multiboot_info->mmap_addr;
       (uint32_t)map < multiboot_info->mmap_addr + multiboot_info->mmap_length;
       map = (void*)map + map->size + sizeof(unsigned long))
  {
    //! Skip reserved segments of memory
    if (map->type != MULTIBOOT_INFO_USABLE_SEGMENT)
      continue;

    //! If base_addr_high is nonzero, then the given segment could not be handled by our 32bits architecture
    //! Thus, we skip that kind of segments
    if (map->base_addr_high > 0)
      continue;

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
      continue;

		printf("[INFO] Usable memory segment from %p to %p (%X bytes)\n",
			 	 	 segment_start, segment_end, (unsigned int)(segment_end - segment_start));

    _store_segment(segment_start, segment_end - segment_start);
	}

  return 0;
}

frame_t
frame_allocator_alloc(void) {
  // for (uint8_t i = 0; i < 31; ++i) {
  //   if ((frame_alloc_map & (1 << (31 - i))) == FRAME_ALLOC_FREE) {
  //     //! Toggle bit corresponding to that frame, so that it is marked as used (0)
  //     frame_alloc_map &= ~(1 << (31 - i));
  //     //! Return the corresponding frame, starting from start_frame (aka end_kernel)
  //     return start_frame + (i * FRAME_ALLOC_FRAME_SIZE);
  //   }
  // }
  //
  return NULL;
}

void
frame_allocator_free(frame_t frame) {
  // uint32_t idx = ((uint32_t)frame / FRAME_ALLOC_FRAME_SIZE) - (uint32_t)start_frame;
  //
  // //! Simply set the bit representing the corresponding frame to free (1)
  // frame_alloc_map |= 1 << (31 - idx);
}
