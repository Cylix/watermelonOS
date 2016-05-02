#pragma once

#include <stddef.h>

//! strlen
//!   Compute and return the length of a string
//!
//! Input:
//!   str: string for which the length will be computed
//!        pointer assumed to be valid (no check against NULL)
//!
//! Output:
//!   Length of the string
size_t strlen(const char* str);
