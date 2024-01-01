#include <stdio.h>
#include <stdlib.h>
#include "../src/csv.h"

char *load_file_as_string(const char *file_name);
void unload_file_text(char *text);
void test_csv_split_by_newlines(const char *input);

int main()
{
	char *text = load_file_as_string("tests/test.csv");
	if (!text)
		return -1;
	test_csv_split_by_newlines(text);
	unload_file_text(text);
	return 0;
}

void test_csv_split_by_newlines(const char *input)
{
	char **split_by_nl = csv_split_by_newlines(input);
	char **ptr = split_by_nl;
	while (*ptr)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
	csv_free_split_by_newlines(split_by_nl);
}

char *load_file_as_string(const char *file_name)
{
	FILE *file = fopen(file_name, "rb");
	char *buffer;
	size_t length;
	size_t count;

	if (!file)
	{
		printf("Failed to load file\n");
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer = malloc((length + 1) * sizeof(char));
	if (!buffer)
	{
		printf("Failed to allocate memory\n");
		return NULL;
	}

	count = fread(buffer, sizeof(char), length, file);
	if (count < length)
	{
		printf("Reallocating buffer\n");
		buffer = realloc(buffer, count + 1);
	}

	buffer[count] = '\0';
	fclose(file);
	return buffer;
}

void unload_file_text(char *text)
{
	free(text);
}
