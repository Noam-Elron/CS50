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
        for (int j = 0; j < (width/2); j++)
        {
            int tmpred = image[i][j].rgbtRed;
            int tmpgreen = image[i][j].rgbtGreen;
            int tmpblue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width-1-j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;

            image[i][width-1-j].rgbtRed = tmpred;
            image[i][width-1-j].rgbtGreen = tmpgreen;
            image[i][width-1-j].rgbtBlue = tmpblue;
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
            int avgRed = copy[i][j].rgbtRed;
            int avgGreen = copy[i][j].rgbtGreen; //Pixel itself
            int avgBlue = copy[i][j].rgbtBlue;
            int pix_count = 1; // Pixel itself

            if (i > 0 && j > 0 && i < width-1 && j < height - 1) // Middle Pixels - AKA not Corner or Edge
            {
                //Top row
                avgRed += copy[i-1][j-1].rgbtRed;
                avgGreen += copy[i-1][j-1].rgbtGreen; //Diagonally Left, Up
                avgBlue += copy[i-1][j-1].rgbtBlue;

                avgRed += copy[i-1][j].rgbtRed;
                avgGreen += copy[i-1][j].rgbtGreen; // Straight Up
                avgBlue += copy[i-1][j].rgbtBlue;

                avgRed += copy[i-1][j+1].rgbtRed;
                avgGreen += copy[i-1][j+1].rgbtGreen; // Diagonally Right, Up
                avgBlue += copy[i-1][j+1].rgbtBlue;

                //Middle row
                avgRed += copy[i][j-1].rgbtRed;
                avgGreen += copy[i][j-1].rgbtGreen; // Left
                avgBlue += copy[i][j-1].rgbtBlue;

                avgRed += copy[i][j+1].rgbtRed;
                avgGreen += copy[i][j+1].rgbtGreen; // Right
                avgBlue += copy[i][j+1].rgbtBlue;

                //Bottom row
                avgRed += copy[i+1][j-1].rgbtRed;
                avgGreen += copy[i+1][j-1].rgbtGreen; // Diagonally Left, Down
                avgBlue += copy[i+1][j-1].rgbtBlue;

                avgRed += copy[i+1][j].rgbtRed;
                avgGreen += copy[i+1][j].rgbtGreen; // Straight Down
                avgBlue += copy[i+1][j].rgbtBlue;

                avgRed += copy[i+1][j+1].rgbtRed;
                avgGreen += copy[i+1][j+1].rgbtGreen; // Diagonally Right, Down
                avgBlue += copy[i+1][j+1].rgbtBlue;


                pix_count += 8;
            }

            else if ((i == 0 && j == 0)) // Top Left Corner
            {
                avgRed += copy[i][j+1].rgbtRed;
                avgGreen += copy[i][j+1].rgbtGreen; // Right
                avgBlue += copy[i][j+1].rgbtBlue;

                avgRed += copy[i+1][j].rgbtRed;
                avgGreen += copy[i+1][j].rgbtGreen; // Down
                avgBlue += copy[i+1][j].rgbtBlue;

                avgRed += copy[i+1][j+1].rgbtRed;
                avgGreen += copy[i+1][j+1].rgbtGreen; // Diagonally Right, Down
                avgBlue += copy[i+1][j+1].rgbtBlue;

                pix_count += 3;

            }

            else if (i == height-1 && j == 0) //Bottom Left Corner
            {
                avgRed += copy[i-1][j].rgbtRed;
                avgGreen += copy[i-1][j].rgbtGreen; // Up
                avgBlue += copy[i-1][j].rgbtBlue;

                avgRed += copy[i-1][j+1].rgbtRed;
                avgGreen += copy[i-1][j+1].rgbtGreen; // Diagonally Up, Right
                avgBlue += copy[i-1][j+1].rgbtBlue;

                avgRed += copy[i][j+1].rgbtRed;
                avgGreen += copy[i][j+1].rgbtGreen; // Right
                avgBlue += copy[i][j+1].rgbtBlue;

                pix_count += 3;

            }

            else if (i == 0 && j == width-1) //Top Right Corner
            {
                avgRed += copy[i][j-1].rgbtRed;
                avgGreen += copy[i][j-1].rgbtGreen; // Left
                avgBlue += copy[i][j-1].rgbtBlue;

                avgRed += copy[i+1][j-1].rgbtRed;
                avgGreen += copy[i+1][j-1].rgbtGreen; // Diagonally Down, Left
                avgBlue += copy[i+1][j-1].rgbtBlue;

                avgRed += copy[i+1][j].rgbtRed;
                avgGreen += copy[i+1][j].rgbtGreen; // Down
                avgBlue += copy[i+1][j].rgbtBlue;

                pix_count += 3;

            }

            else if (i == height-1 && j == width-1) // Bottom Right Corner
            {
                avgRed += copy[i-1][j].rgbtRed;
                avgGreen += copy[i-1][j].rgbtGreen; // Up
                avgBlue += copy[i-1][j].rgbtBlue;

                avgRed += copy[i-1][j-1].rgbtRed;
                avgGreen += copy[i-1][j-1].rgbtGreen; // Diagonally Up, Left
                avgBlue += copy[i-1][j-1].rgbtBlue;

                avgRed += copy[i][j-1].rgbtRed;
                avgGreen += copy[i][j-1].rgbtGreen; // Left
                avgBlue += copy[i][j-1].rgbtBlue;

                pix_count += 3;

            }


            else if (i == 0 && j != 0 && j != width-1) // Top Edges
            {
                avgRed += copy[i][j-1].rgbtRed;
                avgGreen += copy[i][j-1].rgbtGreen; // Left
                avgBlue += copy[i][j-1].rgbtBlue;

                avgRed += copy[i+1][j-1].rgbtRed;
                avgGreen += copy[i+1][j-1].rgbtGreen; // Diagonally Down, Left
                avgBlue += copy[i+1][j-1].rgbtBlue;

                avgRed += copy[i+1][j].rgbtRed;
                avgGreen += copy[i+1][j].rgbtGreen; // Down
                avgBlue += copy[i+1][j].rgbtBlue;

                avgRed += copy[i+1][j+1].rgbtRed;
                avgGreen += copy[i+1][j+1].rgbtGreen; // Diagonally Down, Right
                avgBlue += copy[i+1][j+1].rgbtBlue;

                avgRed += copy[i][j+1].rgbtRed;
                avgGreen += copy[i][j+1].rgbtGreen; // Right
                avgBlue += copy[i][j+1].rgbtBlue;

                pix_count += 5;

            }

            else if (j == 0 && i != 0 && i != height-1) // Left Edges
            {
                avgRed += copy[i-1][j].rgbtRed;
                avgGreen += copy[i-1][j].rgbtGreen; // Up
                avgBlue += copy[i-1][j].rgbtBlue;

                avgRed += copy[i-1][j+1].rgbtRed;
                avgGreen += copy[i-1][j+1].rgbtGreen; // Diagonally Up, Right
                avgBlue += copy[i-1][j+1].rgbtBlue;

                avgRed += copy[i][j+1].rgbtRed;
                avgGreen += copy[i][j+1].rgbtGreen; // Right
                avgBlue += copy[i][j+1].rgbtBlue;

                avgRed += copy[i+1][j+1].rgbtRed;
                avgGreen += copy[i+1][j+1].rgbtGreen; // Diagonally Down, Right
                avgBlue += copy[i+1][j+1].rgbtBlue;

                avgRed += copy[i+1][j].rgbtRed;
                avgGreen += copy[i+1][j].rgbtGreen; // Down
                avgBlue += copy[i+1][j].rgbtBlue;

                pix_count += 5;

            }

            else if (i == height-1 && j != 0 && j != width-1) // Bottom Edges
            {
                avgRed += copy[i][j-1].rgbtRed;
                avgGreen += copy[i][j-1].rgbtGreen; // Left
                avgBlue += copy[i][j-1].rgbtBlue;

                avgRed += copy[i-1][j-1].rgbtRed;
                avgGreen += copy[i-1][j-1].rgbtGreen; // Diagonally Up, Left
                avgBlue += copy[i-1][j-1].rgbtBlue;

                avgRed += copy[i-1][j].rgbtRed;
                avgGreen += copy[i-1][j].rgbtGreen; // Up
                avgBlue += copy[i-1][j].rgbtBlue;

                avgRed += copy[i-1][j+1].rgbtRed;
                avgGreen += copy[i-1][j+1].rgbtGreen; // Diagonally Up, Right
                avgBlue += copy[i-1][j+1].rgbtBlue;

                avgRed += copy[i][j+1].rgbtRed;
                avgGreen += copy[i][j+1].rgbtGreen; // Right
                avgBlue += copy[i][j+1].rgbtBlue;

                pix_count += 5;

            }

            else if (j == width-1 && i != 0 && i != height-1) // Right Edges
            {
                avgRed += copy[i-1][j].rgbtRed;
                avgGreen += copy[i-1][j].rgbtGreen; // Up
                avgBlue += copy[i-1][j].rgbtBlue;

                avgRed += copy[i-1][j-1].rgbtRed;
                avgGreen += copy[i-1][j-1].rgbtGreen; // Diagonally Up, Left
                avgBlue += copy[i-1][j-1].rgbtBlue;

                avgRed += copy[i][j-1].rgbtRed;
                avgGreen += copy[i][j-1].rgbtGreen; // Left
                avgBlue += copy[i][j-1].rgbtBlue;

                avgRed += copy[i+1][j-1].rgbtRed;
                avgGreen += copy[i+1][j-1].rgbtGreen; // Diagonally Down, Left
                avgBlue += copy[i+1][j-1].rgbtBlue;

                avgRed += copy[i+1][j].rgbtRed;
                avgGreen += copy[i+1][j].rgbtGreen; // Down
                avgBlue += copy[i+1][j].rgbtBlue;

                pix_count += 5;

            }
        image[i][j].rgbtRed = round((avgRed/((float)pix_count)));
        image[i][j].rgbtGreen = round((avgGreen/((float)pix_count)));
        image[i][j].rgbtBlue = round((avgBlue/((float)pix_count)));

        }
    }

    return;
}
