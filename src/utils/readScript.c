#include <stdio.h>
#include <stdlib.h>

char * readScript(const char * filename) {
    FILE * file = fopen(filename, "r");

    if(file == NULL) {
        printf("Filed to open file\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size_file = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(size_file + 1);
    fread(buffer, 1, size_file, file);
    fclose(file);
    buffer[size_file] = '\0';
    return buffer;
}