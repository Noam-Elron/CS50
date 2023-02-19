#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int grade_level(int letter, int word, int sentence);

int main(void)
{
    string inp = get_string("Enter text: ");
    //printf("Return: %s\n", inp);
    int characters = count_letters(inp);
    int words = count_words(inp);
    int sentences = count_sentences(inp);
    int grade = grade_level(characters, words, sentences);
    //printf("Characters: %i, Words: %i, Sentences: %i\n", characters, words, sentences);
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
    printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int let = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            let++;
        }
    }
    return let;
}

int count_words(string text)
{
    int words = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == 32 && text[i + 1] != 32)
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}

int grade_level(int letter, int word, int sentence)
{
    float average_letter = ((float)letter / (float)word) * 100; //per 100 words
    //printf("Average letters per 100 words: %f\n", average_letter);
    float average_sentence = ((float)sentence / (float)word) * 100; //per 100 words
    //printf("Average sentences per 100 words: %f\n", average_sentence);
    float index = (0.0588 * average_letter - 0.296 * average_sentence - 15.8);
    //printf("Grade: %f\n", index);
    return round(index);
}