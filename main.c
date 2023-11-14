#include <stdio.h>
#include <string.h>
#include "src/includes/lar.h"
#include "src/includes/console.h"
#include "src/includes/functions.h"
#include <JavaScriptCore/JavaScript.h>

/*
 * Exposes custom functions and APIs to the JavaScript context.
 *
 * @param context           The JavaScript context.
 * @param globalObject      The global object to which the functions and APIs will be attached.
 *
 * @return                  There is no explicit return value.
 */
void Apis(JSContextRef context, JSObjectRef globalObject) {
    // Expose custom functions 'Add' and 'Mult'.
    createCustomFunction(context, globalObject, "Add", Add);
    createCustomFunction(context, globalObject, "Mult", Mult);

    // Expose the 'require' function and console APIs to the global object.
    requireFunction(context, globalObject);
    consoleApis(context, globalObject);

    // Expose file system APIs under the 'lar' namespace.
    larApis(context, globalObject);
}

/*
 * Main function for the JavaScript interpreter.
 *
 * @param argc              The number of command line arguments.
 * @param argv              An array of command line arguments.
 *
 * @return                  Returns 0 on successful execution.
 */
int main(int argc, char *argv[]) {
    // Create a global JavaScript context.
    JSGlobalContextRef context = JSGlobalContextCreate(NULL);

    // Get the global object for the JavaScript context.
    JSObjectRef globalObject = JSContextGetGlobalObject(context);

    // Expose custom functions and APIs to the JavaScript context.
    Apis(context, globalObject);

    // Check if there are command line arguments.
    if (argc > 1) {
        // Iterate through the arguments.
        for (int i = 1; i < argc; i++) {
            // Check if the argument is "run" and if the next argument is provided.
            if (strcmp(argv[i], "run") == 0 && argv[i + 1]) {
                // Interpret the JavaScript code from the specified file.
                interpreter(argv[i + 1], context, globalObject);
            }
        }
    } else {
        // Print a message if no arguments are provided.
        printf("No arguments provided.\n");
    }

    // Release the global JavaScript context.
    JSGlobalContextRelease(context);

    return 0;
}
