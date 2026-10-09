#include <ctype.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *hash_mode = NULL;
static char *attack_mode = NULL;
static char *hash_file = NULL;
static char target_hash[41];
static char *wordlist_filename = NULL;
static char *character_set = NULL;
static char *progress = "Running";

int validate_arguments(char *hash_mode, char *attack_mode);

int open_file(char *file_name);

int read_file(int file_fd, char *output, size_t output_size);

int validate_hash(void);

int main(int argc, char *argv[]) {
    int opt;

    hash_mode = NULL;
    attack_mode = NULL;

    int hash_file_fd = 0;
    int dict_file_fd = 0;

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

    hash_file = argv[optind];

    if (strcmp(attack_mode, "0") == 0) {
        wordlist_filename = argv[optind];
    } else {
        character_set = argv[optind];
    }

    printf("file: %s\n", argv[0]);
    printf("%s\n", hash_mode);
    printf("%s\n", attack_mode);
    printf("hash file: %s\n", hash_file);
    printf("wordlist: %s\n",
           wordlist_filename == NULL ? character_set : wordlist_filename);
    printf("progress: %s\n", progress);

    if ((hash_file_fd = open_file(hash_file)) == -1) {
        return -1;
    }

    printf("file fd: %d\n", hash_file_fd);

    if ((dict_file_fd =
             open_file(wordlist_filename == NULL ? character_set
                                                 : wordlist_filename)) == -1) {
        return -1;
    }

    printf("wordlist fd: %d\n", dict_file_fd);

    if (read_file(hash_file_fd, target_hash, sizeof(target_hash)) == -1) {
        return -1;
    }

    if (validate_hash() != 0) {
        return -1;
    }

    printf("target hash: %s", target_hash);

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

int open_file(char *file_name) {
    int fd = open(file_name, O_RDONLY);

    if (fd == -1) {
        perror("Open");
        return -1;
    }

    return fd;
}

int read_file(int file_fd, char *output, size_t output_size) {
    int bytes_read = read(file_fd, output, output_size);

    for (int i = 0; i < bytes_read; i++) {

        if (output[i] == '\n') {
            output[i] = '\0';
        }
    }

    if (bytes_read < 1) {
        perror("read");
        return -1;
    }

    return 0;
}

int validate_hash(void) {

    if (strcmp(hash_mode, "0")) {
        if (sizeof(target_hash) != 33) {
            printf("Error: Invalid Hash %s\n", target_hash);
            return -1;
        }

    } else {
        if (sizeof(target_hash) != 41) {
            printf("Error: Invalid Hash %s\n", target_hash);
            return -1;
        }
    }

    for (size_t i = 0; i < sizeof(target_hash); i++) {
        if (!isxdigit(target_hash[i]) && target_hash[i] != '\0') {
            printf("Error: Invalid Hash %c\n", target_hash[i]);
            return -1;
        }
    }

    return 0;
}
