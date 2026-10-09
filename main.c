#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char *hash_mode = NULL;
static char *attack_mode = NULL;
static char *target_hash = NULL;
static char *wordlist_filename = NULL;
static char *character_set = NULL;
static char *progress = "Running";

int validate_arguments(char *hash_mode, char *attack_mode);

int main(int argc, char *argv[]) {
    int opt;
    hash_mode = NULL;
    attack_mode = NULL;

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

    if (validate_arguments(hash_mode, attack_mode) != 0) {
        return -1;
    }

    target_hash = argv[optind];

    if (strcmp(attack_mode, "0") == 0) {
        wordlist_filename = argv[optind];
    } else {
        character_set = argv[optind];
    }

    printf("file: %s\n", argv[0]);
    printf("%s\n", hash_mode);
    printf("%s\n", attack_mode);
    printf("hash file: %s\n", target_hash);
    printf("wordlist: %s\n",
           wordlist_filename == NULL ? character_set : wordlist_filename);
    printf("progress: %s\n", progress);

    return 0;
}

int validate_arguments(char *hash_mode, char *attack_mode) {
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
