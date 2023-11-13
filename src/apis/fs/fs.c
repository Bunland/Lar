#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

void fsFunction(JSContextRef context, JSObjectRef globalObject) {
    JSStringRef fsName = JSStringCreateWithUTF8CString("lar");
    JSObjectRef fsGlobalObject = JSObjectMake(context, NULL, NULL);
    JSObjectSetProperty(context, globalObject, fsName, fsGlobalObject, kJSClassAttributeNone, NULL);

    JSStringRef existsFunction = JSStringCreateWithUTF8CString("exists");
    JSObjectRef existsFuntionObject = JSObjectMakeFunctionWithCallback(context, existsFunction, Exist);
    JSObjectSetProperty(context, fsGlobalObject, existsFunction, existsFuntionObject, kJSClassAttributeNone, NULL);

    JSStringRef readFileFunction = JSStringCreateWithUTF8CString("readFile");
    JSObjectRef readFileFuntionObject = JSObjectMakeFunctionWithCallback(context, readFileFunction, ReadFile);
    JSObjectSetProperty(context, fsGlobalObject, readFileFunction, readFileFuntionObject, kJSClassAttributeNone, NULL);

    JSStringRef removeFileFunction = JSStringCreateWithUTF8CString("remove");
    JSObjectRef removeFileFuntionObject = JSObjectMakeFunctionWithCallback(context, removeFileFunction, Remove);
    JSObjectSetProperty(context, fsGlobalObject, removeFileFunction, removeFileFuntionObject, kJSClassAttributeNone, NULL);

    JSStringRef writeFileFunction = JSStringCreateWithUTF8CString("write");
    JSObjectRef writeFileFuntionObject = JSObjectMakeFunctionWithCallback(context, writeFileFunction, Write);
    JSObjectSetProperty(context, fsGlobalObject, writeFileFunction, writeFileFuntionObject, kJSClassAttributeNone, NULL);

    JSStringRelease(fsName);
    JSStringRelease(existsFunction);
    JSStringRelease(readFileFunction);
    JSStringRelease(removeFileFunction);   
    JSStringRelease(writeFileFunction);   
}