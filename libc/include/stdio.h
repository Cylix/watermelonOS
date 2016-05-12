#pragma once

#include <sys/cdefs.h>
#include <stdarg.h>

//! Function pointer type declaration
//! Flags handler must follow this prototype:
//!  > take as parameter a pointer to the va_list which can be modified
//!  > return the number of bytes printed
typedef int (*printf_flag_handler_t)(va_list*);

//! printf_flag_assoc
//! associate a flag to its handler
//!
//! Fields
//!  > flag: flag to be handled
//!  > handler: flag handler
typedef struct printf_flag_assoc_s {
  char flag;
  printf_flag_handler_t handler;
} printf_flag_assoc_t;

//! Different printf handlers, used internally by printf
//! Each handler can fetch the data it needs from the va_list argument
//! Each handler must return the number of printed characters
int printf_handle_percent(va_list*);
int printf_handle_flag_c(va_list*);
int printf_handle_flag_s(va_list*);
int printf_handle_flag_d(va_list*);
int printf_handle_flag_u(va_list*);
int printf_handle_flag_x(va_list*);
int printf_handle_flag_X(va_list*);

//! printf
//!   Formats and print arguments under the control of the format parameter
//!   Simple implementation, only support %c and %s flags and does not provide buffering
//!
//! Input:
//!   format: parameters formating definition
//!   vaargs: values to use for the formating
//!
//! Output:
//!   Number of bytes written
int printf(const char* restrict format, ...);

//! putchar
//!   Write the given char to stdout
//!
//! Input:
//!   c: character to print
//!
//! Output:
//!   The printed character or EOF in case of error
int putchar(int c);

//! puts
//!   Write the given null terminated string to stdout, followed by a newline
//!
//! Input:
//!   str: string to print
//!
//! Output:
//!   Nonnegative value on success, EOF otherwise
int puts(const char* str);
