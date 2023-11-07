#include <JavaScriptCore/JavaScript.h>

/*
* Creates a custom function in JavaScript.
*
* @param context           The JavaScript context in which the function will be created.
* @param globalObject      The global object to which the custom function will be attached.
* @param functionName      The name of the function to be created in JavaScript.
* @param functionCallback  A pointer to the C/C++ function that will execute when the JavaScript function is invoked.
* 
* @return                 There is no explicit return value.
*/

void createCustomFunction(JSContextRef context, JSObjectRef globalObject, const char *functionName, JSObjectCallAsFunctionCallback functionCallback) {
    // Create a JavaScript string from the function name in UTF-8 format.
    JSStringRef functionString = JSStringCreateWithUTF8CString(functionName);

    // Create a JavaScript function object using the string and the function callback.
    JSObjectRef functionObject = JSObjectMakeFunctionWithCallback(context, functionString, functionCallback);

    // Set the newly created function as a property of the global object.
    JSObjectSetProperty(context, globalObject, functionString, functionObject, kJSPropertyAttributeNone, NULL);

    // Release the function string created with JSStringCreateWithUTF8CString to prevent memory leaks.
    JSStringRelease(functionString);
}