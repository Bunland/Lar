#include <JavaScriptCore/JavaScript.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char* readScript(const char * filename);
void interpreter (char * filename, JSContextRef context, JSObjectRef globalObject);
void createCustomFunction(JSContextRef context, JSObjectRef globalObject, const char * functionName, JSObjectCallAsFunctionCallback functionCallback);
void consoleLogFunction(JSContextRef context, JSObjectRef globaObject);


void requireFunction(JSContextRef context, JSObjectRef globalObject);

JSValueRef Add(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
JSValueRef Mult(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);

#endif