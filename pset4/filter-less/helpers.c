#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    if (height < 0)
    {
        return;
    }

    grayscale(height - 1, width, image);

    for (int i = 0; i < width; i++)
    {
        //Get mean for all 3 colors in a pixel, and pass the value ro .r .g .b
        image[height][i].rgbtBlue = round((image[height][i].rgbtBlue + image[height][i].rgbtGreen + image[height][i].rgbtRed) / (float) sizeof(RGBTRIPLE));
        image[height][i].rgbtGreen = image[height][i].rgbtBlue;
        image[height][i].rgbtRed = image[height][i].rgbtBlue;
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepia_blue, sepia_green, sepia_red;

    if (height < 0)
    {
        return;
    }

    sepia(height - 1, width, image);

    for (int i = 0; i < width; i++) //iterate through the array and apply the sepia formula
    {
        sepia_blue = (0.272 * image[height][i].rgbtRed) + (0.534 * image[height][i].rgbtGreen) + (0.131 * image[height][i].rgbtBlue);
        sepia_green = (0.349 * image[height][i].rgbtRed) + (0.686 * image[height][i].rgbtGreen) + (0.168 * image[height][i].rgbtBlue);
        sepia_red = (0.393 * image[height][i].rgbtRed) + (0.769 * image[height][i].rgbtGreen) + (0.189 * image[height][i].rgbtBlue);

        if (sepia_blue > 255)   //if any of the sepia values exceeds "max" value of 255, pass it as 255.
        {
            sepia_blue = 255;
        }

        if (sepia_green > 255)
        {
            sepia_green = 255;
        }

        if (sepia_red > 255)
        {
            sepia_red = 255;
        }
        image[height][i].rgbtBlue = round(sepia_blue);
        image[height][i].rgbtGreen = round(sepia_green);
        image[height][i].rgbtRed = round(sepia_red);

    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (height < 0)
    {
        return;
    }

    reflect(height - 1, width, image);
    //first successful attempt to make recursive calls, after it succeed, implemented it in the other functions

    for (int i = 0, n = width / 2; i < n; i++) // after reaching the middle of the array, every pixel is swapped. if it went further it would re-swap all pixels
    {
        RGBTRIPLE tmp_pix = image[height][i];   //store pixel in a temporary variable.
        image[height][i] = image[height][width - (i + 1)];
        //i starts at 0, but pixel count starts at 1, i.e.  width = 600, the last pixel of the row in the array is image[][599].
        image[height][width - (i + 1)] = tmp_pix;
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
            copy[i][j] = image[i][j];   //make a copy of the original array, to refer for blur box, to avoid get the avg value of an iterated pixel
        }
    }

    for (int i = 0; i < height; i++)        //nest loops to
    {
        for (int j = 0; j < width; j++)     //iterate throught the original array
        {
            int avg_blue = 0,  avg_green = 0,  avg_red = 0;
            float n = 0.0;
            for (int h = -1; h < 2; h++)    //nested loop
            {
                for (int k = -1; k < 2; k++)    //to iterate through the blur box pixel positions relative to image array
                {
                    if ((h + i >= 0 && h + i < height) && (k + j >= 0 && k + j < width))    //conditional to exclude pixels outside the image[][] limits
                    {
                                                                                            //  _________________
                        avg_blue += copy[h + i][k + j].rgbtBlue;                            // |i-1  |i-1  |i-1  |  Blur box, pixel relative positions
                        avg_green += copy[h + i][k + j].rgbtGreen;                          // |j-1  |j=0  |j+1  |  to a pixel[i][j]
                        avg_red +=  copy[h + i][k + j].rgbtRed;                             // |_____|_____|_____|
                        n++;   //counter 'n' for how many blur box pixels meet              // |i=0  |i    |i=0  |
                    }          //the conditionals so, later to be used to calculate         // |j-1  |j    |j+1  |
                }              //the pixel color mean                                       // |_____|_____|_____|
            }                                                                               // |i+1  |i+1  |i+1  |
            image[i][j].rgbtBlue = round(avg_blue / n);                                     // |j-1  |j=0  |j+1  |
            image[i][j].rgbtGreen = round(avg_green / n);                                   // |_____|_____|_____|
            image[i][j].rgbtRed = round(avg_red / n);
        }
    }

    return;
}