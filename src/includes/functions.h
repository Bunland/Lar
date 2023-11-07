#include <JavaScriptCore/JavaScript.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void interpreter (char * filename, JSContextRef context, JSObjectRef globalObject);
void createCustomFunction(JSContextRef context, JSObjectRef globalObject, const char * functionName, JSObjectCallAsFunctionCallback functionCallback);
JSValueRef Add(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* execption);
JSValueRef Mult(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* execption);


#endif