#include <stdio.h>

int
puts(const char* string) {
	//! TODO: optimize and do not use printf
	return printf("%s\n", string);
}
