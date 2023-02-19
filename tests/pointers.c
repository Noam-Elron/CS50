#include <stdio.h>

int main(void)
{
    char *s = "Hello";
    char **p = &s;

    printf("Address of first char of string: %p\n", s);
    printf("Address of s: %p\n", &s);
    printf("Address of p: %p\n", &p);
    printf("Address stored in p should be address of s: %p\n", p);


    printf("Value stored in pointer: %c\n", *s);
    printf("Value stored in pointer pointing to pointer: %c\n", **p);




    //printf("Value: %s\n", s);
    //printf("Value: %s\n", *p);
}
