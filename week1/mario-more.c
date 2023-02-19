#include <cs50.h>
#include <stdio.h>


int height_inp();
void mario();

int main(void)
{
    mario();
}


int height_inp()
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

void mario()
{
    int height = height_inp();
    // Height, starts from the top and makes its way down to height of 1
    for (int cur_height = height; cur_height > 0; cur_height--)
    {
        /*Creates the spaces, starts at the top with a space less
          than the height value, each time the current height
          decreases, the amount of spaces gets decreased aswell. */
        for (int dots = cur_height - 1; dots > 0; dots--)
        {
            printf(" ");
        }
        /*Amount of bricks is always equal to 1, but never greater the
        current height -1. Since it starts at the top layer, bricks
        are set to 1, and if the current height is less than max,
        it adds bricks incrementally. */
        for (int brick = 1; brick <= height - cur_height + 1; brick++)
        {
            printf("#");
        }
        //Gap
        printf("  ");

        for (int brick = 1; brick <= height - cur_height + 1; brick++)
        {
            printf("#");
        }
        //Newline for next layer
        printf("\n");

    }

}