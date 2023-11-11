#include <stdio.h>
#include <stdlib.h>
#include "../includes/functions.h"
#include <JavaScriptCore/JavaScript.h>

// char * readScript(const char * filename) {
//     FILE * file = fopen(filename, "r");

//     if(file == NULL) {
//         printf("Filed to open file\n");
//         return NULL;
//     }

//     fseek(file, 0, SEEK_END);
//     long size_file = ftell(file);
//     fseek(file, 0, SEEK_SET);
//     char* buffer = (char*)malloc(size_file + 1);
//     fread(buffer, 1, size_file, file);
//     fclose(file);
//     buffer[size_file] = '\0';
//     return buffer;
// }

void interpreter (char * filename, JSContextRef context, JSObjectRef globalObject) {

    char * fileContent = readScript(filename);

    JSStringRef jsCode = JSStringCreateWithUTF8CString(fileContent);
    JSValueRef exception = NULL;
    JSValueRef result = JSEvaluateScript(context, jsCode, NULL, NULL, 0, &exception);

    if (exception) {
        // Obtener el tamaño del buffer necesario
        size_t bufferSize = JSStringGetMaximumUTF8CStringSize(JSValueToStringCopy(context, exception, NULL));
        char buffer[bufferSize];
        
        // Obtener la cadena UTF-8
        JSStringGetUTF8CString(JSValueToStringCopy(context, exception, NULL), buffer, bufferSize);
        
        // Imprimir el error
        printf("Error en la ejecución del script: %s\n", buffer);
    }


    JSStringRef jsString = JSValueToStringCopy(context, result, NULL);

    size_t bufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
    char * str = (char *)malloc(bufferSize);
    JSStringGetUTF8CString(jsString, str, bufferSize);

    // printf("%s\n", str);

    free(str);
    free(fileContent);
    JSStringRelease(jsString);
}