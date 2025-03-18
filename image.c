#include <stdio.h>
#include <stdlib.h>

#define name_size 100

#pragma pack(1) // Ensure no padding is added to the structure

extern void FlipVertical(unsigned char ***img1, unsigned char ***img2, int height, int width);

struct bitmap_header {
    char name[2];
    unsigned int size;
     int reserved;
    unsigned int offset;
    unsigned int header_size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int img_size;
    int x_res;
    int y_res;
    unsigned int n_colors;
    unsigned int important_colors;
};

void savebmpfile(const char *filename, struct bitmap_header *header, unsigned char ***img, int rows, int cols) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Write the header
    fwrite(header, sizeof(struct bitmap_header), 1, fp);

    // Write the pixel data
    for (int j = rows - 1; j >= 0; j--) {
        for (int k = 0; k < cols; k++) {
            fwrite(&img[2][j][k], 1, 1, fp); // B
            fwrite(&img[1][j][k], 1, 1, fp); // G
            fwrite(&img[0][j][k], 1, 1, fp); // R
        }
    }

    fclose(fp);
}

void openbmpfile(const char *filename) {
	char fullFilename[name_size];
	char fullFlipped[name_size];
	snprintf(fullFilename, sizeof(fullFilename), "%s.bmp", filename);
	snprintf(fullFlipped, sizeof(fullFlipped), "%s_flipped.bmp", filename);
    FILE *fp = fopen(fullFilename, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    struct bitmap_header header;
    fread(&header, sizeof(struct bitmap_header), 1, fp);

    if (header.name[0] != 'B' || header.name[1] != 'M') {
        printf("Not a BMP file\n");
        fclose(fp);
        return;
    }

    printf("First two characters: %c%c\n", header.name[0], header.name[1]);
    printf("Image dimensions: %d x %d\n", header.width, header.height);

    int width = header.width;
    int height = header.height;

    // Move to offset to the start of the pixel data
    fseek(fp, header.offset, SEEK_SET);

    // Allocate memory for the image arrays
    unsigned char ***img1 = malloc(3 * sizeof(unsigned char **));
    unsigned char ***img2 = malloc(3 * sizeof(unsigned char **));
    for (int i = 0; i < 3; i++) {
        img1[i] = malloc(height * sizeof(unsigned char *));
        img2[i] = malloc(height * sizeof(unsigned char *));
        for (int j = 0; j < height; j++) {
            img1[i][j] = malloc(width * sizeof(unsigned char));
            img2[i][j] = malloc(width * sizeof(unsigned char));
        }
    }

    // Read pixel data into img1
    for (int j = height - 1; j >= 0; j--) {
        for (int k = 0; k < width; k++) {
            fread(&img1[2][j][k], 1, 1, fp); // Blue
            fread(&img1[1][j][k], 1, 1, fp); // Green
            fread(&img1[0][j][k], 1, 1, fp); // Red
        }
    }

    fclose(fp);

    // Flip img1 vertically into img2
    FlipVertical(img1, img2, height, width);

    // Save img2 to a new BMP file
    savebmpfile(fullFlipped, &header, img2, height, width);

    // Free memory
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < height; j++) {
            free(img1[i][j]);
            free(img2[i][j]);
        }
        free(img1[i]);
        free(img2[i]);
    }
    free(img1);
    free(img2);
}

int main() {
	char filename[name_size];
	printf("Please input your bmp file to flip: ");
	scanf("%99s", filename);
    openbmpfile(filename);
    return 0;
}