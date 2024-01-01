#include <string.h>
#include <stdlib.h>
#include "csv.h"

static size_t count_char(const char *str, char c);
static int get_char_index(const char *str, char c);

char ***csv_parse_str(const char *str)
{
}

void csv_free_parse_str(char ***parsed)
{
}

char **csv_parse_line(const char *line)
{
}

void csv_free_parse_line(char **parsed)
{
}

char **csv_split_by_newlines(const char *str)
{
	int line_count = count_char(str, '\n');
	char **buffer, **buffer_ptr;
	buffer_ptr = buffer = calloc(line_count + 1, sizeof(char *));
	int line_place = 0;
	if (!buffer)
		return NULL;

	while (*str)
	{

		if (!*buffer_ptr)
		{
			*buffer_ptr = calloc((get_char_index(str, '\n') + 1), sizeof(char)); // start here. allocating memory for strings in string array
			if (!*buffer_ptr)
				return NULL;
		}
		if (*str == '\n')
		{
			(*buffer_ptr)[line_place] = '\0';
			if (str[1])
			{
				line_place = 0;
				buffer_ptr++;
			}
		}
		else
		{
			(*buffer_ptr)[line_place++] = *str;
		}

		str++;
	}
	(*buffer_ptr)[line_place] = '\0';
	*(buffer_ptr + 1) = NULL;
	return buffer;
}

void csv_free_split_by_newlines(char **split)
{
	if (!split)
		return;

	char **split_ptr = split;
	while (*split_ptr)
	{
		free(*split_ptr);
		split_ptr++;
	}
	free(split);
}

static size_t count_char(const char *str, char c)
{
	int i = 0;
	while (*str != '\0')
	{
		if (*str == c)
			i++;
		str++;
	}
	return i;
}

static int get_char_index(const char *str, char c)
{
	char *c_ptr = strchr(str, c);
	return (c_ptr) ? (int)(c_ptr - str) : -1;
}