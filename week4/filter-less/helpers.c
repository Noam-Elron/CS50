#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float total = 0;
            total += image[i][j].rgbtBlue;
            total += image[i][j].rgbtGreen;
            total += image[i][j].rgbtRed;
            total = round(total / 3.0);
            image[i][j].rgbtBlue = total;
            image[i][j].rgbtGreen = total;
            image[i][j].rgbtRed = total;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            int tmpred = image[i][j].rgbtRed;
            int tmpgreen = image[i][j].rgbtGreen;
            int tmpblue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed = tmpred;
            image[i][width - 1 - j].rgbtGreen = tmpgreen;
            image[i][width - 1 - j].rgbtBlue = tmpblue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgRed = 0;
            int avgGreen = 0;
            int avgBlue = 0;
            int pix_count = 0;

            for (int r = i - 1; r <= i + 1; r++) // Rows- HEIGHT
            {
                for (int c = j - 1; c <= j + 1; c++) // Column -> Element in row
                {
                    if (r >= 0 && c >= 0 && r <= height - 1 && c <= width - 1)
                    {
                        avgRed += copy[r][c].rgbtRed;
                        avgGreen += copy[r][c].rgbtGreen;
                        avgBlue += copy[r][c].rgbtBlue;
                        pix_count += 1;
                    }
                }
            }
            image[i][j].rgbtRed = round((avgRed / ((float)pix_count)));
            image[i][j].rgbtGreen = round((avgGreen / ((float)pix_count)));
            image[i][j].rgbtBlue = round((avgBlue / ((float)pix_count)));
        }
    }

    return;
}
