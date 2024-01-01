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
	int entry_count = count_char(line, ',');
	if (line[strlen(line) - 1] != ',')
		entry_count++;

	char **buffer, **buffer_ptr;
	buffer_ptr = buffer = calloc(entry_count + 1, sizeof(char *));
	int entry_place = 0;
	if (!buffer)
		return NULL;

	while (*line)
	{
		if (!*buffer_ptr)
		{
			int entry_length = get_char_index(line, ',');
			if (entry_length < 0)
				entry_length = strlen(line);
			*buffer_ptr = calloc(entry_length + 1, sizeof(char)); // start here. allocating memory for strings in string array
			if (!*buffer_ptr)
				return NULL;
		}
		if (*line == ',')
		{
			buffer_ptr[0][entry_place] = '\0';
			if (line[1])
			{
				entry_place = 0;
				buffer_ptr++;
			}
		}
		else
		{
			buffer_ptr[0][entry_place++] = *line;
		}

		line++;
	}
	buffer_ptr[0][entry_place] = '\0';
	buffer_ptr[1] = NULL;
	return buffer;
}

void csv_free_parse_line(char **parsed)
{
	if (!parsed)
		return;

	char **parsed_ptr = parsed;
	while (*parsed_ptr)
	{
		free(*parsed_ptr);
		parsed_ptr++;
	}
	free(parsed);
}

char **csv_split_by_newlines(const char *str)
{
	int line_count = count_char(str, '\n');
	if (str[strlen(str) - 1] != '\n')
		line_count++;

	char **buffer, **buffer_ptr;
	buffer_ptr = buffer = calloc(line_count + 1, sizeof(char *));
	int line_place = 0;
	if (!buffer)
		return NULL;

	while (*str)
	{

		if (!*buffer_ptr)
		{
			int line_length = get_char_index(str, '\n');
			if (line_length < 0)
				line_length = strlen(str);
			*buffer_ptr = calloc(line_length + 1, sizeof(char)); // start here. allocating memory for strings in string array
			if (!*buffer_ptr)
				return NULL;
		}
		if (*str == '\n')
		{
			buffer_ptr[0][line_place] = '\0';
			if (str[1])
			{
				line_place = 0;
				buffer_ptr++;
			}
		}
		else
		{
			buffer_ptr[0][line_place++] = *str;
		}

		str++;
	}
	buffer_ptr[0][line_place] = '\0';
	buffer_ptr[1] = NULL;
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
		*split_ptr = NULL;
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