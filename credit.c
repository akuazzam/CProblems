#include<stdio.h>
#include<cs50.h>

bool checksum (long credit);
int startswith (long credit);
int sumdigits (int digit);
int size (long credit);

int main () {
    long credit = get_long ("Number: ");

    // first check if credit is valid. If not, simply print Invalid
    if (! checksum (credit)) {
        printf ("%s\n", "INVALID");
    }
    //for amex
    else if (startswith(credit) == 34 || startswith(credit) == 37) {
        // check for size
        if (size (credit) == 15) {
            printf ("%s\n", "AMEX");
        }
        else {
            printf ("%s\n", "INVALID");
        }
    }
    // check if digits start between [51 - 55] for mastercard
    else if (startswith(credit) >=51 && startswith(credit) <= 55) {
        if (size(credit) == 16) {
            printf ("%s\n", "MASTERCARD");
        }
        else {
            printf ("%s\n", "INVALID");
        }
    }
    // for visa, check if the reduced number is 4.
    // eg: 49 -> 4
     else if (startswith(credit) / 10 == 4) {
        if (size(credit) == 13 || size (credit) == 16) {
            printf ("%s\n", "VISA");
        }
        else {
            printf ("%s\n", "INVALID");
        }
    }
    // if none of those, report invalid
    else {
        printf ("%s\n", "INVALID");
    }

}

bool checksum (long credit) {
    int parity = 0; //use this to alternate between digits
    int sum = 0;
    while (credit > 0) {
        int digit = credit % 10; //gets the last digit
        if (parity % 2 == 1) {
            digit = digit * 2;
            sum += sumdigits (digit);
        }
        else {
        sum += digit;
        }
        credit = credit / 10; // remove last digit
        parity ++;
    }
    if (sum % 10 == 0) return true;
    else return false;
}

int startswith (long credit) {
    // keep removing lesser digits (dividing by 10) until credit is less than 100 (or is between 0-99)
    // This gets us the first two digits
    while (credit > 100) {
        credit = credit / 10;
    }
    return credit;
}

//gets sum of individual digits
// eg: 145 -> 5 + 4 + 1
int sumdigits (int digit) {
    int sum = 0;
    while (digit > 0) {
        sum += digit % 10;
        digit = digit / 10;
    }
    return sum;
}

int size (long credit) {
    int n = 0;
    while (credit > 0) {
        credit = credit/10;
        n ++;
    }
    return n;
}
