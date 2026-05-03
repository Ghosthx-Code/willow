#include "src/obj/write.h"
#include "src/obj/io.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* filename = "output.c";
    const char* data = "#include <stdio.h>\n\nint main() { \n printf(\"Hello, World!\\n\"); \n return 0; \n}";

    writeFile(filename, data);
    system("gcc output.c -o output");
    system("rm -rf output.c");
    return 0;
}