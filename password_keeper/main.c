#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define file_name "passwords"

struct keychain {
    char address[50];
    char password[50];
    int password_length;
};

bool addPassword(FILE *file);

void xor(char *string, size_t string_length, char *key) {
    size_t key_length = strlen(key);
    for (size_t i = 0; i < string_length; i++) {
        string[i] = key[i % key_length] ^ string[i];
    }
}

void getMasterKey(char *key) {
    char *pass;
    pass = getpass("Enter master key\n");
    strcpy(key, pass);
}

//print addresses and passwords
void print_all(FILE *file, char query[80]) {
    bool found = false;
    char key[50];
    getMasterKey(key);
    struct keychain keychain;

    printf("Addresses and passwords: \n");
    while (fread(&keychain, sizeof(keychain), 1, file) == 1) {
        if (strcmp(query, "*") == 0 || strstr(keychain.address, query) != NULL) {
            xor(keychain.password, keychain.password_length, key);
            printf("%s: %s\n", keychain.address, keychain.password);
            xor(keychain.password, keychain.password_length, key);
            found = true;
        }
    }

    if (!found) {
        printf("Unfortunately, no passwords are found there\n");
    }
}

void add(FILE *file, struct keychain *keychain) {
    fwrite(keychain, sizeof(*keychain), 1, file);
}

//Funtion selection menu
int main() {
    char query[80];
    FILE *file;
    int num;
    do {
        printf("\nSelect program function:\n1)Enter new password\n2)Search password\n3)Print a report of sites and passwords\n4)Exit the program\n");
        scanf("%d", &num);
        switch (num) {
            case 1:
                file = fopen(file_name, "ab");
                if (file == NULL) {
                    printf("cant find a file %s\n", file_name);
                    return 1;
                }
                addPassword(file);
                fclose(file);
                break;
            case 2:
                file = fopen(file_name, "rb");
                if (file == NULL) {
                    printf("cant find a file\n");
                    return 1;
                }
                printf("Enter a search query\n");
                scanf("%s", query);
                print_all(file, query);
                fclose(file);
                break;
            case 3:
                file = fopen(file_name, "rb");
                if (file == NULL) {
                    printf("cant find a file\n");
                    return 1;
                }
                print_all(file, "*");
                fclose(file);
                break;
            case 4:
                printf("Exit the program\n");
                break;
            default:
                break;
        }
    } while (num > 0 && num < 4);


    return 0;
}

//function to add password
bool addPassword(FILE *file) {
    char key[50];
    getMasterKey(key);

    struct keychain keychain1;
    struct keychain keychain2;
    printf("Enter an address 50 characters MAX\n");
    scanf("%s", keychain1.address);

    //ask user to enter password twice
    char *pass;
    pass = getpass("Enter a password 50 characters MAX\n");
    strcpy(keychain1.password, pass);
    pass = getpass("Enter a password again\n");
    strcpy(keychain2.password, pass);

    //if passwords are typed correctly save them to the file
    if (strcmp(keychain1.password, keychain2.password) == 0) {
        keychain1.password_length = strlen(keychain1.password);
        xor(keychain1.password, keychain1.password_length, key);
        add(file, &keychain1);
        printf("Password was successfully saved\n");
        return true;
    } else {
        printf("Passwords are not same\n");
        return false;
    }
}