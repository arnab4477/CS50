#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }


    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaBlue, sepiaGreen;

    for (int i = 0 ; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;


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
            int refl = width - j - 1;
            int newRed = image[i][j].rgbtRed;
            int newGreen = image[i][j].rgbtGreen;
            int newBlue = image[i][j].rgbtBlue;


            image[i][j].rgbtBlue = image[i][refl].rgbtBlue;
            image[i][j].rgbtGreen = image[i][refl].rgbtGreen;
            image[i][j].rgbtRed = image[i][refl].rgbtRed;

            image[i][refl].rgbtBlue = newBlue;
            image[i][refl].rgbtGreen = newGreen;
            image[i][refl].rgbtRed = newRed;

        }

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }



    float blurRed, blurGreen, blurBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                blurRed = round((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 9.0);
                blurGreen = round((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 9.0);
                blurBlue = round((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 9.0);

                temp[i][j].rgbtRed = blurRed;
                temp[i][j].rgbtGreen = blurGreen;
                temp[i][j].rgbtBlue = blurBlue;

            }
            else if (i == 0 && j == 0)
            {
                blurRed = round((image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 4.0);
                blurGreen = round((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 4.0);
                blurBlue = round((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 4.0);

                temp[i][j].rgbtRed = blurRed;
                temp[i][j].rgbtGreen = blurGreen;
                temp[i][j].rgbtBlue = blurBlue;
            }
            else if (i == 0 && j > 0 && j < width - 1)
            {
                blurRed = round((image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 6.0);
                blurGreen = round((image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 6.0);
                blurBlue = round((image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 6.0);

                temp[i][j].rgbtRed = blurRed;
                temp[i][j].rgbtGreen = blurGreen;
                temp[i][j].rgbtBlue = blurBlue;
            }
            else if (i > 0 && i < height - 1 && j == 0)
            {
                blurRed = round((image[i-1][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed + image[i+1][j+1].rgbtRed) / 6.0);
                blurGreen = round((image[i-1][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen) / 6.0);
                blurBlue = round((image[i-1][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue) / 6.0);

                temp[i][j].rgbtRed = blurRed;
                temp[i][j].rgbtGreen = blurGreen;
                temp[i][j].rgbtBlue = blurBlue;
            }
            else if (i == height - 1 && j == width - 1)
            {
                blurRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed) / 4.0);
                blurGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen) / 4.0);
                blurBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue) / 4.0);

                temp[i][j].rgbtRed = blurRed;
                temp[i][j].rgbtGreen = blurGreen;
                temp[i][j].rgbtBlue = blurBlue;
            }
            else if (i == height - 1 && j == 0)
            {
                blurRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed) / 4.0);
                blurGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen) / 4.0);
                blurBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue) / 4.0);

                temp[i][j].rgbtRed = blurRed;
                temp[i][j].rgbtGreen = blurGreen;
                temp[i][j].rgbtBlue = blurBlue;
            }
            else if (i == 0 && j == width - 1)
            {
                blurRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed) / 4);
                blurGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen) / 4);
                blurBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue) / 4);

                temp[i][j].rgbtRed = blurRed;
                temp[i][j].rgbtGreen = blurGreen;
                temp[i][j].rgbtBlue = blurBlue;
            }
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                blurRed = round((image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed) / 6.0);
                blurGreen = round((image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen) / 6.0);
                blurBlue = round((image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue) / 6.0);

                temp[i][j].rgbtRed = blurRed;
                temp[i][j].rgbtGreen = blurGreen;
                temp[i][j].rgbtBlue = blurBlue;
            }
            else if (i > 0 && i < height - 1 && j == width - 1)
            {
                blurRed = round((image[i-1][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed) / 6.0);
                blurGreen = round((image[i-1][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen) / 6.0);
                blurBlue = round((image[i-1][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue) / 6.0);

                temp[i][j].rgbtRed = blurRed;
                temp[i][j].rgbtGreen = blurGreen;
                temp[i][j].rgbtBlue = blurBlue;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
