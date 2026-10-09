#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char *hash_mode = NULL;
static char *attack_mode = NULL;
static char *target_hash = NULL;
static char *wordlist_filename = NULL;
static char *character_set = NULL;
static char *progress = NULL;

int validate_argument(char *hash_mode, char *attack_mode);

int main(int argc, char *argv[]) {
    int opt;
    char *hash_mode = NULL;
    char *attack_mode = NULL;

    while ((opt = getopt(argc, argv, "m:a:")) != -1) {
        switch (opt) {
        case 'm':
            hash_mode = optarg;
            break;

        case 'a':
            attack_mode = optarg;
            break;

        default:
            printf("Invalid Option: %s\n", optarg);
            return 0;
        }
    }

    if (hash_mode == NULL && attack_mode == NULL) {
        printf("Error: Invalid Options\n");
        return -1;
    }

    printf("file: %s\n", argv[0]);
    printf("%s\n", hash_mode);
    printf("%s\n", attack_mode);
    printf("hash file: %s\n", argv[optind]);
    printf("wordlist: %s\n", argv[optind + 1]);

    if (validate_argument(hash_mode, attack_mode) != 0) {
        return -1;
    }

    return 0;
}

int validate_argument(char *hash_mode, char *attack_mode) {
    if (strcmp(hash_mode, "0") != 0 && strcmp(hash_mode, "100") != 0) {
        printf("Error: Invalid Hash Mode: %s\n", hash_mode);
        return -1;
    }

    if (strcmp(attack_mode, "0") != 0 && strcmp(attack_mode, "3") != 0) {
        printf("Error: Invalid Attack Option: %s\n", attack_mode);
        return -1;
    }

    return 0;
}
