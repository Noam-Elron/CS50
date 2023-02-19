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
            int total = 0;
            total += image[i][j].rgbtRed;
            total += image[i][j].rgbtGreen;
            total += image[i][j].rgbtBlue;
            image[i][j].rgbtRed = round((total / 3.0));
            image[i][j].rgbtGreen = round((total / 3.0));
            image[i][j].rgbtBlue = round((total / 3.0));

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
            int tmpRed = image[i][j].rgbtRed;
            int tmpGreen = image[i][j].rgbtGreen;
            int tmpBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed = tmpRed;
            image[i][width - 1 - j].rgbtGreen = tmpGreen;
            image[i][width - 1 - j].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) // Rows
    {
        for (int j = 0; j < width; j++) // Columns
        {
            copy[i][j] = image[i][j];
        }
    }
    // Creating a copy of image in order to be able to manipulate original images values based on the calculations.


    for (int i = 0; i < height; i++) // Rows
    {
        for (int j = 0; j < width; j++) // Columns
        {
            int avgRed = 0;
            int avgGreen = 0;
            int avgBlue = 0;
            int pix_count = 0;

            for (int row = i - 1; row <= i + 1; row++) //Goes over the rows 1 below up to 1 above the current row
            {
                for (int column = j - 1; column <= j + 1; column++) //Goes over the columns 1 to the left up till 1 to the right
                {
                    if (row >= 0 && column >= 0 && row <= height - 1 && column <= width - 1)
                    {
                        avgRed += copy[row][column].rgbtRed;
                        avgGreen += copy[row][column].rgbtGreen;
                        avgBlue += copy[row][column].rgbtBlue;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) // Rows
    {
        for (int j = 0; j < width; j++) // Columns
        {
            copy[i][j] = image[i][j];
        }
    }
    // Creating a copy of image in order to be able to manipulate original images values based on the calculations.

    for (int i = 0; i < height; i++) // Rows
    {
        for (int j = 0; j < width; j++) // Columns
        {
            int gxRed = 0;
            int gxGreen = 0;
            int gxBlue = 0;

            int gyRed = 0;
            int gyGreen = 0;
            int gyBlue = 0;

            int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            for (int row = i - 1; row <= i + 1; row++) //Goes over the rows 1 below up to 1 above the current row
            {
                for (int column = j - 1; column <= j + 1; column++) //Goes over the columns 1 to the left up till 1 to the right
                {
                    if ((row > -1) && (column > -1) && (row < height) && (column < width))
                    {
                        gxRed += copy[row][column].rgbtRed * gx[row - i + 1][column - j + 1];
                        gxGreen += copy[row][column].rgbtGreen * gx[row - i + 1][column - j + 1];
                        gxBlue += copy[row][column].rgbtBlue * gx[row - i + 1][column - j + 1];
                        /* Multiplies the value of a pixel (in the 3x3 area surrounding the, Pixel being manipulated) by its position in relation to the pixel being manipulated.
                        Row - i + 1 is the same as getting a value between 0 and 2 because row is always either equal to i-1, i or i+1. so i-1-i+1=0, i-i+1=1, i+1-i+1 = 2. Same with column.
                        */
                        gyRed += copy[row][column].rgbtRed * gy[row - i + 1][column - j + 1];
                        gyGreen += copy[row][column].rgbtGreen * gy[row - i + 1][column - j + 1];
                        gyBlue += copy[row][column].rgbtBlue * gy[row - i + 1][column - j + 1];
                    }
                }
            }

            int new_colors[3] = {0, 0, 0};

            new_colors[0] = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            new_colors[1] = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            new_colors[2] = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            for (int g = 0; g < 3; g++)
            {
                if (new_colors[g] > 255)
                {
                    new_colors[g] = 255;
                }
            }

            image[i][j].rgbtRed = new_colors[0];
            image[i][j].rgbtGreen = new_colors[1];
            image[i][j].rgbtBlue = new_colors[2];
        }
    }

    return;
}
