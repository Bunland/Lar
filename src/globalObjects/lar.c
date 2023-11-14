#include "../includes/fs.h"
#include <JavaScriptCore/JavaScript.h>

/*
 * Creates a custom function in the lar object.
 *
 * @param context           The JavaScript context in which the function will be created.
 * @param larGlobalObject   The global object representing the lar object.
 * @param functionName      The name of the function to be created in the lar object.
 * @param functionCallback  A pointer to the C/C++ function that will execute when the lar function is invoked.
 * 
 * @return                 There is no explicit return value.
 */
void larCustomFunction(JSContextRef context, JSObjectRef larGlobalObject, const char *functionName, JSObjectCallAsFunctionCallback functionCallback) {

    // Create a JavaScript string from the function name in UTF-8 format.
    JSStringRef functionString = JSStringCreateWithUTF8CString(functionName);

    // Create a JavaScript function object using the string and the function callback.
    JSObjectRef functionObject = JSObjectMakeFunctionWithCallback(context, functionString, functionCallback);

    // Set the newly created function as a property of the lar object.
    JSObjectSetProperty(context, larGlobalObject, functionString, functionObject, kJSPropertyAttributeNone, NULL);

    // Release the function string created with JSStringCreateWithUTF8CString to prevent memory leaks.
    JSStringRelease(functionString);
}

/*
 * Adds file system functions to the global object under the lar namespace.
 *
 * @param context           The JavaScript context.
 * @param globalObject      The global object to which the lar object will be attached.
 */
void larApis(JSContextRef context, JSObjectRef globalObject) {
    // Create a JavaScript string representing the name 'lar'.
    JSStringRef lar = JSStringCreateWithUTF8CString("lar");

    // Create a JavaScript object to represent the lar object.
    JSObjectRef larGlobalObject = JSObjectMake(context, NULL, NULL);

    // Set the lar object as a property of the global object.
    JSObjectSetProperty(context, globalObject, lar, larGlobalObject, kJSClassAttributeNone, NULL);
 
    // Add custom lar functions (e.g., 'exists', 'readFile', 'remove', 'write') to the lar object.
    larCustomFunction(context, larGlobalObject, "exists", Exist);
    larCustomFunction(context, larGlobalObject, "readFile", ReadFile);
    larCustomFunction(context, larGlobalObject, "remove", Remove);
    larCustomFunction(context, larGlobalObject, "write", Write);

    // Release the allocated memory for the 'lar' string.
    JSStringRelease(lar);
}
