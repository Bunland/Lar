#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

/*
 * Removes a file from the file system.
 *
 * @param filename          The name of the file to be removed.
 *
 * @return                  Returns true if the file is successfully removed, false otherwise.
 */
bool removeFile(char * filename) {
    // Use the remove function to delete the file.
    return remove(filename) == 0;
}

/*
 * JavaScript function to remove a file from the file system.
 *
 * @param context           The JavaScript context.
 * @param function          The JavaScript function object.
 * @param thisObject        The JavaScript 'this' object.
 * @param argumentCount     The number of arguments passed to the function.
 * @param arguments         An array of arguments passed to the function.
 * @param exception         A pointer to a JavaScript value to store an exception if any.
 *
 * @return                  Returns a JavaScript boolean indicating whether the file was successfully removed.
 */
JSValueRef Remove(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount < 1) {
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

    // Remove the file using the removeFile function.
    bool result = removeFile(fileNameCStr);
    free(fileNameCStr);

    // Release the allocated memory for the filename.
    JSStringRelease(filename);

    // Return a JavaScript boolean indicating the result of the file removal operation.
    return JSValueMakeBoolean(context, result);
}
