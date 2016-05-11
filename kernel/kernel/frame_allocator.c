#include <kernel/frame_allocator.h>
#include <stdlib.h>

uint32_t frame_alloc_map = FRAME_ALLOC_FREE;
frame_t  start_frame     = &end_kernel;

frame_t
kalloc_frame(void) {
  for (uint8_t i = 0; i < 31; ++i) {
    if ((frame_alloc_map & (1 << (31 - i))) == FRAME_ALLOC_FREE) {
      //! Toggle bit corresponding to that frame, so that it is marked as used (0)
      frame_alloc_map &= ~(1 << (31 - i));
      //! Return the corresponding frame, starting from start_frame (aka end_kernel)
      return start_frame + (i * FRAME_ALLOC_FRAME_SIZE);
    }
  }

  return NULL;
}

void
kfree_frame(frame_t frame) {
  uint32_t idx = ((uint32_t)frame / FRAME_ALLOC_FRAME_SIZE) - (uint32_t)start_frame;

  //! Simply set the bit representing the corresponding frame to free (1)
  frame_alloc_map |= 1 << (31 - idx);
}
