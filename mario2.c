#include<stdio.h>
#include<cs50.h>

int main () {
    int h = get_int ("Enter height: ");

    for (int i = 0; i < h; i ++) {
        for (int j = 0; j < h - i - 1; j ++) {
            printf (" ");
        }
        for (int k = 0; k < i + 1; k ++) {
            printf ("#");
        }

        printf (" ");

        for (int r = 0; r < i + 1; r ++) {
            printf ("#");
        }

        printf ("\n");
    }

}
