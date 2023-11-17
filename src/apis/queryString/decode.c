#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <JavaScriptCore/JavaScript.h>

/*
 * Structure representing a key-value pair.
 */
typedef struct {
    char * key;    // The key of the pair.
    char * value;  // The value associated with the key.
} keyValue;


char * decode(char * queryString) {
    char * result = strdup("{");
    char * token = strtok(queryString, "=&");

    while(token != NULL) {
        keyValue kv;
        kv.key = strdup(token);

        token = strtok(NULL, "=&");

        if(token != NULL){
            kv.value = strdup(token);
            char * keyValueStr = malloc(strlen(kv.key) + strlen(kv.value) + 6);
            if (keyValueStr == NULL) {
                perror("Error allocating memory");
                exit(EXIT_FAILURE);
            }

            sprintf(keyValueStr, "\"%s\": \"%s\"", kv.key, kv.value);
            result = realloc(result, strlen(result) + strlen(keyValueStr) + 3);
            if (result == NULL) {
                free(kv.value);
                free(keyValueStr);
                perror("Error reallocating memory for result");
                exit(EXIT_FAILURE);
            }
            strcat(result, keyValueStr);
            strcat(result, ", ");
            free(keyValueStr);
            free(kv.value);
        }

        free(kv.key);
        token = strtok(NULL, "=&");
    }

    if(strlen(result) > 1) {
        result[strlen(result) - 2] = '}';
        result[strlen(result) - 1] = '\0';
    } else {
        result[1] = '}';
        result[2] = '\0';
    }
    return result;
}

/*
 * Decodes a query string to a JSON-formatted string.
 *
 * @param queryString       The query string to be decoded.
 *
 * @return                  Returns a dynamically allocated JSON-formatted string.
 */
// char* decode(char* queryString) {
//     // Initialize an empty string for the result.
//     char* result = strdup("{");

//     // Use an indicator to add a comma after the first key-value pair.
//     int firstKey = 1;

//     // Tokenize the query string based on '=' and '&'.
//     char* token = strtok(queryString, "=&");

//     while (token != NULL) {
//         keyValue kv;
//         kv.key = strdup(token);

//         token = strtok(NULL, "=&");

//         if (token != NULL) {
//             kv.value = strdup(token);

//             // Add a comma before the next key-value pair if it's not the first.
//             if (!firstKey) {
//                 strcat(result, ", ");
//             } else {
//                 // Change the indicator after adding the first key-value pair.
//                 firstKey = 0;
//             }

//             // Add the key-value pair to the result.
//             strcat(result, "\"");
//             strcat(result, kv.key);
//             strcat(result, "\": \"");
//             strcat(result, kv.value);
//             strcat(result, "\"");

//             // Free memory for the value.
//             free(kv.value);
//         }

//         // Free memory for the key.
//         free(kv.key);
        
//         // Move to the next token in the query string.
//         token = strtok(NULL, "=&");
//     }

//     // Add the closing of the JSON string.
//     strcat(result, "}");

//     return result;
// }

/*
 * JavaScript function to decode a query string to a JSON-formatted string.
 *
 * @param context           The JavaScript context.
 * @param function          The JavaScript function object.
 * @param thisObject        The JavaScript 'this' object.
 * @param argumentCount     The number of arguments passed to the function.
 * @param arguments         An array of arguments passed to the function.
 * @param exception         A pointer to a JavaScript value to store an exception if any.
 *
 * @return                  Returns a JavaScript object representing the decoded JSON string.
 */
JSValueRef Decode(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if (argumentCount < 1) {
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

    // Decode the query string using the decode function.
    char* decodedStr = decode(strCStr);

    // Create a JavaScript object directly from the decoded string.
    JSStringRef jsonStr = JSStringCreateWithUTF8CString(decodedStr);
    JSValueRef jsonValue = JSValueMakeFromJSONString(context, jsonStr);

    // Free memory.
    JSStringRelease(str);
    JSStringRelease(jsonStr);
    free(decodedStr);

    // Convert the JavaScript object to a JSON string.
    JSStringRef resultStr = JSValueCreateJSONString(context, jsonValue, 0, exception);

    // Return the JSON string.
    return JSValueMakeFromJSONString(context, resultStr);
}