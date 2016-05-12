#pragma once

#include <sys/cdefs.h>
#include <stddef.h>

//! NULL macro definition
#ifndef NULL
# define NULL (void*)0
#endif

//! abort
//!   Causes abnormal program termination
//!
//! Input:
//!   None
//!
//! Output:
//!   None
__attribute__((__noreturn__))
void abort(void);

//! itoa
//!   Convert integer number into string, using the given base
//!
//! Input:
//!   nb: number to convert
//!   nb_str: buffer in which the convertion will be stored.
//!           buffer should be large enough to contain conversion + null-terminating byte
//!           maximum theoretical size is sizeof(int)*8+1
//!   base: base to used for the conversion
//!
//! Output:
//!   size of the string convertion
size_t itoa(int nb, char* nb_str, unsigned int base);

//! uitoa
//!   Convert integer number into string, using the given base
//!   Similar to uitoa, but operates on unsigned numbers
//!
//! Input:
//!   nb: number to convert
//!   nb_str: buffer in which the convertion will be stored.
//!           buffer should be large enough to contain conversion + null-terminating byte
//!           maximum theoretical size is sizeof(int)*8+1
//!   base: base to used for the conversion
//!
//! Output:
//!   size of the string convertion
size_t uitoa(unsigned int nb, char* nb_str, unsigned int base);
