#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Could not open image\n");
    }

    char file_name[8];
    int photo_count = 0;
    bool include_jpeg_header;
    BYTE buffer[BLOCK_SIZE];
    FILE *image_file = NULL;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE) {
        include_jpeg_header =
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0;

        if (include_jpeg_header && image_file != NULL) {
            fclose(image_file);
            photo_count++;
        }

        if (include_jpeg_header) {
            sprintf(file_name, "%03d.jpg", photo_count);
            image_file = fopen(file_name, "w");
        }

        if (image_file != NULL) {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, image_file);
        }
    }

    fclose(image_file);
    fclose(file);
}
