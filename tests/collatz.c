#include <stdio.h>
#include <cs50.h>

int collatz(int num, int steps[]);

int main(void)
{
    int num = get_int("Enter Collatz Starting Integer: ");
    printf("Steps taken: %i\n", collatz(num));
}

int collatz(int num)
{
    //printf("Cur Num: %i\n", num);
    if (num == 1)
        return 0;
    else if (num % 2 == 0)
        return 1 + collatz(num/2, steps);
    else
        return 1 + collatz(3*num+1, steps);

}