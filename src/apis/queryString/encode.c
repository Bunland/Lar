#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <JavaScriptCore/JavaScript.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

void removeSpaces(char *str) {
   int i, j = 0;
   for(i = 0; str[i] != '\0'; i++) {
       str[i] = str[i + j];
       if(str[i] == ' ' || str[i] == '\t') {
           j++;
           i--;
       }
   }
}

char *encode(char * jsonString) {
   removeSpaces(jsonString);
   char * result = strdup("");
   char * token = strtok(jsonString, ":,\"{}");

   while (token != NULL) {
       KeyValue kv;
       kv.key = strdup(token);

       token = strtok(NULL, ":,\"{}");

       if(token != NULL) {
            kv.value = strdup(token);

            char * keyValueStr = malloc(strlen(kv.key) + strlen(kv.value) + 3);

                if (keyValueStr == NULL) {
                    perror("Error allocating memory");
                    exit(EXIT_FAILURE);
                }

            sprintf(keyValueStr, "%s=%s&", kv.key, kv.value);
            result = realloc(result, strlen(result) + strlen(keyValueStr) + 1);
            if (result == NULL) {
                free(kv.value);
                free(keyValueStr);
                perror("Error reallocating memory for result");
                exit(EXIT_FAILURE);
            }

            strcat(result, keyValueStr);
            free(kv.value);
            free(keyValueStr);


        // kv.value = strdup(token);

        // char *keyValueStr = malloc(strlen(kv.key) + strlen(kv.value) + 2);  // Cambiado +3 a +2
        // strcpy(keyValueStr, kv.key);
        // strcat(keyValueStr, "=");
        // strcat(keyValueStr, kv.value);
        // strcat(keyValueStr, "&");

        // result = realloc(result, strlen(result) + strlen(keyValueStr) + 1);
        // strcat(result, keyValueStr);

        // free(kv.value);
        // free(keyValueStr);

       }

       free(kv.key);
       token = strtok(NULL, ":,\"{}");
   }

   if (strlen(result) > 0) {
       result[strlen(result) - 1] = '\0';
   }

   return result;
}

// typedef struct {
//     char *key;
//     char *value;
// } KeyValue;

// typedef struct Node {
//     char *data;
//     struct Node *next;
// } Node;

// void removeSpaces(char *str) {
//     int i, j = 0;
//     for (i = 0; str[i] != '\0'; i++) {
//         str[i] = str[i + j];
//         if (str[i] == ' ' || str[i] == '\t') {
//             j++;
//             i--;
//         }
//     }
// }

// void appendNode(Node **head, char *data) {
//     Node *newNode = (Node *)malloc(sizeof(Node));
//     if (newNode == NULL) {
//         // Manejo de error: No se pudo asignar memoria
//         exit(EXIT_FAILURE);
//     }

//     newNode->data = data;
//     newNode->next = NULL;

//     if (*head == NULL) {
//         *head = newNode;
//     } else {
//         Node *current = *head;
//         while (current->next != NULL) {
//             current = current->next;
//         }
//         current->next = newNode;
//     }
// }

// void freeNodeList(Node *head) {
//     while (head != NULL) {
//         Node *temp = head;
//         head = head->next;
//         free(temp->data);
//         free(temp);
//     }
// }

// char *encode(char *jsonString) {
//     removeSpaces(jsonString);

//     Node *subStrings = NULL;

//     char *token = strtok(jsonString, ":,\"{}");
//     while (token != NULL) {
//         KeyValue kv;
//         kv.key = strdup(token);

//         token = strtok(NULL, ":,\"{}");

//         if (token != NULL) {
//             kv.value = strdup(token);

//             char *keyValueStr = (char *)malloc(strlen(kv.key) + strlen(kv.value) + 3);
//             if (keyValueStr == NULL) {
//                 // Manejo de error: No se pudo asignar memoria
//                 freeNodeList(subStrings);
//                 exit(EXIT_FAILURE);
//             }

//             snprintf(keyValueStr, strlen(kv.key) + strlen(kv.value) + 3, "%s=%s&", kv.key, kv.value);
//             appendNode(&subStrings, keyValueStr);

//             free(kv.value);
//         }

//         free(kv.key);
//         token = strtok(NULL, ":,\"{}");
//     }

//     size_t totalLength = 0;
//     Node *current = subStrings;
//     while (current != NULL) {
//         totalLength += strlen(current->data);
//         current = current->next;
//     }

//     char *result = (char *)malloc(totalLength + 1);
//     if (result == NULL) {
//         // Manejo de error: No se pudo asignar memoria
//         freeNodeList(subStrings);
//         exit(EXIT_FAILURE);
//     }

//     result[0] = '\0'; // Inicializar la cadena vacía

//     current = subStrings;
//     while (current != NULL) {
//         strcat(result, current->data);
//         Node *temp = current;
//         current = current->next;
//         free(temp->data);
//         free(temp);
//     }

//    if (strlen(result) > 0) {
//        result[strlen(result) - 1] = '\0';
//    }


//     return result;
// }

JSValueRef Encode(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef * exception) {
    if (argumentCount < 1) {
        printf("The function requires one argument\n");
        return JSValueMakeUndefined(context);
    }

    JSStringRef resultStr = JSValueCreateJSONString(context, arguments[0], 0, NULL);
    size_t bufferSizes = JSStringGetMaximumUTF8CStringSize(resultStr);
    char * buffer = (char*)malloc(bufferSizes);

    if (buffer == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    JSStringGetUTF8CString(resultStr, buffer, bufferSizes);
    JSStringRelease(resultStr);

    char* encodeStr = encode(buffer);
    free(buffer);

    JSStringRef resultContent = JSStringCreateWithUTF8CString(encodeStr);
    free(encodeStr);

    JSValueRef resultValue = JSValueMakeString(context, resultContent);
    JSStringRelease(resultContent);

    return resultValue;
}