#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

char * readScript(const char * filename) {
    FILE * file = fopen(filename, "r");

    if(file == NULL) {
        printf("Filed to open file\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size_file = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(size_file + 1);
    fread(buffer, 1, size_file, file);
    fclose(file);
    buffer[size_file] = '\0';
    return buffer;
}

void interpreter (char * filename, JSContextRef context, JSObjectRef globalObject) {

    char * fileContent = readScript(filename);

    JSStringRef jsCode = JSStringCreateWithUTF8CString(fileContent);
    JSValueRef result = JSEvaluateScript(context, jsCode, NULL, NULL, 0, NULL);

    JSStringRef jsString = JSValueToStringCopy(context, result, NULL);

    size_t bufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
    char * str = (char *)malloc(bufferSize);
    JSStringGetUTF8CString(jsString, str, bufferSize);

    printf("%s\n", str);

    free(str);
    free(fileContent);
    JSStringRelease(jsString);
}