#include "helpers.h"
#include <math.h>
#include <wchar.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Define variable average
    float avg;

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // set average
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            // assign average
            image[i][j].rgbtBlue = roundf(avg);
            image[i][j].rgbtGreen = roundf(avg);
            image[i][j].rgbtRed = roundf(avg);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflected[height][width];
    // Store reflected values
    for (int i = 0; i < height; i++)
    {
        int k = width - 1;
        for (int j = 0; j < width; j++)
        {
            reflected[i][k].rgbtBlue = image[i][j].rgbtBlue;
            reflected[i][k].rgbtGreen = image[i][j].rgbtGreen;
            reflected[i][k].rgbtRed = image[i][j].rgbtRed;
            k--;
        }
    }
    // Assign reflected values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = reflected[i][j].rgbtBlue;
            image[i][j].rgbtGreen = reflected[i][j].rgbtGreen;
            image[i][j].rgbtRed = reflected[i][j].rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    int sumB, sumG, sumR, h, w;
    float pixels;

    // iterate through array of pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // reset counters
            sumB = 0, sumG = 0, sumR = 0, h = i - 1;
            pixels = 0.0;

            for (int k = 0; k < 3; k++)
            {
                // h and w allow integer to be negative, which determines edge conditions
                w = j - 1;

                for (int l = 0; l < 3; l++)
                {
                    if ((h >= 0) && (h < height) && (w >= 0) && (w < width) && (w < j + 3) && (h < i + 3))
                    {
                        // sums up pixels inside of image
                        sumB += image[h][w].rgbtBlue;
                        sumG += image[h][w].rgbtGreen;
                        sumR += image[h][w].rgbtRed;
                        pixels++;
                    }
                    w++;
                }
                h++;
            }

            // set blurred array to average
            blurred[i][j].rgbtBlue = roundf(sumB / pixels);
            blurred[i][j].rgbtGreen = roundf(sumG / pixels);
            blurred[i][j].rgbtRed = roundf(sumR / pixels);

        }

    }
    // reassign image to blurred
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blurred[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blurred[i][j].rgbtGreen;
            image[i][j].rgbtRed = blurred[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // declare mini matrices
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE edge[height][width];
    int wsum_Bx, wsum_Gx, wsum_Rx, wsum_By, wsum_Gy, wsum_Ry, h, w;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset counters
            wsum_Bx = 0, wsum_Gx = 0, wsum_Rx = 0, wsum_By = 0, wsum_Gy = 0, wsum_Ry = 0, h = i - 1;

            for (int k = 0; k < 3; k++)
            {
                // w and h set edge conditions as before
                w = j - 1;

                for (int l = 0; l < 3; l++)
                {
                    if ((h >= 0) && (h < height) && (w >= 0) && (w < width) && (w < j + 3) && (h < i + 3))
                    {
                        // gets weighted sum of mini array based on relevant matrix
                        wsum_Bx += Gx[k][l] * image[h][w].rgbtBlue;
                        wsum_Gx += Gx[k][l] * image[h][w].rgbtGreen;
                        wsum_Rx += Gx[k][l] * image[h][w].rgbtRed;
                        wsum_By += Gy[k][l] * image[h][w].rgbtBlue;
                        wsum_Gy += Gy[k][l] * image[h][w].rgbtGreen;
                        wsum_Ry += Gy[k][l] * image[h][w].rgbtRed;
                    }
                    w++;
                }
                h++;
            }
                //
                edge[i][j].rgbtBlue = wctob(roundf(sqrt(pow(wsum_Bx, 2) + pow(wsum_By, 2))));
                edge[i][j].rgbtGreen = wctob(roundf(sqrt(pow(wsum_Gx, 2) + pow(wsum_Gy, 2))));
                edge[i][j].rgbtRed = wctob(roundf(sqrt(pow(wsum_Rx, 2) + pow(wsum_Ry, 2))));
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = edge[i][j].rgbtBlue;
            image[i][j].rgbtGreen = edge[i][j].rgbtGreen;
            image[i][j].rgbtRed = edge[i][j].rgbtRed;
        }
    }

    return;
}