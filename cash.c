#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main () {
    float cash;
    do {
        cash = get_float ("Change owed: ");
    } while (cash < 0);

    cash = round (cash * 100);
    int count = 0;

    while (cash > 0) {
        if (cash >= 25) cash -= 25;
        else if (cash >= 10) cash -= 10;
        else if (cash >= 5) cash -= 5;
        else cash -= 1;
        count ++;
    }

    printf ("%i\n ", count);

}
