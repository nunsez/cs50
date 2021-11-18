#include <math.h>

#include "helpers.h"

int limit255_and_round(float);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE triple;
    BYTE gray;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            triple = image[i][j];
            gray = round((triple.rgbtRed + triple.rgbtGreen + triple.rgbtBlue) / 3.0);
            triple.rgbtRed = gray;
            triple.rgbtGreen = gray;
            triple.rgbtBlue = gray;
            image[i][j] = triple;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp_triple;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            temp_triple = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp_triple;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE triple;
    RGBTRIPLE image_blur[height][width];
    int count;
    float sum_red;
    float sum_green;
    float sum_blue;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            count = 0;
            sum_red = 0;
            sum_green = 0;
            sum_blue = 0;

            for (int k = -1; k <= 1; k++) {
                int current_i = i + k;

                if (current_i < 0 || current_i >= height) {
                    continue;
                }

                for (int m = -1; m <= 1; m++) {
                    int current_j = j + m;

                    if (current_j < 0 || current_j >= width) {
                        continue;
                    }

                    triple = image[current_i][current_j];
                    sum_red += triple.rgbtRed;
                    sum_green += triple.rgbtGreen;
                    sum_blue += triple.rgbtBlue;
                    count += 1;

                }
            }

            triple.rgbtRed = round(sum_red / count);
            triple.rgbtGreen = round(sum_green / count);
            triple.rgbtBlue = round(sum_blue / count);
            image_blur[i][j] = triple;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = image_blur[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE triple;
    RGBTRIPLE image_copy[height][width];
    int current_i;
    int current_j;
    int sobel_Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobel_Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int Gx_red;
    int Gx_green;
    int Gx_blue;
    int Gy_red;
    int Gy_green;
    int Gy_blue;


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Gx_red = 0;
            Gx_green = 0;
            Gx_blue = 0;
            Gy_red = 0;
            Gy_green = 0;
            Gy_blue = 0;

            for (int k = -1; k <= 1; k++) {
                current_i = i + k;

                if (current_i < 0 || current_i >= height) {
                    continue;
                }

                for (int m = -1; m <= 1; m++) {
                    current_j = j + m;

                    if (current_j < 0 || current_j >= width) {
                        continue;
                    }

                    triple = image_copy[current_i][current_j];
                    Gx_red += triple.rgbtRed * sobel_Gx[k + 1][m + 1];
                    Gx_green += triple.rgbtGreen * sobel_Gx[k + 1][m + 1];
                    Gx_blue += triple.rgbtBlue * sobel_Gx[k + 1][m + 1];
                    Gy_red += triple.rgbtRed * sobel_Gy[k + 1][m + 1];
                    Gy_green += triple.rgbtGreen * sobel_Gy[k + 1][m + 1];
                    Gy_blue += triple.rgbtBlue * sobel_Gy[k + 1][m + 1];
                }
            }

            triple.rgbtRed = limit255_and_round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            triple.rgbtGreen = limit255_and_round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            triple.rgbtBlue = limit255_and_round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            image[i][j] = triple;
        }
    }
}

int limit255_and_round(float value) {
    if (value > 255) return 255;
    return round(value);
}
