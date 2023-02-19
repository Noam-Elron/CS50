#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void valid(string text, int arr[]);
void alpha(int alphabet[]);
void conversion(int output[], int len, string input, string key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
    int arr[2];
    string key = argv[1];
    valid(key, arr);
    if (arr[0] == 1)
    {
        printf("Error, invalid command line argument input.\n");
        return 1;
    }

    string input = get_string("plaintext: ");
    int inp_len = strlen(input);

    int output[inp_len];
    conversion(output, inp_len, input, key);
    printf("ciphertext: ");
    for (int i = 0; i < inp_len; i++)
    {
        printf("%c", output[i]);
    }
    printf("\n");
    return 0;
    }
    else
    {
        printf("Error, Please only input a single word Key.\n");
        return 1;
    }
}


void conversion(int output[], int len, string input, string key)
{
    int alp = 26;
    int alphabet[alp];
    alpha(alphabet);


    //printf("Input Length: %i\n", len);
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < alp; j++)
        {

            if (input[i] == alphabet[j])
            {
                //printf("Inp Let: %c, Key Let: %c\n", input[i], key[j]);
                output[i] = (int)toupper(key[j]);
            }
            else if (input[i] == tolower(alphabet[j]))
            {
                //printf("Inp Let: %c, Alpha Let: %c\n", input[i], tolower(key[j]));
                output[i] = (int)tolower(key[j]);
            }
            else if ((isalpha(input[i]) == 0))
            {
                //printf("Inp Let: %c, Out Let: %c\n", input[i], input[i]);
                output[i] = input[i];
            }
        }
        //printf("Post Output: %c\n", output[i]);
    }

}



void valid(string text, int arr[])
{
    int lets = strlen(text);
    arr[1] = lets;
    //printf("Text: %s\n", text);
    for (int i = 0; i < lets; i++)
    {
        if (isalpha(text[i]) == 0)
        {
            //printf("char: %c\n", text[i]);
            arr[0] = 1;
        }
        for (int j = i+1; j < lets; j++)
        {
            if (text[i] == text[j])
            {
                //printf("char: %c at index: %i and %i\n", text[i], i, j);
                arr[0] = 1;
            }
        }
    }


    if (lets != 26)
    {
        arr[0] = 1;
    }

}

void alpha(int alphabet[])
{
    for (int i = 0; i < 26; i++)
    {
        alphabet[i] = 65 + i;
        //printf("%c", alphabet[i]);

    }
    //printf("\n");
}