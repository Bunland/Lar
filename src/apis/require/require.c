#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>
#include "../../includes/functions.h"

JSValueRef Require(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount <1) {
        return JSValueMakeUndefined(context);
    }

    JSStringRef moduleName = JSValueToStringCopy(context, arguments[0], exception);
    size_t bufferSize = JSStringGetMaximumUTF8CStringSize(moduleName);
    char * moduleNameCStr = (char*)malloc(bufferSize);
    JSStringGetUTF8CString(moduleName, moduleNameCStr, bufferSize);

    char * fileContent = readScript(moduleNameCStr);

    if(fileContent != NULL) {
        JSStringRef exportName = JSStringCreateWithUTF8CString("exports");
        JSObjectRef exportObject = JSObjectMake(context, NULL, NULL);
        JSObjectSetProperty(context, JSContextGetGlobalObject(context), exportName, exportObject, kJSClassAttributeNone, NULL);

        JSStringRef script = JSStringCreateWithUTF8CString(fileContent);
        JSEvaluateScript(context, script, NULL, NULL, 0, exception);

        JSStringRelease(script);
        free(fileContent);

        JSValueRef exportValue = JSObjectGetProperty(context, JSContextGetGlobalObject(context), exportName, NULL);
        JSStringRelease(exportName);

        return exportValue;
    }

    return JSValueMakeUndefined(context);
}

void requireFunction(JSContextRef context, JSObjectRef globalObject) { 
    JSStringRef requireName = JSStringCreateWithUTF8CString("require");
    JSObjectRef requireFunctionName = JSObjectMakeFunctionWithCallback(context,  requireName, Require);
    JSObjectSetProperty(context, globalObject, requireName, requireFunctionName, kJSClassAttributeNone, NULL);
    JSStringRelease(requireName);
}