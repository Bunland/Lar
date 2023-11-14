#include <stdio.h>
#include <stdlib.h>
#include "../includes/functions.h"
#include <JavaScriptCore/JavaScript.h>

/*
 * Evaluates JavaScript code from a file using a provided JavaScript context and global object.
 *
 * @param filename          The name of the file containing the JavaScript code.
 * @param context           The JavaScript context in which the code will be evaluated.
 * @param globalObject      The global object to be used during the evaluation.
 *
 * @return                  There is no explicit return value.
 */
void interpreter(char *filename, JSContextRef context, JSObjectRef globalObject) {
    // Read the content of the JavaScript file.
    char *fileContent = readScript(filename);

    // Create a JavaScript string from the file content.
    JSStringRef jsCode = JSStringCreateWithUTF8CString(fileContent);

    // Evaluate the JavaScript code.
    JSValueRef exception = NULL;
    JSEvaluateScript(context, jsCode, NULL, NULL, 0, &exception);

    // Check if an exception occurred during evaluation.
    if (exception) {
        // Get the size of the buffer needed to store the error message.
        size_t bufferSize = JSStringGetMaximumUTF8CStringSize(JSValueToStringCopy(context, exception, NULL));
        char buffer[bufferSize];
        
        // Get the UTF-8 string representing the error message.
        JSStringGetUTF8CString(JSValueToStringCopy(context, exception, NULL), buffer, bufferSize);
        
        // Print the error message.
        printf("%s\n", buffer);
    }

    // Release the allocated resources.
    JSStringRelease(jsCode);
    free(fileContent);
}
