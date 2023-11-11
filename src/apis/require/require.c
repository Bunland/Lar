#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>
#include "../../includes/functions.h"

JSValueRef Require(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    if(argumentCount < 1) {
        return JSValueMakeUndefined(context);
    }

    JSStringRef moduleName = JSValueToStringCopy(context, arguments[0], exception);
    size_t bufferSize = JSStringGetMaximumUTF8CStringSize(moduleName);
    char* moduleNameCStr = (char*)malloc(bufferSize);
    JSStringGetUTF8CString(moduleName, moduleNameCStr, bufferSize);

    char * fileContent = readScript(moduleNameCStr);

    if(fileContent != NULL) {
        // JSStringRef script  = JSStringCreateWithUTF8CString(fileContent);
        // JSValueRef result = JSEvaluateScript(context, script, NULL, NULL, 0, exception);


        // // Crear un objeto global "module" si no existe
        JSStringRef exportsName  = JSStringCreateWithUTF8CString("exports");
        JSObjectRef exportsObject = JSObjectMake(context, NULL, NULL);
        JSObjectSetProperty(context, JSContextGetGlobalObject(context), exportsName, exportsObject, kJSPropertyAttributeNone, NULL);

        // Ejecutar el script
        JSStringRef script = JSStringCreateWithUTF8CString(fileContent);
        JSEvaluateScript(context, script, NULL, NULL, 0, exception);

        JSStringRelease(script);
        free(fileContent);

        // Obtener el valor de exports después de ejecutar el script
        JSValueRef exportsValue = JSObjectGetProperty(context, JSContextGetGlobalObject(context), exportsName, NULL);

        // Devolver el objeto exports directamente
        return exportsValue;
    } 
    return JSValueMakeUndefined(context);
}



void requireFunction(JSContextRef context, JSObjectRef globalObject) { 
    JSStringRef requireName = JSStringCreateWithUTF8CString("require");
    JSObjectRef requireFunctionObject = JSObjectMakeFunctionWithCallback(context, requireName, Require);
    JSObjectSetProperty(context, globalObject,  requireName, requireFunctionObject, kJSPropertyAttributeNone, NULL);
}