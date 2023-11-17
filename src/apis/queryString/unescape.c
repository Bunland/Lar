#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <JavaScriptCore/JavaScript.h>

/*
 * Decodes a URL-encoded string by replacing percent-encoded characters with their original values.
 *
 * @param str               The URL-encoded input string to be decoded.
 *
 * @return                  Returns a dynamically allocated string containing the decoded result.
 *                          It is the caller's responsibility to free the allocated memory.
 */
char* unescape(const char *str) {
    // Allocate memory for the decoded string.
    char *decodedStr = malloc(strlen(str) + 1); // +1 for the null terminator
    
    // Check for memory allocation errors.
    if (decodedStr == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    int len = strlen(str);
    int i, j = 0;
    char hex[3] = {'\0'};

    // Iterate through each character in the URL-encoded string.
    for (i = 0; i < len; ++i) {
        // Check for percent-encoded characters.
        if (str[i] == '%' && i + 2 < len) {
            hex[0] = str[i + 1];
            hex[1] = str[i + 2];

            // Convert the hexadecimal part to an integer value.
            int value;
            sscanf(hex, "%x", &value);

            // Replace the escape code with the decoded character.
            decodedStr[j++] = (char)value;

            // Skip the two hexadecimal characters.
            i += 2;
        } else {
            // Keep the original character.
            decodedStr[j++] = str[i];
        }
    }

    // Add the null terminator at the end of the string.
    decodedStr[j] = '\0';

    return decodedStr;
}

/*
 * JavaScript function to decode a URL-encoded string using the unescape function.
 *
 * @param context           The JavaScript context.
 * @param function          The JavaScript function object.
 * @param thisObject        The JavaScript 'this' object.
 * @param argumentCount     The number of arguments passed to the function.
 * @param arguments         An array of arguments passed to the function.
 * @param exception         A pointer to a JavaScript value to store an exception if any.
 *
 * @return                  Returns a JavaScript string representing the decoded version of the input URL-encoded string.
 */
JSValueRef Unescape(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount < 1) {
        printf("The function requires one argument\n");
        return JSValueMakeUndefined(context);
    }

    // Convert the JavaScript string argument to a C string.
    JSStringRef str = JSValueToStringCopy(context, arguments[0], exception);
    size_t bufferSize = JSStringGetMaximumUTF8CStringSize(str);
    char * strCStr = (char*)malloc(bufferSize);

    // Check for memory allocation errors.
    if (strCStr == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    JSStringGetUTF8CString(str, strCStr, bufferSize);

    // Decode the URL-encoded string using the unescape function.
    char *strUnescape = unescape(strCStr);
    free(strCStr);

    // Create a JavaScript string from the decoded string.
    JSStringRef resultContent = JSStringCreateWithUTF8CString(strUnescape);
    free(strUnescape);

    // Create a JavaScript string value from the decoded string.
    JSValueRef resultValue = JSValueMakeString(context, resultContent);
    JSStringRelease(resultContent);

    // Release the allocated memory for the input string.
    JSStringRelease(str);

    // Return the JavaScript string value containing the decoded string.
    return resultValue;
}
