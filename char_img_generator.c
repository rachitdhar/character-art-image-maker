#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define DEFAULT_ROWS 50
#define DEFAULT_COLS 50
#define MIN_ROWS 10
#define MIN_COLS 10
#define MAX_ROWS 1000
#define MAX_COLS 1000

const char* RAMP = " .:-=+*#%@";

// conversion of RGB to brightness (on a scale of 0 to 255)
stbi_uc rgb_to_brightness(stbi_uc r, stbi_uc g, stbi_uc b)
{
	return (stbi_uc)(0.2126 * (float)r + 0.7152 * (float)g + 0.0722 * (float)b);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("ERROR: Insufficient parameters.\nFORMATS ACCEPTABLE:\n\tchar_img_generator.exe <IMG_FILE_NAME>\t\t\t | To make char image of <IMG_FILE_NAME>\n\tchar_img_generator.exe <IMG_FILE_NAME> <ROWS> <COLS>\t | To make a (<ROWS> X <COLS>) char image of <IMG_FILE_NAME>");
		exit(1);
	}
	const char* filename = argv[1];

	int rows = DEFAULT_ROWS, cols = DEFAULT_COLS;
	if (argc == 4)
	{
		rows = atoi(argv[2]);
		cols = atoi(argv[3]);

		if (rows < MIN_ROWS || rows > MAX_ROWS || cols < MIN_COLS || cols > MAX_COLS) {
			printf("ERROR: Invalid ROW/COLUMN size passed.\nROW and COLUMN size must be between %d and %d.\n", MIN_ROWS, MAX_ROWS);
			exit(1);
		}
	}

	// read image file
	int height, width, channels;
	stbi_uc* data = stbi_load(filename, &width, &height, &channels, 0);
	if (data == NULL)
	{
		printf("ERROR: Failed to read the file.\n");
		exit(1);
	}
	printf("Loaded image %s successfully.\nDimensions: (%d X %d), Channels: %d\n\n", filename, width, height, channels);

	// iterating over pixels and storing averages
	stbi_uc** avg_brightness = malloc(sizeof(stbi_uc*) * height);
	for (int i = 0; i < height; i++)
		avg_brightness[i] = malloc(sizeof(stbi_uc) * width);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int index = (y * width + x) * channels;

			stbi_uc r = data[index];
			stbi_uc g = data[index + 1];
			stbi_uc b = data[index + 2];

			avg_brightness[y][x] = rgb_to_brightness(r, g, b);
		}
	}

	// printing to console
	int col_interval = width / cols;
	int row_interval = height / rows;

	for (int r = 0; r < height; r += row_interval) {
		for (int c = 0; c < width; c += col_interval) {
			int ramp_index = (int)(((float)avg_brightness[r][c] / 255) * 10);
			char ramp_char = RAMP[ramp_index];
			printf("%c%c", ramp_char, ramp_char);	// double printing to adjust for 1:2 ratio of width:height of a character in the console
		}
		printf("\n");
	}

	// free data
	for (int i = 0; i < height; i++) {
		free(avg_brightness[i]);
	}
	free(avg_brightness);
	stbi_image_free(data);
	return 0;
}