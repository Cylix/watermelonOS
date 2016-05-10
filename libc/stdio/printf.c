#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void
print(const char* data, size_t data_length) {
	for (size_t i = 0; i < data_length; ++i)
		putchar((int)data[i]);
}

int
printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		if (*format != '%') {
			print(format, sizeof(char));
			++written;
			++format;
			continue;
		}

		++format;
		if (*format == '%') {
			print(format, sizeof(char));
			++written;
		}
		else if (*format == 'c') {
			char c = (char)va_arg(parameters, int);
			print(&c, sizeof(char));
			++written;
		}
		else if (*format == 's') {
			const char* s = va_arg(parameters, const char*);
			const size_t len = strlen(s);
			print(s, len);
			written += len;
		}
		++format;
	}

	va_end(parameters);

	return written;
}
