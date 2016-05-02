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
VGA_driver_print_at(char c, uint8_t color, size_t x, size_t y) {
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
      VGA_driver_print_at(' ', state.color, x, y);
}

void
VGA_driver_setcolor(enum vga_color fg, enum vga_color bg) {
  state.color = VGA_driver_make_color(fg, bg);
}

void
VGA_driver_putchar(char c) {
  VGA_driver_print_at(c, state.color, state.column, state.row);

  if (++state.column == VGA_WIDTH)
    VGA_driver_break_line();
}

void
VGA_driver_break_line(void) {
  state.column = 0;

  if (++state.row == VGA_HEIGHT)
    VGA_driver_scroll();
}

void
VGA_driver_scroll(void) {
  //! move every line to the top (start processing from line 1, not 0)
  for (size_t y = 1; y < VGA_HEIGHT; ++y)
    for (size_t x = 0; x < VGA_WIDTH; ++x) {
      const size_t prev_row_pos = (y - 1) * VGA_WIDTH + x;
      const size_t curr_row_pos = y * VGA_WIDTH + x;
      state.buffer[prev_row_pos] = state.buffer[curr_row_pos];
    }
  //! Ensure that last line is emptied
  for (size_t x = 0; x < VGA_WIDTH; ++x)
    VGA_driver_print_at(' ', state.color, x, VGA_HEIGHT - 1);

  //! scroll cursor
  --state.row;
}

void
VGA_driver_putstr(const char* str) {
  for (size_t i = 0; str[i] != '\0'; ++i)
    if (str[i] == '\n')
      VGA_driver_break_line();
    else
      VGA_driver_putchar(str[i]);
}
