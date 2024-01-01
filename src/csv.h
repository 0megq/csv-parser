char ***csv_parse_str(const char *str);
void csv_free_parse_str(char ***parsed);
char **csv_parse_line(const char *line, size_t *entry_count);
void csv_free_parse_line(char **parsed);
char **csv_split_by_newlines(const char *str, size_t *line_count);
void csv_free_split_by_newlines(char **split);