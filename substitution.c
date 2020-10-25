#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>

bool validinput (string input);
void encrypt (string plaintext, string key);

int main (int argc, string argv []) {
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (! validinput (argv[1])) {
        printf("Invalid key\n");
        return 1;
    }

    string plaintext = get_string ("plaintext: ");
    printf ("ciphertext: ");
    encrypt (plaintext, argv[1]);

    return 0;
}

bool validinput (string input) {
    int n = strlen (input);
    if (n != 26) return false;
    int uniqueset [26] = {0};
    for (int i = 0; i < n; i ++) {
        if (! isalpha (input[i])) return false;
        int idx = toupper(input[i]) - 65;
        if (uniqueset[idx] > 0) return false;
        uniqueset[idx] ++;
    }
    return true;
}

void encrypt (string text, string key) {
    for (int i = 0, n = strlen(text); i < n; i ++) {
        if (! isalpha(text[i])) {
            printf ("%c", text[i]);
            continue;
        }
        int c = toupper(text [i]) - 65;
        char encrypted = key [c];
        if (isupper(text[i])) printf ("%c", toupper(encrypted));
        else printf ("%c", tolower (encrypted));
    }
    printf("\n");
}
