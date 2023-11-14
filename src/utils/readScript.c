#include <stdio.h>
#include <stdlib.h>

/*
 * Reads the content of a file and returns it as a string.
 *
 * @param filename          The name of the file to be read.
 *
 * @return                  Returns a dynamically allocated buffer containing the content of the file.
 *                          Returns NULL if the file cannot be opened.
 */
char *readScript(const char *filename) {
    // Attempt to open the file in read mode.
    FILE *file = fopen(filename, "r");

    // If the file cannot be opened, print an error message and return NULL.
    if (file == NULL) {
        printf("Failed to open file\n");
        return NULL;
    }

    // Move the file pointer to the end of the file to determine its size.
    fseek(file, 0, SEEK_END);
    long sizeOfFile = ftell(file);

    // Move the file pointer back to the beginning of the file.
    // fseek(file, 0, SEEK_SET);
    rewind(file);

    // Allocate a buffer to hold the content of the file.
    char *buffer = (char *)malloc(sizeOfFile + 1);

    // Read the content of the file into the buffer.
    fread(buffer, 1, sizeOfFile, file);

    // Close the file.
    fclose(file);

    // Add a null terminator to the end of the buffer to create a valid C string.
    buffer[sizeOfFile] = '\0';

    // Return the dynamically allocated buffer containing the file content.
    return buffer;
}
