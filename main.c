#include <stdio.h>
#include <string.h>
#include "src/includes/functions.h"


void Apis(JSContextRef context, JSObjectRef globalObject) {
    createCustomFunction(context, globalObject, "Add", Add);
}

// int main() {
//     JSGlobalContextRef context = JSGlobalContextCreate(NULL);
//     JSObjectRef globalObject = JSContextGetGlobalObject(context);

//     Apis(context, globalObject);


    
//     // functionUno();
//     // int result = functionDos(2, 2);
//     // printf("El resultado de funcionDos es: %d\n", result);
//     return 0;
// }

int main(int argc, char *argv[]) {
    JSGlobalContextRef context = JSGlobalContextCreate(NULL);
    JSObjectRef globalObject = JSContextGetGlobalObject(context);
    Apis(context, globalObject);


    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if(strcmp(argv[i], "run") == 0 && argv[2]){
                // printf("%s", argv[1]);
                interpreter(argv[2], context, globalObject);
            }
        }
    } else {
        printf("No se han proporcionado argumentos.\n");
    }

    JSGlobalContextRelease(context);

    return 0;
}