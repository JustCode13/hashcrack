#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 7) {
        printf("Error invalid arguments\n");
        return 1;
    }

    for (int i = 0; i < argc; i++) {
        printf("%d: %s\n", i + 1, argv[i]);
    }

    return 0;
}
