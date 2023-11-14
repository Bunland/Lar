#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

/*
 * Reads the contents of a file and returns it as a dynamically allocated string.
 *
 * @param filename          The name of the file to be read.
 *
 * @return                  Returns a dynamically allocated string containing the file content.
 *                          Returns NULL if the file cannot be opened or read.
 */
char *readFile(char * filename) {
    // Attempt to open the file in read mode.
    FILE * file = fopen(filename, "r");

    // If the file cannot be opened, return NULL.
    if(file == NULL) {
        return NULL;
    }

    // Determine the size of the file.
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory for the file content.
    char * buffer = malloc(file_size + 1);

    // Read the file content into the buffer.
    size_t read_size = fread(buffer, 1, file_size, file);
    buffer[read_size] = '\0';

    // Close the file.
    fclose(file);

    // Return the dynamically allocated buffer containing the file content.
    return buffer;
}

/*
 * JavaScript function to read the contents of a file.
 *
 * @param context           The JavaScript context.
 * @param function          The JavaScript function object.
 * @param thisObject        The JavaScript 'this' object.
 * @param argumentCount     The number of arguments passed to the function.
 * @param arguments         An array of arguments passed to the function.
 * @param exception         A pointer to a JavaScript value to store an exception if any.
 *
 * @return                  Returns a JavaScript string containing the file content.
 *                          Returns an error message if the file cannot be opened or read.
 */
JSValueRef ReadFile(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount < 1) {
        printf("The function requires one argument\n");
        return JSValueMakeUndefined(context);
    }

    // Convert the JavaScript string argument to a C string.
    JSStringRef filename = JSValueToStringCopy(context, arguments[0], exception);
    size_t bufferSize = JSStringGetMaximumUTF8CStringSize(filename);
    char * fileNameCStr = (char*)malloc(bufferSize);
    JSStringGetUTF8CString(filename, fileNameCStr, bufferSize);

    // Read the contents of the file using the readFile function.
    char *fileContent = readFile(fileNameCStr);
    free(fileNameCStr);

    // Handle the case where the file does not exist.
    if(!fileContent) {
        char * message = "The file does not exist";
        JSStringRef resultContent = JSStringCreateWithUTF8CString(message);
        JSValueRef err = JSValueMakeString(context, resultContent);
        JSStringRelease(resultContent);
        return err;
    }

    // Create a JavaScript string from the file content.
    JSStringRef resultContent = JSStringCreateWithUTF8CString(fileContent);
    free(fileContent);

    // Create a JavaScript string value from the file content.
    JSValueRef resultValue = JSValueMakeString(context, resultContent);
    JSStringRelease(resultContent);

    // Release the allocated memory for the filename.
    JSStringRelease(filename);

    // Return the JavaScript string value containing the file content.
    return resultValue;
}
