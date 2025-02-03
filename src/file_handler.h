#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

int file_exists(const char *filepath);
char *read_file(const char *filepath);
const char *get_content_type(const char *path);
int write_file(const char *filepath, const char *content);
int delete_file(const char *filepath);

#endif
