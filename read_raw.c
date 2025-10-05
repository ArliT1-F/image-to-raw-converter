/*
 * Read raw BGR/RGB files in pure C
 * Compile: gcc -o read_raw read_raw.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t format;  // 1=BGRA, 2=RGBA, 3=BGR, 4=RGB
} ImageHeader;
#pragma pack(pop)

typedef struct {
    uint8_t* data;
    uint32_t width;
    uint32_t height;
    uint32_t channels;
    char format[8];
} RawImage;

void free_image(RawImage* img) {
    if (img && img->data) {
        free(img->data);
        img->data = NULL;
    }
}

RawImage* read_raw_with_metadata(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "❌ Cannot open file: %s\n", filename);
        return NULL;
    }
    
    // Read header
    ImageHeader header;
    if (fread(&header, sizeof(ImageHeader), 1, file) != 1) {
        fprintf(stderr, "❌ Failed to read header\n");
        fclose(file);
        return NULL;
    }
    
    // Determine format
    const char* format_names[] = {"", "BGRA", "RGBA", "BGR", "RGB"};
    uint32_t channels = (header.format == 1 || header.format == 2) ? 4 : 3;
    
    printf("📐 Dimensions: %ux%u\n", header.width, header.height);
    printf("🎨 Format: %s\n", format_names[header.format]);
    printf("📊 Channels: %u\n", channels);
    
    // Allocate memory for pixel data
    size_t data_size = header.width * header.height * channels;
    uint8_t* pixel_data = (uint8_t*)malloc(data_size);
    
    if (!pixel_data) {
        fprintf(stderr, "❌ Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    // Read pixel data
    size_t bytes_read = fread(pixel_data, 1, data_size, file);
    fclose(file);
    
    if (bytes_read != data_size) {
        fprintf(stderr, "❌ Read %zu bytes, expected %zu\n", bytes_read, data_size);
        free(pixel_data);
        return NULL;
    }
    
    // Create image structure
    RawImage* img = (RawImage*)malloc(sizeof(RawImage));
    img->data = pixel_data;
    img->width = header.width;
    img->height = header.height;
    img->channels = channels;
    strncpy(img->format, format_names[header.format], sizeof(img->format));
    
    printf("✅ Successfully loaded image!\n");
    
    return img;
}

RawImage* read_raw_without_metadata(const char* filename, 
                                     uint32_t width, 
                                     uint32_t height, 
                                     const char* format) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "❌ Cannot open file: %s\n", filename);
        return NULL;
    }
    
    uint32_t channels = (strcmp(format, "BGRA") == 0 || strcmp(format, "RGBA") == 0) ? 4 : 3;
    size_t data_size = width * height * channels;
    
    uint8_t* pixel_data = (uint8_t*)malloc(data_size);
    if (!pixel_data) {
        fprintf(stderr, "❌ Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    size_t bytes_read = fread(pixel_data, 1, data_size, file);
    fclose(file);
    
    if (bytes_read != data_size) {
        fprintf(stderr, "❌ Read %zu bytes, expected %zu\n", bytes_read, data_size);
        free(pixel_data);
        return NULL;
    }
    
    RawImage* img = (RawImage*)malloc(sizeof(RawImage));
    img->data = pixel_data;
    img->width = width;
    img->height = height;
    img->channels = channels;
    strncpy(img->format, format, sizeof(img->format));
    
    printf("✅ Successfully loaded %ux%u image in %s format\n", width, height, format);
    
    return img;
}

// Get pixel value at (x, y)
void get_pixel(RawImage* img, uint32_t x, uint32_t y) {
    if (!img || x >= img->width || y >= img->height) {
        printf("❌ Invalid coordinates\n");
        return;
    }
    
    uint32_t index = (y * img->width + x) * img->channels;
    
    printf("🎨 Pixel at (%u, %u): ", x, y);
    for (uint32_t i = 0; i < img->channels; i++) {
        printf("%u ", img->data[index + i]);
    }
    printf("\n");
}

// Save as PPM (simple image format, can be viewed with image viewers)
int save_as_ppm(RawImage* img, const char* output_filename) {
    if (img->channels != 3) {
        fprintf(stderr, "❌ PPM only supports 3-channel images\n");
        return -1;
    }
    
    FILE* file = fopen(output_filename, "wb");
    if (!file) {
        fprintf(stderr, "❌ Cannot create file: %s\n", output_filename);
        return -1;
    }
    
    // Write PPM header
    fprintf(file, "P6\n%u %u\n255\n", img->width, img->height);
    
    // Convert BGR to RGB if needed
    if (strcmp(img->format, "BGR") == 0) {
        for (uint32_t i = 0; i < img->width * img->height; i++) {
            uint32_t index = i * 3;
            // Write in RGB order (reverse BGR)
            fwrite(&img->data[index + 2], 1, 1, file); // R
            fwrite(&img->data[index + 1], 1, 1, file); // G
            fwrite(&img->data[index + 0], 1, 1, file); // B
        }
    } else {
        fwrite(img->data, 1, img->width * img->height * 3, file);
    }
    
    fclose(file);
    printf("💾 Saved as %s (PPM format)\n", output_filename);
    return 0;
}

int main() {
    printf("🖼️  Raw Image File Reader (C)\n\n");
    
    // Example 1: Read with metadata
    printf("=== Example 1: Reading file WITH metadata ===\n");
    RawImage* img1 = read_raw_with_metadata("test_bgr_meta.raw");
    
    if (img1) {
        // Get pixel at (0, 0)
        get_pixel(img1, 0, 0);

        // Save as PPM
        if (img1 -> channels == 3) {
            save_as_ppm(img1, "output.ppm");
        }

        free_image(img1);
        free(img1);
    }

    printf("\n");

    // Example 2: Read without metadata
    printf("=== Example 2: Reading File WITHOUT metadata ===\n");
    RawImage* img2 = read_raw_without_metadata("test_bgr.raw", 1920, 1080, "BGR");

    if (img2) {
        get_pixel(img2, 100, 100);
        free_image(img2);
        free(img2);
    }

    return 0;

}