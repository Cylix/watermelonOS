#pragma once

#include <stddef.h>
#include <stdint.h>

#define VGA_BUFFER_ADDR 0xB8000
#define VGA_WIDTH       80
#define VGA_HEIGHT      25


//! Hardware text mode color constants.
enum vga_color {
  COLOR_BLACK         = 0,
  COLOR_BLUE          = 1,
  COLOR_GREEN         = 2,
  COLOR_CYAN          = 3,
  COLOR_RED           = 4,
  COLOR_MAGENTA       = 5,
  COLOR_BROWN         = 6,
  COLOR_LIGHT_GREY    = 7,
  COLOR_DARK_GREY     = 8,
  COLOR_LIGHT_BLUE    = 9,
  COLOR_LIGHT_GREEN   = 10,
  COLOR_LIGHT_CYAN    = 11,
  COLOR_LIGHT_RED     = 12,
  COLOR_LIGHT_MAGENTA = 13,
  COLOR_LIGHT_BROWN   = 14,
  COLOR_WHITE         = 15,
};

//! VGA_driver_VGA_state
//! attributes defining the current state of the terminal
//!
//! Fields:
//!   row: cursor row
//!   column: cursor column
//!   color: current color used to print characters
//!   buffer: address of the VGA buffer
typedef struct VGA_driver_state_s {
  size_t     row;
  size_t     column;
  uint8_t    color;
  uint16_t*  buffer;
} VGA_driver_state_t;

//! VGA_driver_initialize
//!   Initialize the VGA driver.
//!   Must be called before using any other VGA_driver_ function
//!
//! Input:
//!   None
//!
//! Output:
//!   None
void VGA_driver_initialize(void);

//! VGA_driver_setcolor
//!   Change the color used to display characters
//!
//! Input:
//!   fg: foreground color
//!   bg: background color
//!
//! Output:
//!   None
void VGA_driver_setcolor(enum vga_color fg, enum vga_color bg);

//! VGA_driver_putchar
//!   Print a single character onto the terminal
//!   Move the cursor
//!
//! Input:
//!   c: character to print
//!
//! Output:
//!   None
void VGA_driver_putchar(char c);

//! VGA_driver_writestring
//!   Write a string onto the terminal
//!   Move the cursor
//!
//! Input:
//!   data: string to print
//!
//! Output:
//!   None
void VGA_driver_writestring(const char* data);
