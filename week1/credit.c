#include <cs50.h>
#include <stdio.h>

int dig_count(long num);
int checksum(int arr[], int dig);
const char* comp(long num, int dig);
//int* dig_arr(long num, int dig);

int* dig_arr(long num, int dig)
{
    int arr[dig-1];

    //Starting at the last index of array all_digits which is all_digits[digits-1]
    for (int i = dig-1; i >= 0; i--)
    {
        //As long as copy is greater than 9, there are digits after it
        if (num > 9)
        {
            // Adds last digit to array
            arr[i] = num % 10;
            //Removed last digit
            num = num / 10;
        }
        // If copy is less than 10 only 1 digit remains, which will also be when i==0. Simply adds first digit of copy to index[i] (i==0) of array.
        else
        {
            arr[i] = num;
        }
    }
    int* all_dig = arr;
    return all_dig;
}

int main(void)
{
    long credit_card = get_long("Enter credit card number: ");
    // useful to have copy of variable credit_card in order to be able to manipulate it multiple times and re-use credit_card digits
    long copy = credit_card;
    int digits = dig_count(credit_card);
    const char* company = comp(credit_card, digits);

    //Using the amount of digits in the number to create an appropriately sized array with n indexes (n=digits).
    int* all_digits;
    all_digits = dig_arr(credit_card, digits);
    int sum = checksum(all_digits, digits);

    //printf("Sum: %i\n", countsum);
    if (sum % 10 != 0)
    {
        company = "INVALID";
    }
    printf("%s\n", company);
}



int dig_count(long num)
{
    int dig = 0;
    while (num != 0) //Countinues the loop so long as copy isnt equal to 0. So if copy was down to last digit, like 8, because 8/10 rounded down is 0 the loop ends.
    {
            num = num / 10; //removing last digit every iteration
            dig = dig + 1; //Adding to the counter every iteration to keep track of how many digits there are.
    }
    return dig;
}

int checksum(int arr[], int dig)
{
    int countsum = 0;
    int g = 0;
    for (int j = (dig - 1); j >= 0; j--) //Starts at last digit of array
    {
        //printf("current digit number: %i, which is digit %i\n", digits-g, arr[j]);
        //printf("Countsum pre: %i\n", countsum);

        if (g % 2 == 1) // If g is uneven, it means its every other digit.
        {
            countsum = (countsum + (arr[j] * 2 % 10) + (arr[j] * 2 / 10));
            /* Regardless of if a digit when multiplied by 2 is greater than 10, when taking the remainder when dividing by 10 you get the second digit
            after it has been multiplied, same as if it was that number +10. 14*2 % 10 == 8, 4*2 % 10 == 8.
            If the number when multiplied by 2 is greater than 10, the second addition gives us that first digit multiplied by 2, 14*2(==28) / 10 == 2, if the number
            wasnt greater than 10 than its simply 4*2(==8) / 10 == 0, thus nothing is added.
            */
        }
        else
        {
            countsum = (countsum + arr[j]);
        }
        //printf("Countsum post: %i\n", countsum);
        g++;
    }
    return countsum;
}

const char* comp(long num, int dig)
{
    string company;
    //Gets first two digits of creditcard
    while (num > 100)
    {
        num = num / 10;
    }

    if ((num == 51 || num == 52 || num == 53 || num == 54 || num == 55) && (dig == 16))
    {
        company = ("MASTERCARD");
    }
    else if ((num/10 == 4) && (dig == 13 || dig == 16)) //Visa always starts with first starting digit 4, so second digit is unimportant. copy/10 gives us first digit
    {
        company = ("VISA");
    }
    else if ((num == 34 || num == 37) && (dig == 15))
    {
        company = ("AMEX");
    }
    else
    {
        company = ("INVALID");
    }
    return company;
}