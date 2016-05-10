#pragma once

#include <sys/cdefs.h>

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
