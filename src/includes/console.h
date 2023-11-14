#include <JavaScriptCore/JavaScript.h>
#ifndef CONSOLE_H
#define CONSOLE_H

JSValueRef Log(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception);
void consoleApis(JSContextRef context, JSObjectRef globalObject);

#endif
