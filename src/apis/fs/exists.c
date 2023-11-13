#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>


bool fileExists(const char* filename) {
    FILE * file = fopen(filename, "r");

    if(file) {
        fclose(file);
        return true;
    }
    return false;
}


JSValueRef Exist(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount < 1) {
        printf("The function requires one argument\n");
        return JSValueMakeUndefined(context);
    }

    JSStringRef filename = JSValueToStringCopy(context, arguments[0], exception);
    size_t buffserSize = JSStringGetMaximumUTF8CStringSize(filename);
    char * fileNameCStr = (char*)malloc(buffserSize);
    JSStringGetUTF8CString(filename, fileNameCStr, buffserSize);

    bool result = fileExists(fileNameCStr);

    free(fileNameCStr);
    JSStringRelease(filename);
    return JSValueMakeBoolean(context, result);
}


// void existsFunction(JSContextRef context, JSObjectRef globalObject) {
//     JSStringRef existsName = JSStringCreateWithUTF8CString("lar");
//     JSObjectRef existsObject = JSObjectMake(context, NULL, NULL);
//     JSObjectSetProperty(context, globalObject, existsName, existsObject, kJSClassAttributeNone, NULL);

//     JSStringRef existsFunction = JSStringCreateWithUTF8CString("exists");
//     JSObjectRef existsFuntionObject = JSObjectMakeFunctionWithCallback(context, existsFunction, Exist);
//     JSObjectSetProperty(context, existsObject, existsFunction, existsFuntionObject, kJSClassAttributeNone, NULL);

//     JSStringRelease(existsName);
//     JSStringRelease(existsFunction);
// }