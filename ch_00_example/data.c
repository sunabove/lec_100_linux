#include <stdio.h>
#include <locale.h>
int main(int argc, char **argv) {
    setlocale(LC_NUMERIC, "");

    char c = 'A';
    char * s = "ABCD" ;
    int i = 1234 ;
    double d = 1234.5678 ; 

    printf("%c\n", c);
    printf("%s\n", s);
    printf("%'d\n", i);
    printf("%'.2f\n", d);

    return 0;
}

