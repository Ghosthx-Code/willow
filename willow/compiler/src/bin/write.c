#include "../obj/write.h"
#include "../obj/io.h"        
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* writeFile(const char* filename, const char* data) {
    if (!data) {
        return NULL;
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        return NULL;
    }

    size_t data_length = strlen(data);
    size_t written = fwrite(data, sizeof(char), data_length, file);
    fclose(file);

    if (written != data_length) {
        return NULL;
    }

    return (char*)data;
}