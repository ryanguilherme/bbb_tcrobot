/**
 * FILE
 * This library functions read and write on a file based on it's path
 */


#ifndef BBB_TCROBOT_FILE_H
#define BBB_TCROBOT_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/**
 * @name read_file
 * @details Read a input file and return what is written into
 * @param file_path
 * @return file_value
 */
int read_file(const char* file_path);
void write_file(char path[256], int value);

#endif //BBB_TCROBOT_FILE_H
