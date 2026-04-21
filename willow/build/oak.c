#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper to safely format and run shell commands
void run_cmd(const char* format, const char* arg1, const char* arg2) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), format, arg1, arg2);
    system(cmd);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <command> <dir_name> [lib_name]\n", argv[0]);
        return 1;
    }

    const char* dir = argv[2];

    if (strcmp(argv[1], "--build-new") == 0) {
        run_cmd("mkdir -p \"%s/src/include\"", dir, NULL);
        run_cmd("mkdir -p \"%s/willow/\"", dir, NULL);
        
        run_cmd("cp -r ~/willow/src/* \"%s/src/\"", dir, NULL);
        run_cmd("cp ~/willow/Makefile \"%s/Makefile\"", dir, NULL);
        run_cmd("cp -r ~/willow/src/include/* \"%s/src/include/\"", dir, NULL);
        run_cmd("cp -r ~/willow/willow/* \"%s/willow/\"", dir, NULL);
    }

    else if (strcmp(argv[1], "--build-new-lib") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Error: Missing library name.\n");
            return 1;
        }
        const char* lib = argv[3];

        // 1. Create specific subfolders for math and py
        run_cmd("mkdir -p \"%s/libarys/math\"", dir, NULL);
        run_cmd("mkdir -p \"%s/libarys/py\"", dir, NULL);
        
        // 2. Copy contents into those specific folders
        run_cmd("cp -r ~/willow/libarys/math/* \"%s/libarys/math/\"", dir, NULL);
        run_cmd("cp -r ~/willow/libarys/py/* \"%s/libarys/py/\"", dir, NULL);
        
        // 3. Setup the new custom library folder requested by the user
        char lib_path[512];
        snprintf(lib_path, sizeof(lib_path), "%s/libarys/%s", dir, lib);
        run_cmd("mkdir -p \"%s\"", lib_path, NULL);
        
        char toml_dest[512];
        snprintf(toml_dest, sizeof(toml_dest), "%s/%s.toml", lib_path, lib);
        run_cmd("cp ~/willow/lirbarys/folder/libary.toml \"%s\"", toml_dest, NULL);
    }

    return 0;
}
