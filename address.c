#include <stdio.h>

int main(void)
{
    //int n = 50;
    //int *p = &n;
    //printf("%p\n", p);
    //printf("%i\n", *p);


    //char *s = "HI!";
    //printf("%s\n",s);

    char *s = "HI!";
    printf("%c\n",*s);
    printf("%c\n",*(s + 1));
    printf("%c\n",*(s + 2));

    int numbers[] = {4, 6, 8, 2, 7, 5, 0};

    printf("%i\n", *numbers);
    printf("%i\n", *(numbers + 1));
    printf("%i\n", *(numbers + 2));
    printf("%i\n", *(numbers + 3));
    printf("%i\n", *(numbers + 4));
    printf("%i\n", *(numbers + 5));
    printf("%i\n", *(numbers + 6));


}