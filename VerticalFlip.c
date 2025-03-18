#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
extern int FlipVertical(uint8_t*** img1, uint8_t*** img2, int rows, int cols);

int main()
{
    int rows, depth = 3, cols;				   
    printf("Enter rows: ");
    scanf("%d", &rows);
    printf("Enter columns: ");
    scanf("%d", &cols);
    
	
    
    uint8_t ***img1 = (uint8_t***)malloc(depth * sizeof(uint8_t**));
    uint8_t ***img2 = (uint8_t***)malloc(depth * sizeof(uint8_t**));
    
    for (int i = 0; i < depth; i++) {
        img1[i] = (uint8_t**)malloc(rows * sizeof(uint8_t *));
        img2[i] = (uint8_t**)malloc(rows * sizeof(uint8_t *));
        
        for (int j = 0; j < rows; j++) {
            img1[i][j] = (uint8_t*)malloc(cols * sizeof(uint8_t));
            img2[i][j] = (uint8_t*)malloc(cols * sizeof(uint8_t));
        }
    }
    
    srand(time(0));
    
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                img1[i][j][k] = rand() % 256;
            }
        }
    }
    int m = rows, n = cols;
    
    FlipVertical(img1, img2, m, n);
    
    printf("Original Image:\n");
    for (int j = 0; j < rows; j++) {
        for (int k = 0; k < cols; k++) {
            printf("[%d %d %d] ", img1[0][j][k], img1[1][j][k], img1[2][j][k]);
        }
        printf("\n");
    }
    
    printf("\nFlipped Image:\n");
    for (int j = 0; j < rows; j++) {
        for (int k = 0; k < cols; k++) {
            printf("[%d %d %d] ", img2[0][j][k], img2[1][j][k], img2[2][j][k]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < rows; j++) {
            free(img1[i][j]);
            free(img2[i][j]);
        }
        free(img1[i]);
        free(img2[i]);
    }
    free(img1);
    free(img2);
    
    return 0;
}