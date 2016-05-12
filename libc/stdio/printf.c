#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static printf_flag_assoc_t _flags[] = {
	{ '%', &printf_handle_percent },
	{ 'c', &printf_handle_flag_c },
	{ 's', &printf_handle_flag_s },
	{ 'd', &printf_handle_flag_d },
	{ 'u', &printf_handle_flag_u },
	{ 'x', &printf_handle_flag_x },
	{ 'X', &printf_handle_flag_X },
	{ 0, NULL }
};

static void
_print(const char* data, size_t data_length) {
	for (size_t i = 0; i < data_length; ++i)
		putchar((int)data[i]);
}

static int
_print_nb(va_list* parameters, char is_unsigned, unsigned int base) {
	int nb = va_arg(*parameters, int);

	//! allocate max number space + nullbyte + max prefix size (2 for 0x)
	//! also Initialize with base 16 prefix.
	//! this prefix will be erased for base that do not need it
	char nb_str[sizeof(int) * 8 + 1 + 2] = { '0', 'x' };
	size_t len = (base == 16 ? 2 : 0);

	if (is_unsigned)
		len += uitoa((unsigned int)nb, nb_str + len, base);
	else
		len += itoa(nb, nb_str + len, base);

	_print(nb_str, len);

	return len;
}

int
printf_handle_percent(__attribute__ ((unused)) va_list* parameters) {
	char c = '%';

	_print(&c, sizeof(char));

	return 1;
}

int
printf_handle_flag_c(va_list* parameters) {
	char c = (char)va_arg(*parameters, int);

	_print(&c, sizeof(char));

	return 1;
}

int
printf_handle_flag_s(va_list* parameters) {
	const char* s = va_arg(*parameters, const char*);
	const size_t len = strlen(s);

	_print(s, len);

	return len;
}

int
printf_handle_flag_d(va_list* parameters) {
	return _print_nb(parameters, 0, 10);
}

int
printf_handle_flag_u(va_list* parameters) {
	return _print_nb(parameters, 1, 10);
}

int
printf_handle_flag_x(va_list* parameters) {
	return _print_nb(parameters, 0, 16);
}

int
printf_handle_flag_X(va_list* parameters) {
	return _print_nb(parameters, 1, 16);
}

int
printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') {
		if (*format != '%') {
			_print(format, sizeof(char));
			++written;
			++format;
		}
		else {
			++format;
			for (size_t i = 0; _flags[i].flag; ++i)
				if (_flags[i].flag == *format) {
					written += (*_flags[i].handler)(&parameters);
					break;
				}
			++format;
		}
	}

	va_end(parameters);

	return written;
}
