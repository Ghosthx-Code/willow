#include "src/obj/write.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* filename = "output.txt";
    const char* data = "Hello, World!\nThis is a test of the writeFile function.";

    writeFile(filename, data);
}