#include <stdio.h>

#if defined(__is_kernel)
#include <kernel/display/tty.h>
#endif

int
putchar(int int_c) {
#if defined(__is_kernel)
	char c = (char)int_c;
	tty_write(&c, sizeof(c));
#else
	// TODO: You need to implement a write system call.
#endif
	return int_c;
}
