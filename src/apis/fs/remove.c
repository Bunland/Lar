#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

bool removeFile(char * filename) {
    return remove(filename) == 0;
}

JSValueRef Remove(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount < 1) {
        printf("The function requires one argument\n");
        return JSValueMakeUndefined(context);
    }

    JSStringRef filename = JSValueToStringCopy(context, arguments[0], exception);
    size_t buffserSize = JSStringGetMaximumUTF8CStringSize(filename);
    char * fileNameCStr = (char*)malloc(buffserSize);
    JSStringGetUTF8CString(filename, fileNameCStr, buffserSize);

    bool result = removeFile(fileNameCStr);
    free(fileNameCStr);
    
    JSStringRelease(filename);
    return JSValueMakeBoolean(context, result);
}