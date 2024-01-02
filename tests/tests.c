#include <stdio.h>
#include <stdlib.h>
#include "../src/csv.h"

char *load_file_as_string(const char *file_name);
void unload_file_text(char *text);
void test_csv_split_by_newlines(void);
void test_csv_parse_line(void);
void test_csv_parse_str(void);

int main()
{
	// test_csv_split_by_newlines();
	// test_csv_parse_line();
	test_csv_parse_str();
	return 0;
}

void test_csv_parse_str(void)
{
	printf("----------------------------------------\n");
	printf("Running csv_parse_str test...\n");
	printf("----------------------------------------\n");
	char *text = load_file_as_string("tests/test.csv");
	if (!text)
		return;

	const char *const *const *parsed = csv_parse_str(text);

	printf("Printing parsed csv as table...\n");
	for (size_t i = 0; parsed[i] != NULL; i++)
	{
		printf("%llu: [", i + 1);
		for (size_t j = 0; parsed[i][j] != NULL; j++)
		{
			printf(" %llu {%s},", j + 1, parsed[i][j]);
		}
		printf("]\n");
	}
	csv_free_parse_str(parsed);
}

void test_csv_parse_line(void)
{
	printf("----------------------------------------\n");
	printf("Running csv_parse_line test...\n");
	printf("----------------------------------------\n");
	size_t entry_count = 0;
	const char *const *parsed_line = csv_parse_line("hello,fhji,df,idlik", &entry_count);

	printf("%llu entries:\n", entry_count);
	for (size_t i = 0; i < entry_count; i++)
	{
		printf("%s\n", parsed_line[i]);
	}
	csv_free_parse_line(parsed_line);
}

void test_csv_split_by_newlines(void)
{
	printf("----------------------------------------\n");
	printf("Running csv_split_by_newlines test...\n");
	printf("----------------------------------------\n");

	char *text = load_file_as_string("tests/test.csv");
	if (!text)
		return;

	size_t line_count = 0;
	const char *const *split_by_nl = csv_split_by_newlines(text, &line_count);

	printf("%llu lines:\n", line_count);
	for (size_t i = 0; i < line_count; i++)
	{
		printf("%s\n", split_by_nl[i]);
	}
	csv_free_split_by_newlines(split_by_nl);

	unload_file_text(text);
}

char *load_file_as_string(const char *file_name)
{
	FILE *file = fopen(file_name, "r");
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
