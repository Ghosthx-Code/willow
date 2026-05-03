#include "../obj/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// reads line by line and stores in a buffer, resizing as needed

char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    size_t capacity = 1024;
    size_t length = 0;
    char* buffer = (char*)malloc(capacity);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        size_t line_length = strlen(line);
        
        while (length + line_length >= capacity) {
            capacity *= 2;
            char* temp = (char*)realloc(buffer, capacity);
            if (!temp) {
                free(buffer);
                fclose(file);
                return NULL;
            }
            buffer = temp;
        }
        
        strcpy(buffer + length, line);
        length += line_length;
    }

    buffer[length] = '\0';
    fclose(file);
    return buffer;
}