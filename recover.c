#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf ("Incorrect number of args: %i\n", argc);
        return 1;
    }

    char *file_name = argv[1];
    FILE *input = fopen (file_name, "r");
    if (input == NULL) {
        printf ("Cannot open file\n");
        return 1;
    }
    const int BLOCK_SIZE = 512;
    //unsigned char *block = malloc (BLOCK_SIZE);
    unsigned char block [512];
    int count = 0;
    FILE *output = NULL;
    while (fread (block, BLOCK_SIZE, 1, input) == 1) {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >>4 == 0xe) {
            char file_out [10];
            if (count < 10) {
                sprintf(file_out, "00%i.jpg", count);
            } else {
                sprintf (file_out, "0%i.jpg", count);
            }
            if (count == 0){
                output = fopen (file_out, "a");
            }
            else {
            // jpeg file, close old pointer. Reopen a new one
                fclose (output);
                output = fopen (file_out, "a");
            }
            count ++;
        }

        if (output != NULL) {
            fwrite (block, BLOCK_SIZE, 1, output);
        }

        if (feof (input)) break;
    }

    if (output != NULL) {
        fclose (output);
    }

    /*if (block != NULL) {
        free (block);
    }*/

    return 0;

}
