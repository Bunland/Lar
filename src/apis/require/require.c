#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>
#include "../../includes/functions.h"

/*
 * JavaScript function to emulate the 'require' function.
 *
 * @param context           The JavaScript context.
 * @param function          The JavaScript function object.
 * @param thisObject        The JavaScript 'this' object.
 * @param argumentCount     The number of arguments passed to the function.
 * @param arguments         An array of arguments passed to the function.
 * @param exception         A pointer to a JavaScript value to store an exception if any.
 *
 * @return                  Returns the exported value from the required module.
 *                          Returns undefined if the module cannot be loaded.
 */
JSValueRef Require(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount < 1) {
        // If no argument is provided, return undefined.
        return JSValueMakeUndefined(context);
    }

    // Convert the JavaScript string argument to a C string.
    JSStringRef moduleName = JSValueToStringCopy(context, arguments[0], exception);
    size_t bufferSize = JSStringGetMaximumUTF8CStringSize(moduleName);
    char * moduleNameCStr = (char*)malloc(bufferSize);
    JSStringGetUTF8CString(moduleName, moduleNameCStr, bufferSize);

    // Read the content of the required module.
    char * fileContent = readScript(moduleNameCStr);

    // Check if the module content is not NULL.
    if(fileContent != NULL) {
        // Create a JavaScript string representing the 'exports' object.
        JSStringRef exportName = JSStringCreateWithUTF8CString("exports");

        // Create an empty JavaScript object to store the module exports.
        JSObjectRef exportObject = JSObjectMake(context, NULL, NULL);

        // Set the 'exports' object as a property of the global object.
        JSObjectSetProperty(context, JSContextGetGlobalObject(context), exportName, exportObject, kJSClassAttributeNone, NULL);

        // Create a JavaScript string from the module content.
        JSStringRef script = JSStringCreateWithUTF8CString(fileContent);

        // Evaluate the module content in the global context.
        JSEvaluateScript(context, script, NULL, NULL, 0, exception);

        // Release the allocated memory for the module content.
        JSStringRelease(script);
        free(fileContent);

        // Get the 'exports' object from the global context.
        JSValueRef exportValue = JSObjectGetProperty(context, JSContextGetGlobalObject(context), exportName, NULL);

        // Release the allocated memory for the 'exports' string.
        JSStringRelease(exportName);

        // Return the exported value from the required module.
        return exportValue;
    }

    // If the module content is NULL, return undefined.
    return JSValueMakeUndefined(context);
}

/*
 * Function to expose the 'require' function in the JavaScript context.
 *
 * @param context           The JavaScript context.
 * @param globalObject      The global object to which the 'require' function will be attached.
 */
void requireFunction(JSContextRef context, JSObjectRef globalObject) {
    // Create a JavaScript string representing the name 'require'.
    JSStringRef requireName = JSStringCreateWithUTF8CString("require");

    // Create a JavaScript function object with the 'Require' function callback.
    JSObjectRef requireFunction = JSObjectMakeFunctionWithCallback(context, requireName, Require);

    // Set the 'require' function as a property of the global object.
    JSObjectSetProperty(context, globalObject, requireName, requireFunction, kJSClassAttributeNone, NULL);

    // Release the allocated memory for the 'require' string.
    JSStringRelease(requireName);
}
