#include <string.h>
#include <stdlib.h>
#include "csv.h"

static size_t count_char(const char *str, char c);
static int get_char_index(const char *str, char c);

const char *const *const *csv_parse_str(const char *str)
{
	size_t line_count = 0; // Stores how many lines are in the given string
	const char *const *lines = csv_split_by_newlines(str, &line_count);
	char ***buffer; // Stores the string
	buffer = calloc(line_count + 1, sizeof(char **));
	size_t entry_index; // Stores the index of the current entry in the current line in the buffer
	size_t entry_count; // Stores how many entries are in the current line
	for (size_t line_index = 0; line_index < line_count; line_index++)
	{
		entry_count = 0;
		const char *const *line_entries = csv_parse_line(lines[line_index], &entry_count);

		buffer[line_index] = calloc(entry_count + 1, sizeof(char *));

		for (entry_index = 0; entry_index < entry_count; entry_index++)
		{
			buffer[line_index][entry_index] = strdup(line_entries[entry_index]);
		}
		csv_free_parse_line(line_entries);
		buffer[line_index][entry_index] = NULL;
	}
	csv_free_split_by_newlines(lines);
	buffer[line_count] = NULL;
	return (const char *const *const *)buffer;
}

void csv_free_parse_str(const char *const *const *parsed)
{
	if (!parsed)
		return;

	char ***parsed_ptr = (void *)parsed;
	while (*parsed_ptr)
	{
		char **parsed_ptr_ptr = *parsed_ptr;
		while (*parsed_ptr_ptr)
		{
			free(*parsed_ptr_ptr);
			parsed_ptr_ptr++;
		}
		free(*parsed_ptr);
		parsed_ptr++;
	}
	free((void *)parsed);
}

const char *const *csv_parse_line(const char *line, size_t *entry_count)
{
	if (!entry_count)
		return NULL;

	if (!line)
	{
		*entry_count = 0;
		return NULL;
	}
	if (!*line)
	{
		line = ",";
	}

	*entry_count = count_char(line, ',');
	if (line[strlen(line) - 1] != ',')
		(*entry_count)++;

	char **buffer, **buffer_ptr;
	buffer_ptr = buffer = calloc(*entry_count + 1, sizeof(char *));
	size_t entry_place = 0;
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
	return (const char *const *)buffer;
}

void csv_free_parse_line(const char *const *parsed)
{
	if (!parsed)
		return;

	char **parsed_ptr = (void *)parsed;
	while (*parsed_ptr)
	{
		free(*parsed_ptr);
		parsed_ptr++;
	}
	free((void *)parsed);
}

const char *const *csv_split_by_newlines(const char *str, size_t *line_count)
{
	if (!line_count)
		return NULL;
	if (!str) // dealing with NULL pointer
	{
		*line_count = 0;
		return NULL;
	}
	if (!*str) // dealing with an empty string AKA pointer to NULL
	{
		str = "\n";
	}

	*line_count = count_char(str, '\n');
	if (str[strlen(str) - 1] != '\n')
		(*line_count)++;

	char **buffer, **buffer_ptr;
	buffer_ptr = buffer = calloc(*line_count + 1, sizeof(char *));
	size_t line_place = 0;
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
	return (const char *const *)buffer;
}

void csv_free_split_by_newlines(const char *const *split)
{
	if (!split)
		return;

	char **split_ptr = (void *)split;
	while (*split_ptr)
	{
		free(*split_ptr);
		*split_ptr = NULL;
		split_ptr++;
	}
	free((void *)split);
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