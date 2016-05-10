#pragma once

#include <sys/cdefs.h>

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
