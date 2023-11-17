#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <JavaScriptCore/JavaScript.h>

/*
 * Escapes special characters in a string to create a URL-encoded version.
 *
 * @param str               The input string to be escaped.
 *
 * @return                  Returns a dynamically allocated URL-encoded string.
 */

char* escape(const char* str) {
    // Get the length of the input string.
    size_t len = strlen(str);

    // Allocate memory for the result string. Each character may be replaced with up to three characters.
    char* result = malloc(len * 3 + 1);
   
    if (result == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    
    // Pointer 'p' is used to traverse the result string.
    char* p = result;

    // Iterate through each character in the input string.
    for (size_t i = 0; i < len; i++) {
        // Check if the character is a space.
        if (str[i] == ' ') {
            // If it's a space, replace it with URL-encoded representation '%20'.
            p += snprintf(p, 4, "%%20");
        } 
        // Check if the character is one of the specified special characters.
        else if (strchr("&=?," , str[i]) != NULL) {
            // If it's a special character, replace it with its URL-encoded representation.
            p += snprintf(p, 4, "%%%02X", (unsigned char)str[i]);
        } 
        // If the character is neither a space nor a special character.
        else {
            // Copy the character to the result string.
            *p++ = str[i];
        }
    }

    // Null-terminate the result string.
    *p = '\0';

    // Return the dynamically allocated URL-encoded string.
    return result;
}

/*
 * JavaScript function to escape special characters in a string for URL encoding.
 *
 * @param context           The JavaScript context.
 * @param function          The JavaScript function object.
 * @param thisObject        The JavaScript 'this' object.
 * @param argumentCount     The number of arguments passed to the function.
 * @param arguments         An array of arguments passed to the function.
 * @param exception         A pointer to a JavaScript value to store an exception if any.
 *
 * @return                  Returns a JavaScript string representing the URL-encoded version of the input string.
 */
JSValueRef Escape(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount < 1) {
        printf("The function requires one argument\n");
        return JSValueMakeUndefined(context);
    }

    // Convert the JavaScript string argument to a C string.
    JSStringRef str = JSValueToStringCopy(context, arguments[0], exception);
    size_t bufferSize = JSStringGetMaximumUTF8CStringSize(str);
    char * strCStr = (char*)malloc(bufferSize);

    if (strCStr == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    JSStringGetUTF8CString(str, strCStr, bufferSize);

    // Escape special characters in the string using the escape function.
    char *strEscape = escape(strCStr);
    free(strCStr);

    // Create a JavaScript string from the escaped string.
    JSStringRef resultContent = JSStringCreateWithUTF8CString(strEscape);
    free(strEscape);

    // Create a JavaScript string value from the escaped string.
    JSValueRef resultValue = JSValueMakeString(context, resultContent);
    JSStringRelease(resultContent);

    // Release the allocated memory for the input string.
    JSStringRelease(str);

    // Return the JavaScript string value containing the escaped string.
    return resultValue;
}
