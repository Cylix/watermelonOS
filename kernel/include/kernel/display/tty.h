#pragma once

#include <stddef.h>
#include <stdint.h>

//! tty_state
//! attributes defining the current state of the terminal
//!
//! Fields:
//!   row: cursor row
//!   column: cursor column
//!   color: current color used to print characters
typedef struct tty_state_s {
  size_t     row;
  size_t     column;
  uint8_t    color;
} tty_state_t;

//! tty_initialize
//!   Initialize the tty.
//!   Must be called before using any other tty_ function
//!
//! Input:
//!   None
//!
//! Output:
//!   None
void tty_initialize(void);

//! tty_putchar
//!   Print a single character onto the terminal
//!   Move the cursor
//!
//! Input:
//!   c: character to print
//!
//! Output:
//!   None
void tty_putchar(char c);

//! tty_putstr
//!   Write a null-terminated string onto the terminal
//!   Move the cursor
//!
//! Input:
//!   str: string to print
//!
//! Output:
//!   None
void tty_putstr(const char* str);

//! tty_write
//!   Write a string of a given length onto the terminal
//!   Move the cursor
//!
//! Input:
//!   str: string to print
//!   length: number of bytes to print
//!
//! Output:
//!   None
void tty_write(const char* str, size_t length);

//! tty_break_line
//!   Break line and do scrolling if necessary
//!
//! Input:
//!   None
//!
//! Output:
//!   None
void
tty_break_line(void);

//! tty_scroll
//!   Scroll the printed data 1 line to the top
//!   Cursor also scroll
//!
//! Input:
//!   None
//!
//! Output:
//!   None
void
tty_scroll(void);
