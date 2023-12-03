#include "../inc/file.h"

int read_file(const char* file_path) {
    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char file_value;
    if (read(fd, &file_value, sizeof(file_value)) == -1) {
        perror("Failed to read file value");
        exit(EXIT_FAILURE);
    }

    close(fd);

    return file_value - '0';
}

void write_file(char path[256], int value) {
    int fd = open(path, O_WRONLY);

    if (fd < 0) {
        perror("Failed to open file");
        exit(1);
    }

    char str_value[2];
    snprintf(str_value, sizeof(str_value), "%d", value);
    write(fd, str_value, strlen(str_value));
    close(fd);
}
