#include <stdio.h>
#include "../includes/console.h"
#include <JavaScriptCore/JavaScript.h>

/*
 * Creates a custom function in the console object.
 *
 * @param context           The JavaScript context in which the function will be created.
 * @param consoleGlobalObject The global object representing the console.
 * @param functionName      The name of the function to be created in the console.
 * @param functionCallback  A pointer to the C/C++ function that will execute when the console function is invoked.
 * 
 * @return                 There is no explicit return value.
 */
void consoleCustomFunction(JSContextRef context, JSObjectRef consoleGlobalObject, const char *functionName, JSObjectCallAsFunctionCallback functionCallback) {

    // Create a JavaScript string from the function name in UTF-8 format.
    JSStringRef functionString = JSStringCreateWithUTF8CString(functionName);

    // Create a JavaScript function object using the string and the function callback.
    JSObjectRef functionObject = JSObjectMakeFunctionWithCallback(context, functionString, functionCallback);

    // Set the newly created function as a property of the console object.
    JSObjectSetProperty(context, consoleGlobalObject, functionString, functionObject, kJSPropertyAttributeNone, NULL);

    // Release the function string created with JSStringCreateWithUTF8CString to prevent memory leaks.
    JSStringRelease(functionString);
}

/*
 * Adds console functions to the global object.
 *
 * @param context           The JavaScript context.
 * @param globalObject      The global object to which the console object will be attached.
 */
void consoleApis(JSContextRef context, JSObjectRef globalObject) {
    // Create a JavaScript string representing the name 'console'.
    JSStringRef console = JSStringCreateWithUTF8CString("console");

    // Create a JavaScript object to represent the console.
    JSObjectRef consoleGlobalObject = JSObjectMake(context, NULL, NULL);

    // Set the console object as a property of the global object.
    JSObjectSetProperty(context, globalObject, console, consoleGlobalObject, kJSClassAttributeNone, NULL);
 
    // Add custom console functions (e.g., 'log') to the console object.
    consoleCustomFunction(context, consoleGlobalObject, "log", Log);

    // Release the allocated memory for the 'console' string.
    JSStringRelease(console);
}
