#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

char *readFile(char * filename) {
    FILE * file = fopen(filename, "r");

    if(file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char * buffer = malloc(file_size + 1);
    size_t read_size = fread(buffer, 1, file_size, file);
    buffer[read_size] = '\0';

    fclose(file);

    return buffer;
}

JSValueRef ReadFile(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {

    if(argumentCount < 1) {
        printf("The function requires one argument\n");
        return JSValueMakeUndefined(context);
    }

    JSStringRef filename = JSValueToStringCopy(context, arguments[0], exception);
    size_t buffserSize = JSStringGetMaximumUTF8CStringSize(filename);
    char * fileNameCStr = (char*)malloc(buffserSize);
    JSStringGetUTF8CString(filename, fileNameCStr, buffserSize);

    char *fileContent = readFile(fileNameCStr);
    free(fileNameCStr);

    if(!fileContent) {
        char * message = "The file does not exists";
        JSStringRef resultContent = JSStringCreateWithUTF8CString(message); 
        JSValueRef err = JSValueMakeString(context, resultContent);
        // printf("The file does not exists\n");
        // return JSValueMakeUndefined(context);
        return err;
    }

    JSStringRef resultContent = JSStringCreateWithUTF8CString(fileContent); 
    free(fileContent);


    JSValueRef  resultValue = JSValueMakeString(context, resultContent);
    JSStringRelease(resultContent);

    JSStringRelease(filename);

    return resultValue;
}

// void readFileFunction(JSContextRef context, JSObjectRef globalObject) {
//     JSStringRef readFileName = JSStringCreateWithUTF8CString("lar");
//     JSObjectRef readFIleObject = JSObjectMake(context, NULL, NULL);
//     JSObjectSetProperty(context, globalObject, readFileName, readFIleObject, kJSClassAttributeNone, NULL);

//     JSStringRef readFileFunction = JSStringCreateWithUTF8CString("readFile");
//     JSObjectRef readFileFuntionObject = JSObjectMakeFunctionWithCallback(context, readFileFunction, ReadFile);
//     JSObjectSetProperty(context, readFIleObject, readFileFunction, readFileFuntionObject, kJSClassAttributeNone, NULL);

//     JSStringRelease(readFileName);
//     JSStringRelease(readFileFunction);
// }
