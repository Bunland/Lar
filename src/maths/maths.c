#include <stdio.h>
#include <stdlib.h>
#include <JavaScriptCore/JavaScript.h>

JSValueRef Add(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    if(argumentCount < 2 || arguments == NULL) {
        fprintf(stderr, "The function requires 2 arguments.\n");
        return JSValueMakeUndefined(context);
    }

    int numa = JSValueToNumber(context, arguments[0], NULL);
    int numb = JSValueToNumber(context, arguments[1], NULL);

    int add = numa + numb;
    // printf("%d\n", add);

    return JSValueMakeNumber(context, add);
}

JSValueRef Mult(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    if(argumentCount < 2 || arguments == NULL) {
        fprintf(stderr, "The function requires 2 arguments.\n");
        return JSValueMakeUndefined(context);
    }

    int numa = JSValueToNumber(context, arguments[0], NULL);
    int numb = JSValueToNumber(context, arguments[1], NULL);

    int add = numa + numb;
    // printf("%d\n", add);

    return JSValueMakeNumber(context, add);
}