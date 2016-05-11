#pragma once

#include <sys/cdefs.h>

//! NULL macro definition
#define NULL (void*)0

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
