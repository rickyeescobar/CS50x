#include "helpers.h"
#include "math.h"
#include "stdio.h"

//global variables for color select
#define BLUE_SELECT 0
#define GREEN_SELECT 1
#define RED_SELECT 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;

            int avg = round((b + g + r) / 3.0);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy;

    // iterates through rows
    for (int i = 0; i < height; i++)
    {
        // iterates through columns
        for (int j = 0; j < width / 2; j++)
        {
            copy = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = copy;
        }
    }
    return;
}

int get_blurred_pxl(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_select)
{
    int px_sum = 0;
    float px_count = 0;
    for (int x = i - 1; x <= (i + 1); x++)
    {
        for (int y = j - 1; y <= (j + 1); y++)
        {
            if (y < 0 || y >= width || x < 0 || x >= height)
            {
                continue;
            }
            if (color_select == BLUE_SELECT)
            {
                px_sum += image[x][y].rgbtBlue;
            }
            else if (color_select == GREEN_SELECT)
            {
                px_sum += image[x][y].rgbtGreen;
            }
            else
            {
                px_sum += image[x][y].rgbtRed;
            }

            px_count++;

        }
    }
    return round(px_sum / px_count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int avgb = 0, avgg = 0, avgr = 0;

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // rows
    for (int i = 0; i < height; i++)
    {
        //columns
        for (int j = 0; j < width; j++)
        {
            // assign averages to image
            image[i][j].rgbtBlue = get_blurred_pxl(i, j, height, width, copy, BLUE_SELECT);
            image[i][j].rgbtGreen = get_blurred_pxl(i, j, height, width, copy, GREEN_SELECT);
            image[i][j].rgbtRed = get_blurred_pxl(i, j, height, width, copy, RED_SELECT);
        }
    }

    return;
}

int edgify(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_select)
{
    // matrix for Gx
    int Gx = 0;
    int sobel_Gx[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1};
    int x_count = 0;

    // matrix for Gy
    int Gy = 0;
    int sobel_Gy[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1};
    int y_count = 0;


    // loop through copy image to detect edges using sobels algorithym
    // loops through the 9x9 grid of pixels surrounding the center pixel inclusive
    for (int x = i - 1; x <= (i + 1); x++)
    {
        for (int y = j - 1; y <= (j + 1); y++)
        {
            if (y < 0 || y >= width || x < 0 || x >= height)
            {
                // handle pixels outside the edge, sets to 0
                Gx += 0;
                Gy += 0;
                x_count++;
                y_count++;
                continue;
            }
            // for blue property
            else if (color_select == BLUE_SELECT)
            {
                Gx += (sobel_Gx[x_count] * image[x][y].rgbtBlue);
                Gy += (sobel_Gy[y_count] * image[x][y].rgbtBlue);

            }
            // for green property
            else if (color_select == GREEN_SELECT)
            {
                Gx += (sobel_Gx[x_count] * image[x][y].rgbtGreen);
                Gy += (sobel_Gy[y_count] * image[x][y].rgbtGreen);
            }
            // for red property
            else
            {
                Gx += (sobel_Gx[x_count] * image[x][y].rgbtRed);
                Gy += (sobel_Gy[y_count] * image[x][y].rgbtRed);
            }

            // iterate through sobel sequence
            x_count++;
            y_count++;

        }
    }

    // apply sobel equation      (SQRT of Gx^2 + Gy^2)

    int new_pixel = round(sqrt((Gx * Gx) + (Gy * Gy)));

    // handle pixel values over 255
    if (new_pixel > 255)
    {
        new_pixel = 255;
    }

    return new_pixel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy image to scan over
    RGBTRIPLE copy[height][width];

    // loop through image to create a copy
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // process of changing pixels in original image to find edges

    // rows
    for (int i = 0; i < height; i++)
    {
        //columns
        for (int j = 0; j < width; j++)
        {
            // assign values to image
            image[i][j].rgbtBlue = edgify(i, j, height, width, copy, BLUE_SELECT);
            image[i][j].rgbtGreen = edgify(i, j, height, width, copy, GREEN_SELECT);
            image[i][j].rgbtRed = edgify(i, j, height, width, copy, RED_SELECT);
        }
    }

    return;
}
