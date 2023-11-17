#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

/*
 * Writes content to a file.
 *
 * @param filename          The name of the file to which content will be written.
 * @param content           The content to be written to the file.
 *
 * @return                  Returns true if the content is successfully written to the file, false otherwise.
 */
bool write(char * filename, char * content) {
    // Attempt to open the file in write mode.
    FILE *file = fopen(filename, "w");

    // If the file cannot be opened, return false.
    if(file == NULL) {
        return false;
    }

    // If content is not empty, write it to the file.
    if(content != NULL && content[0] != '\0') {
        fprintf(file, "%s", content);
    }

    // Close the file.
    fclose(file);

    // Return true to indicate successful writing of content to the file.
    return true;
}

/*
 * JavaScript function to write content to a file.
 *
 * @param context           The JavaScript context.
 * @param function          The JavaScript function object.
 * @param thisObject        The JavaScript 'this' object.
 * @param argumentCount     The number of arguments passed to the function.
 * @param arguments         An array of arguments passed to the function.
 * @param exception         A pointer to a JavaScript value to store an exception if any.
 *
 * @return                  Returns a JavaScript boolean indicating whether the content was successfully written to the file.
 */
JSValueRef Write(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount < 2) {
        printf("The function requires two arguments\n");
        return JSValueMakeUndefined(context);
    }

    // Convert the JavaScript string arguments to C strings.
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

    JSStringRef filecontent = JSValueToStringCopy(context, arguments[1], exception);
    size_t bufferContentSize = JSStringGetMaximumUTF8CStringSize(filecontent);
    char * fileContentCStr = (char*)malloc(bufferContentSize);
    if (fileContentCStr == NULL) {
        // Error handling: Unable to allocate memory for fileContentCStr
        free(fileNameCStr);  // Free memory before exiting
        JSStringRelease(filecontent);  // Free memory before exiting
        perror("Error allocating memory for fileContentCStr");
        exit(EXIT_FAILURE);
    }

    JSStringGetUTF8CString(filecontent, fileContentCStr, bufferContentSize);

    // Write content to the file using the write function.
    bool result = write(fileNameCStr, fileContentCStr);

    // Free the dynamically allocated memory for filenames and content.
    free(fileNameCStr);
    free(fileContentCStr);

    // Release the allocated memory for the JavaScript strings.
    JSStringRelease(filename);
    JSStringRelease(filecontent);

    // Return a JavaScript boolean indicating the result of the file writing operation.
    return JSValueMakeBoolean(context, result);
}
