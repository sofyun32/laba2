#ifndef OPERATIONS_H
#define OPERATIONS_H

void replace_text_regex(const char *filename, const char *pattern, const char *new_text);
void delete_lines_regex(const char *filename, const char *pattern);
void text_start(const char *filename, const char *text);
void text_end(const char *filename, const char *text);
char *read_file(const char *filename);
void write_file(const char *filename, const char *content);

#endif