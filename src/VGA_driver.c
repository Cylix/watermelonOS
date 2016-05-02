#include "VGA_driver.h"

static VGA_driver_state_t state;

static uint8_t
VGA_driver_make_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

static uint16_t
VGA_driver_make_vgaentry(char c, uint8_t color) {
  uint16_t c16 = c;
  uint16_t color16 = color;

  return c16 | color16 << 8;
}

static void
VGA_driver_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  state.buffer[index] = VGA_driver_make_vgaentry(c, color);
}

void
VGA_driver_initialize(void) {
  state.row     = 0;
  state.column  = 0;
  state.color   = VGA_driver_make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  state.buffer  = (uint16_t*)VGA_BUFFER_ADDR;

  for (size_t y = 0; y < VGA_HEIGHT; ++y)
    for (size_t x = 0; x < VGA_WIDTH; ++x)
      VGA_driver_putentryat(' ', state.color, x, y);
}

void
VGA_driver_setcolor(enum vga_color fg, enum vga_color bg) {
  state.color = VGA_driver_make_color(fg, bg);
}

void
VGA_driver_putchar(char c) {
  VGA_driver_putentryat(c, state.color, state.column, state.row);

  if (++state.column == VGA_WIDTH) {
    state.column = 0;
    if (++state.row == VGA_HEIGHT) {
      state.row = 0;
    }
  }
}

void
VGA_driver_writestring(const char* data) {
  for (size_t i = 0; data[i] != '\0'; ++i)
    VGA_driver_putchar(data[i]);
}
