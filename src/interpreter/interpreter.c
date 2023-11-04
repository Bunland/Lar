#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>


// function to create a custom Javascript function
void createCustomFunction(JSContextRef context, JSObjectRef globalObject, const char * functionName, JSObjectCallAsFunctionCallback funcionCallback) {
    JSStringRef functionString = JSStringCreateWithUTF8CString(functionName);

    JSObjectRef functionObject = JSObjectMakeFunctionWithCallback(context, functionString, funcionCallback);

    JSObjectSetProperty(context ,globalObject, functionString, functionObject, kJSPropertyAttributeNone, NULL);

    // Free string
    JSStringRelease(functionString);
}

 // callback function for adding two numbers in javascript
JSValueRef Add(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* execption) {
    if(argumentCount < 2 || arguments == NULL) {
        fprintf(stderr, "The function requires 2 arguments.\n");
        return JSValueMakeUndefined(context);
    }

    int numa = JSValueToNumber(context, arguments[0], NULL);
    int numb = JSValueToNumber(context, arguments[1], NULL);

    int add = numa + numb;
    printf("%d\n", add);

    return JSValueMakeNumber(context, add);
}

JSValueRef Mult(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* execption) {
    if(argumentCount < 2 || arguments == NULL) {
        fprintf(stderr, "The function requires 2 arguments.\n");
        return JSValueMakeUndefined(context);
    }

    int numa = JSValueToNumber(context, arguments[0], NULL);
    int numb = JSValueToNumber(context, arguments[1], NULL);

    int mult = numa * numb;
    printf("%d\n", mult);

    return JSValueMakeNumber(context, mult);
}


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

int main () {
    JSGlobalContextRef context = JSGlobalContextCreate(NULL);
    JSObjectRef globalObject = JSContextGetGlobalObject(context);

    const char* filename = "index.js";
    char * fileContent = readScript(filename);

    if(fileContent == NULL) {
        return 1;
    }

    // create and register custom javascript function
    createCustomFunction(context, globalObject, "Add", Add);
    createCustomFunction(context, globalObject, "Mult", Mult);

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
    JSGlobalContextRelease(context);
    return 0;
}