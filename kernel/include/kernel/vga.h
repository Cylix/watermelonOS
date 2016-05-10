#pragma once

#include <stddef.h>
#include <stdint.h>

//! Physical address of the VGA Buffer
#define VGA_BUFFER_ADDR 0xB8000
//! Dimension of the VGA screen
#define VGA_WIDTH       80
#define VGA_HEIGHT      25

//! VGA_Buffer
static uint16_t* const VGA_buffer = (uint16_t* const)VGA_BUFFER_ADDR;

//! Hardware text mode color constants.
enum vga_color {
  VGA_COLOR_BLACK         = 0,
  VGA_COLOR_BLUE          = 1,
  VGA_COLOR_GREEN         = 2,
  VGA_COLOR_CYAN          = 3,
  VGA_COLOR_RED           = 4,
  VGA_COLOR_MAGENTA       = 5,
  VGA_COLOR_BROWN         = 6,
  VGA_COLOR_LIGHT_GREY    = 7,
  VGA_COLOR_DARK_GREY     = 8,
  VGA_COLOR_LIGHT_BLUE    = 9,
  VGA_COLOR_LIGHT_GREEN   = 10,
  VGA_COLOR_LIGHT_CYAN    = 11,
  VGA_COLOR_LIGHT_RED     = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN   = 14,
  VGA_COLOR_WHITE         = 15,
};

//! VGA_make_color
//!   Build the 8 bits value to define foreground & backgroudn color
//!
//! Input:
//!   fg: foreground color
//!   bg: background color
//!
//! Output:
//!   8 bits value containing the color configuration
static inline uint8_t
VGA_make_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

//! VGA_make_entry
//!   Build the 16 bits value to define a character and its color
//!
//! Input:
//!   c: character to format
//!   color: color used to display the character
//!
//! Output:
//!   16 bits value containing the character and its color configuration
static inline uint16_t
VGA_make_entry(char c, uint8_t color) {
  uint16_t c_16b = c;
  uint16_t color_16b = color;

  return c_16b | color_16b << 8;
}

//! VGA_set_at
//!   Store the given 16bit formated entry at the given offset
//!
//! Input:
//!   entry: already entry to be stored
//!   offset: offset position at which value will be stored
//!
//! Output:
//!   None
static inline void
VGA_set_at(uint16_t entry, size_t offset) {
  VGA_buffer[offset] = entry;
}

//! VGA_get_at
//!   Return the 16bit formated entry at the given position
//!
//! Input:
//!   offset: offset position at which value will be fetched
//!
//! Output:
//!   Value stored at the given position
static inline uint16_t
VGA_get_at(size_t offset) {
  return VGA_buffer[offset];
}

//! VGA_print_at
//!   Print the given character with the given color at the given position
//!
//! Input:
//!   c: character to print
//!   color: color used to display the character
//!   x: x position
//!   y: y position
//!
//! Output:
//!   None
static inline void
VGA_print_at(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  VGA_set_at(VGA_make_entry(c, color), index);
}
