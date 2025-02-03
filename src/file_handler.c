#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int file_exists(const char *filepath) { return access(filepath, F_OK) == 0; }

char *read_file(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file)
        return NULL;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    return buffer;
}

const char *get_content_type(const char *path) {
    if (strstr(path, ".html"))
        return "text/html";
    if (strstr(path, ".css"))
        return "text/css";
    if (strstr(path, ".js"))
        return "application/javascript";
    if (strstr(path, ".png"))
        return "image/png";
    if (strstr(path, ".jpg"))
        return "image/jpeg";
    return "application/octet-stream";
}

int write_file(const char *filepath, const char *content) {
    printf("Trying to write to file: %s\n", filepath);
    printf("Content to write: %s\n", content);

    FILE *file = fopen(filepath, "w");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }

    int result = fprintf(file, "%s", content);
    fclose(file);

    if (result < 0) {
        printf("Failed to write content to file.\n");
        return 0;
    }

    printf("File written successfully.\n");
    return 1;
}

int delete_file(const char *filepath) { return remove(filepath) == 0; }
