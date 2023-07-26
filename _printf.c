#include "main.h"

/**
 * print_buffer - buffer
 * @buf: array of strings
 * @buf_i: Index
 */
void print_buffer(char buf[], int *buf_i)
{
	if (*buf_i > 0)
		write(1, &buf[0], *buf_i);

	*buf_i = 0;
}

/**
 * _printf - custom printf function
 * @format: format to look for
 * Return: length of the string
 */
int _printf(const char *format, ...)
{
	int i, output = 0, count_chars = 0;
	int flags, width, precision, size, buf_i = 0;
	va_list args;
	char buf[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			print_buffer(buf, &buf_i);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			++i;
			output = handle_print(format, &i, args, buf,
					flags, width, precision, size);
			if (output == -1)
				return (-1);
			count_chars += output;
		}
		else
		{
			buf[buf_i++] = format[i];
			if (buf_i == BUFF_SIZE)
			{
				print_buffer(buf, &buf_i);
				/* write(1, &format[i], 1);*/
			}
			count_chars++;
		}
	}
	print_buffer(buf, &buf_i);
	va_end(args);
	return (count_chars);
}
