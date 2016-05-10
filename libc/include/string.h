#pragma once

#include <sys/cdefs.h>
#include <stddef.h>

//! memcmp
//!   Compare n first bytes of lhs and rhs memory location
//!
//! Input:
//!   lhs: first memory location to compare
//!   rhs: second memory location to compare
//!   n: number of bytes to compare
//!
//! Output:
//!   -1 if lhs is less than rhs, 1 if lhs is greater than rhs, 0 is they are equals
int memcmp(const void* lhs, const void* rhs, size_t n);

//! memcpy
//!   Copy n bytes from src into dst. Areas must not overlap (undefined behavior otherwise)
//!
//! Input:
//!   dst: where bytes will be copied
//!   src: location from which bytes will be fetched
//!   n: number of bytes to cpoy
//!
//! Output:
//!   dst pointer
void* memcpy(void* restrict dst, const void* restrict src, size_t n);

//! memmove
//!   Similar to memcpy, but pointers may overlap without falling in undefined behavior
//!
//! Input:
//!   dst: where bytes will be copied
//!   src: location from which bytes will be fetched
//!   n: number of bytes to copy
//!
//! Output:
//!   dst pointer
void* memmove(void* dst, const void* src, size_t n);

//! memset
//!   Sets n first bytes of the given memory location with the choosen value
//!
//! Input:
//!   dst: memory location to be set
//!   value: value that will be used to set the memory location
//!   n: number of bytes to set
//!
//! Output:
//!   dst pointer
void* memset(void* dst, int value, size_t n);

//! strlen
//!   Determine the length of a null-terminated characters string
//!
//! Input:
//!   str: null-terminated string for which length will be calculated
//!
//! Output:
//!   Length of the string
size_t strlen(const char* str);
