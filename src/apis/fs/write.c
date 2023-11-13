#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

bool write(char * filename, char * content) {
    FILE *file = fopen(filename, "w");

    if(file == NULL) {
        return false;
    }

    if(content != NULL && content[0] != '\0') {
        fprintf(file, "%s", content);
    }

    fclose(file);
    return true;
}

JSValueRef Write(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if(argumentCount < 2) {
        printf("The function requires two argument\n");
        return JSValueMakeUndefined(context);
    }

    JSStringRef filename = JSValueToStringCopy(context, arguments[0], exception);
    size_t buffserSize = JSStringGetMaximumUTF8CStringSize(filename);
    char * fileNameCStr = (char*)malloc(buffserSize);
    JSStringGetUTF8CString(filename, fileNameCStr, buffserSize);

    JSStringRef filecontent = JSValueToStringCopy(context, arguments[1], exception);
    size_t buffserContentSize = JSStringGetMaximumUTF8CStringSize(filecontent);
    char * fileContentCStr = (char*)malloc(buffserContentSize);
    JSStringGetUTF8CString(filecontent, fileContentCStr, buffserContentSize);

    bool result = write(fileNameCStr, fileContentCStr);

    free(fileNameCStr);
    JSStringRelease(filename);
    return JSValueMakeBoolean(context, result);
}
