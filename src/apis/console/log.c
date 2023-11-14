#include <stdio.h>
#include <JavaScriptCore/JavaScript.h>

/*
 * JavaScript function to log messages to the console.
 *
 * @param context           The JavaScript context.
 * @param function          The JavaScript function object.
 * @param thisObject        The JavaScript 'this' object.
 * @param argumentCount     The number of arguments passed to the function.
 * @param arguments         An array of arguments passed to the function.
 * @param exception         A pointer to a JavaScript value to store an exception if any.
 *
 * @return                  Returns undefined.
 */
JSValueRef Log(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    // Iterate through the arguments and print each one to the console.
    for(size_t i = 0; i < argumentCount; i++) {
        // Convert the JavaScript value to a string.
        JSStringRef string = JSValueToStringCopy(context, arguments[i], NULL);

        // Get the size of the UTF-8 buffer needed to store the string.
        size_t bufferSize = JSStringGetMaximumUTF8CStringSize(string);

        // Allocate a buffer to hold the UTF-8 representation of the string.
        char buffer[bufferSize];

        // Convert the JavaScript string to UTF-8 and store it in the buffer.
        JSStringGetUTF8CString(string, buffer, bufferSize);

        // Print the string to the console.
        printf("%s", buffer);

        // Release the allocated memory for the JavaScript string.
        JSStringRelease(string);
    }

    // Print a new line after all arguments have been logged.
    printf("\n");

    // Return undefined.
    return JSValueMakeUndefined(context);
}
