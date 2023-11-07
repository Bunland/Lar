#include <stdio.h>
#include <string.h>
#include "src/includes/functions.h"


void Apis(JSContextRef context, JSObjectRef globalObject) {
    createCustomFunction(context, globalObject, "Add", Add);
    createCustomFunction(context, globalObject, "Mult", Mult);
}

int main(int argc, char *argv[]) {
    JSGlobalContextRef context = JSGlobalContextCreate(NULL);
    JSObjectRef globalObject = JSContextGetGlobalObject(context);
    Apis(context, globalObject);


    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if(strcmp(argv[i], "run") == 0 && argv[2]){
                interpreter(argv[2], context, globalObject);
            }
        }
    } else {
        printf("No arguments provided.\n");
    }

    JSGlobalContextRelease(context);

    return 0;
}