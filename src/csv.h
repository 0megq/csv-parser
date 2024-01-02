const char *const *const *csv_parse_str(const char *str);
void csv_free_parse_str(const char *const *const *parsed);
const char *const *csv_parse_line(const char *line, size_t *entry_count);
void csv_free_parse_line(const char *const *parsed);
const char *const *csv_split_by_newlines(const char *str, size_t *line_count);
void csv_free_split_by_newlines(const char *const *split);