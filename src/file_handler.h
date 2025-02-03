#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

int file_exists(const char *filepath);
char *read_file(const char *filepath);
const char *get_content_type(const char *path);

#endif
