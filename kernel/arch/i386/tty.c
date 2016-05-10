#include <kernel/tty.h>

static tty_state_t state;

void
tty_initialize(void) {
  state.row     = 0;
  state.column  = 0;
  state.color   = VGA_make_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

  for (size_t y = 0; y < VGA_HEIGHT; ++y)
    for (size_t x = 0; x < VGA_WIDTH; ++x)
      VGA_print_at(' ', state.color, x, y);
}

void
tty_setcolor(enum vga_color fg, enum vga_color bg) {
  state.color = VGA_make_color(fg, bg);
}

void
tty_putchar(char c) {
  VGA_print_at(c, state.color, state.column, state.row);

  if (++state.column == VGA_WIDTH)
    tty_break_line();
}

void
tty_putstr(const char* str) {
  for (size_t i = 0; str[i] != '\0'; ++i)
    if (str[i] == '\n')
      tty_break_line();
    else
      tty_putchar(str[i]);
}

void
tty_write(const char* str, size_t length) {
  for (size_t i = 0; i < length; ++i)
    if (str[i] == '\n')
      tty_break_line();
    else
      tty_putchar(str[i]);
}

void
tty_break_line(void) {
  state.column = 0;

  if (++state.row == VGA_HEIGHT)
    tty_scroll();
}

void
tty_scroll(void) {
  //! move every line to the top (start processing from line 1, not 0)
  for (size_t y = 1; y < VGA_HEIGHT; ++y)
    for (size_t x = 0; x < VGA_WIDTH; ++x) {
      const size_t prev_row_pos = (y - 1) * VGA_WIDTH + x;
      const size_t curr_row_pos = y * VGA_WIDTH + x;
      VGA_set_at(prev_row_pos, VGA_get_at(curr_row_pos));
    }
  //! Ensure that last line is emptied
  for (size_t x = 0; x < VGA_WIDTH; ++x)
    VGA_print_at(' ', state.color, x, VGA_HEIGHT - 1);

  //! scroll cursor
  --state.row;
}
