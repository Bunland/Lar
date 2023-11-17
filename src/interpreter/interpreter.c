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
    JSValueRef result =  JSEvaluateScript(context, jsCode, NULL, NULL, 1, &exception);
    // JSValueRef result = JSEvaluateScript(context, scriptStr, NULL, NULL, 1, NULL);


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

    // Imprimir el resultado (debería ser un objeto JavaScript)
    // JSStringRef resultStr = JSValueCreateJSONString(context, result, 0, NULL);
    // size_t bufferSize = JSStringGetMaximumUTF8CStringSize(resultStr);
    // char* buffer = (char*)malloc(bufferSize);
    // JSStringGetUTF8CString(resultStr, buffer, bufferSize);
    // printf("JSON Result: %s\n", buffer);

    // // Liberar recursos
    // free(buffer);
    // JSStringRelease(resultStr);
    // JSGlobalContextRelease(context);


    // Release the allocated resources.
    JSStringRelease(jsCode);
    free(fileContent);
}
