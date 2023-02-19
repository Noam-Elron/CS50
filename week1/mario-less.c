#include <cs50.h>
#include <stdio.h>

int height_inp(void);
void mario(void);

int main(void)
{
    mario();
    return 0;
}



int height_inp(void)
{
    while (true)
    {
        int h = get_int("Enter height of structure, between 1-8: ");

        if (h > 0 && h < 9)
        {
            return h;
        }
        else
        {
            printf("Incorrect value, try again\n");
        }
    }
}


void mario(void)
{
    int height = height_inp();
    for (int cur = 1; cur <= height; cur++)
    {
        for (int space = height - cur; space > 0; space--)
        {
            printf(" ");
        }
        for (int pound = cur; pound > 0; pound--)
        {
            printf("#");
        }
        printf("\n");
    }
    return;
}