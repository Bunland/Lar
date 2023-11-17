#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

/*
 * Checks if a file exists.
 *
 * @param filename          The name of the file to be checked.
 *
 * @return                  Returns true if the file exists, false otherwise.
 */
bool fileExists(const char* filename) {
    // Attempt to open the file in read mode.
    FILE * file = fopen(filename, "r");

    // If the file is successfully opened, close it and return true.
    if (file) {
        fclose(file);
        return true;
    }

    // If the file cannot be opened, return false.
    return false;
}

/*
 * JavaScript function to check the existence of a file.
 *
 * @param context           The JavaScript context.
 * @param function          The JavaScript function object.
 * @param thisObject        The JavaScript 'this' object.
 * @param argumentCount     The number of arguments passed to the function.
 * @param arguments         An array of arguments passed to the function.
 * @param exception         A pointer to a JavaScript value to store an exception if any.
 *
 * @return                  Returns a JavaScript boolean indicating whether the file exists.
 */
JSValueRef Exist(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if (argumentCount < 1) {
        printf("The function requires one argument\n");
        return JSValueMakeUndefined(context);
    }

    // Convert the JavaScript string argument to a C string.
    JSStringRef filename = JSValueToStringCopy(context, arguments[0], exception);
    size_t bufferSize = JSStringGetMaximumUTF8CStringSize(filename);
    char * fileNameCStr = (char*)malloc(bufferSize);
    if (fileNameCStr == NULL) {
        // Error handling: Unable to allocate memory for fileNameCStr
        JSStringRelease(filename);  // Free memory before exiting
        perror("Error allocating memory for fileNameCStr");
        exit(EXIT_FAILURE);
    }
    JSStringGetUTF8CString(filename, fileNameCStr, bufferSize);

    // Check if the file exists using the fileExists function.
    bool result = fileExists(fileNameCStr);

    // Free the dynamically allocated C string and release the JavaScript string.
    free(fileNameCStr);
    JSStringRelease(filename);

    // Return a JavaScript boolean indicating the result.
    return JSValueMakeBoolean(context, result);
}
