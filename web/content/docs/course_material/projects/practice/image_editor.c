/*
 * =============================================================================
 * PPM IMAGE PROCESSING - COURSE PROJECT
 * =============================================================================
 * 
 * PROJECT OVERVIEW:
 * This project teaches file I/O, dynamic memory management, and image processing
 * fundamentals through the PPM (Portable Pixmap) image format.
 * 
 * ABOUT PPM FORMAT:
 * PPM is a simple, uncompressed image format that stores color images as plain
 * text or binary data. It's part of the Netpbm format family.
 * 
 * PPM FILE STRUCTURE:
 * 1. Magic Number: "P3" (ASCII) or "P6" (binary)
 * 2. Whitespace (space, tab, newline)
 * 3. Width (ASCII decimal)
 * 4. Whitespace
 * 5. Height (ASCII decimal)
 * 6. Whitespace
 * 7. Maximum color value (typically 255)
 * 8. Whitespace
 * 9. Pixel data:
 *    - P3: ASCII decimal values (R G B R G B ...)
 *    - P6: Binary bytes (RGB RGB RGB ...)
 * 
 * COMMENTS:
 * Lines starting with '#' are comments and should be ignored.
 * Comments can appear between any tokens in the header.
 * 
 * EXAMPLE PPM FILE (P3 format):
 * P3
 * # This is a comment
 * 3 2
 * 255
 * 255 0 0    0 255 0    0 0 255
 * 255 255 0  255 255 255  0 0 0
 * 
 * This represents a 3x2 image:
 * Row 1: Red, Green, Blue
 * Row 2: Yellow, White, Black
 * 
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Structure to represent a single pixel with RGB components */
typedef struct {
    unsigned char r;  /* Red component (0-255) */
    unsigned char g;  /* Green component (0-255) */
    unsigned char b;  /* Blue component (0-255) */
} Pixel;

/* Structure to represent a complete PPM image */
typedef struct {
    int width;        /* Image width in pixels */
    int height;       /* Image height in pixels */
    int max_color;    /* Maximum color value (usually 255) */
    Pixel *data;      /* Pointer to pixel data array */
} PPM_Image;

/*
 * =============================================================================
 * HELPER FUNCTIONS (PROVIDED)
 * =============================================================================
 */

/*
 * Skip whitespace and comments in a PPM file
 * Comments start with '#' and continue to end of line
 */
void skip_whitespace_and_comments(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '#') {
            /* Skip comment line */
            while ((c = fgetc(fp)) != EOF && c != '\n');
        } else if (!isspace(c)) {
            /* Found non-whitespace, put it back */
            ungetc(c, fp);
            break;
        }
    }
}

/*
 * Create a new PPM image with given dimensions
 * Returns NULL on failure
 */
PPM_Image* create_image(int width, int height, int max_color) {
    PPM_Image *img = (PPM_Image*)malloc(sizeof(PPM_Image));
    if (!img) return NULL;
    
    img->width = width;
    img->height = height;
    img->max_color = max_color;
    
    /* Allocate memory for pixel data */
    img->data = (Pixel*)malloc(width * height * sizeof(Pixel));
    if (!img->data) {
        free(img);
        return NULL;
    }
    
    return img;
}

/*
 * Free memory allocated for a PPM image
 */
void free_image(PPM_Image *img) {
    if (img) {
        if (img->data) {
            free(img->data);
        }
        free(img);
    }
}

/*
 * =============================================================================
 * EXERCISE 1: READ PPM HEADER
 * =============================================================================
 * 
 * TASK: Implement the function to read the PPM file header (P3 format only)
 * 
 * REQUIREMENTS:
 * 1. Read and verify the magic number is "P3"
 * 2. Skip any whitespace and comments
 * 3. Read width, height, and max_color values
 * 4. Return 0 on success, -1 on failure
 * 
 * HINTS:
 * - Use skip_whitespace_and_comments() before reading each value
 * - Use fscanf() to read integer values
 * - Check for valid values (positive dimensions, max_color <= 255)
 */
int read_ppm_header(FILE *fp, int *width, int *height, int *max_color) {
    char magic[3];
    
    /* TODO: Read magic number (2 characters + null terminator) */
    if (fscanf(fp, "%2s", magic) != 1) {
        fprintf(stderr, "Error: Cannot read magic number\n");
        return -1;
    }
    
    /* TODO: Verify magic number is "P3" */
    if (strcmp(magic, "P3") != 0) {
        fprintf(stderr, "Error: Not a P3 PPM file (found: %s)\n", magic);
        return -1;
    }
    
    /* TODO: Skip whitespace and comments, then read width */
    skip_whitespace_and_comments(fp);
    if (fscanf(fp, "%d", width) != 1 || *width <= 0) {
        fprintf(stderr, "Error: Invalid width\n");
        return -1;
    }
    
    /* TODO: Skip whitespace and comments, then read height */
    skip_whitespace_and_comments(fp);
    if (fscanf(fp, "%d", height) != 1 || *height <= 0) {
        fprintf(stderr, "Error: Invalid height\n");
        return -1;
    }
    
    /* TODO: Skip whitespace and comments, then read max_color */
    skip_whitespace_and_comments(fp);
    if (fscanf(fp, "%d", max_color) != 1 || *max_color <= 0 || *max_color > 255) {
        fprintf(stderr, "Error: Invalid max color value\n");
        return -1;
    }
    
    return 0;
}

/*
 * =============================================================================
 * EXERCISE 2: READ PPM PIXEL DATA
 * =============================================================================
 * 
 * TASK: Implement the function to read pixel data from P3 format PPM file
 * 
 * REQUIREMENTS:
 * 1. Read RGB values for each pixel (ASCII format)
 * 2. Store pixels in row-major order (left-to-right, top-to-bottom)
 * 3. Validate that values are within [0, max_color] range
 * 4. Return 0 on success, -1 on failure
 * 
 * HINTS:
 * - Total pixels = width * height
 * - Access pixel at (row, col) using: data[row * width + col]
 * - Use fscanf() to read integer RGB values
 */
int read_ppm_data(FILE *fp, PPM_Image *img) {
    int r, g, b;
    int total_pixels = img->width * img->height;
    
    /* TODO: Loop through all pixels and read RGB values */
    for (int i = 0; i < total_pixels; i++) {
        /* Skip any whitespace/comments before reading */
        skip_whitespace_and_comments(fp);
        
        /* TODO: Read R, G, B values */
        if (fscanf(fp, "%d %d %d", &r, &g, &b) != 3) {
            fprintf(stderr, "Error: Cannot read pixel data at position %d\n", i);
            return -1;
        }
        
        /* TODO: Validate values are in valid range */
        if (r < 0 || r > img->max_color || 
            g < 0 || g > img->max_color || 
            b < 0 || b > img->max_color) {
            fprintf(stderr, "Error: Pixel value out of range at position %d\n", i);
            return -1;
        }
        
        /* TODO: Store pixel data */
        img->data[i].r = (unsigned char)r;
        img->data[i].g = (unsigned char)g;
        img->data[i].b = (unsigned char)b;
    }
    
    return 0;
}

/*
 * =============================================================================
 * EXERCISE 3: WRITE PPM FILE
 * =============================================================================
 * 
 * TASK: Implement the function to write a PPM image to file (P3 format)
 * 
 * REQUIREMENTS:
 * 1. Write the header (magic number, dimensions, max_color)
 * 2. Write pixel data in ASCII format
 * 3. Format output nicely (e.g., 5 pixels per line)
 * 4. Return 0 on success, -1 on failure
 * 
 * HINTS:
 * - Use fprintf() for all output
 * - Consider readability when formatting pixel data
 */
int write_ppm(const char *filename, PPM_Image *img) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file for writing: %s\n", filename);
        return -1;
    }
    
    /* TODO: Write PPM header */
    fprintf(fp, "P3\n");
    fprintf(fp, "# Created by PPM Image Processor\n");
    fprintf(fp, "%d %d\n", img->width, img->height);
    fprintf(fp, "%d\n", img->max_color);
    
    /* TODO: Write pixel data */
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            int idx = i * img->width + j;
            fprintf(fp, "%3d %3d %3d   ", 
                    img->data[idx].r, 
                    img->data[idx].g, 
                    img->data[idx].b);
        }
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    return 0;
}

/*
 * =============================================================================
 * EXERCISE 4: CONVERT TO GRAYSCALE
 * =============================================================================
 * 
 * TASK: Convert a color image to grayscale
 * 
 * REQUIREMENTS:
 * 1. Calculate grayscale value using: gray = 0.299*R + 0.587*G + 0.114*B
 * 2. Set all RGB components to the calculated gray value
 * 3. Process all pixels in the image
 * 
 * HINTS:
 * - These coefficients represent human eye sensitivity
 * - Make sure to cast the result to unsigned char
 */
void convert_to_grayscale(PPM_Image *img) {
    /* TODO: Implement grayscale conversion */
    for (int i = 0; i < img->width * img->height; i++) {
        /* Calculate grayscale value using luminosity method */
        int gray = (int)(0.299 * img->data[i].r + 
                         0.587 * img->data[i].g + 
                         0.114 * img->data[i].b);
        
        /* Set all components to gray value */
        img->data[i].r = (unsigned char)gray;
        img->data[i].g = (unsigned char)gray;
        img->data[i].b = (unsigned char)gray;
    }
}

/*
 * =============================================================================
 * EXERCISE 5: APPLY BRIGHTNESS ADJUSTMENT
 * =============================================================================
 * 
 * TASK: Adjust the brightness of an image
 * 
 * REQUIREMENTS:
 * 1. Add the adjustment value to each RGB component
 * 2. Clamp values to [0, max_color] range
 * 3. Process all pixels
 * 
 * HINTS:
 * - Positive adjustment increases brightness
 * - Negative adjustment decreases brightness
 * - Be careful with overflow/underflow
 */
void adjust_brightness(PPM_Image *img, int adjustment) {
    /* TODO: Implement brightness adjustment */
    for (int i = 0; i < img->width * img->height; i++) {
        /* Adjust red component */
        int new_r = img->data[i].r + adjustment;
        if (new_r < 0) new_r = 0;
        if (new_r > img->max_color) new_r = img->max_color;
        img->data[i].r = (unsigned char)new_r;
        
        /* TODO: Adjust green component */
        int new_g = img->data[i].g + adjustment;
        if (new_g < 0) new_g = 0;
        if (new_g > img->max_color) new_g = img->max_color;
        img->data[i].g = (unsigned char)new_g;
        
        /* TODO: Adjust blue component */
        int new_b = img->data[i].b + adjustment;
        if (new_b < 0) new_b = 0;
        if (new_b > img->max_color) new_b = img->max_color;
        img->data[i].b = (unsigned char)new_b;
    }
}

/*
 * =============================================================================
 * EXERCISE 6: FLIP IMAGE VERTICALLY
 * =============================================================================
 * 
 * TASK: Flip the image upside down
 * 
 * REQUIREMENTS:
 * 1. Swap rows from top and bottom
 * 2. Continue until you reach the middle
 * 3. Handle both even and odd heights correctly
 * 
 * HINTS:
 * - You need to swap entire rows
 * - Consider using a temporary variable to store one pixel
 * - Only need to iterate through half the rows
 * - For each row i from top, swap with row (height - 1 - i) from bottom
 * - Access pixel at row i, col j: data[i * width + j]
 */
void flip_vertical(PPM_Image *img) {
    /* TODO: STUDENT IMPLEMENTATION REQUIRED */
    /* Hint: Loop from row 0 to height/2 */
    /* Hint: For each row, swap all pixels with corresponding row from bottom */
}

/*
 * =============================================================================
 * EXERCISE 7: FLIP IMAGE HORIZONTALLY
 * =============================================================================
 * 
 * TASK: Flip the image left-to-right (mirror image)
 * 
 * REQUIREMENTS:
 * 1. Swap pixels from left and right sides of each row
 * 2. Process all rows
 * 3. Handle both even and odd widths correctly
 * 
 * HINTS:
 * - For each row, swap pixels from position j with position (width - 1 - j)
 * - Only need to iterate through half the columns
 * - Use a temporary Pixel variable for swapping
 */
void flip_horizontal(PPM_Image *img) {
    /* TODO: STUDENT IMPLEMENTATION REQUIRED */
}

/*
 * =============================================================================
 * EXERCISE 8: ROTATE IMAGE 90 DEGREES CLOCKWISE
 * =============================================================================
 * 
 * TASK: Rotate the image 90 degrees clockwise
 * 
 * REQUIREMENTS:
 * 1. Create a new image with swapped dimensions (new width = old height)
 * 2. Map each pixel (row, col) to its new position (col, height-1-row)
 * 3. Return the new rotated image
 * 4. Return NULL on failure
 * 
 * HINTS:
 * - Original pixel at (r, c) moves to (c, height-1-r) in rotated image
 * - You need to allocate a new image structure
 * - The caller is responsible for freeing the returned image
 */
PPM_Image* rotate_90_clockwise(PPM_Image *img) {
    /* TODO: STUDENT IMPLEMENTATION REQUIRED */
    return NULL;  /* Replace with actual implementation */
}

/*
 * =============================================================================
 * EXERCISE 9: APPLY SEPIA TONE FILTER
 * =============================================================================
 * 
 * TASK: Apply a sepia tone effect to the image
 * 
 * REQUIREMENTS:
 * 1. Use the following formulas for sepia tone:
 *    new_r = 0.393*r + 0.769*g + 0.189*b
 *    new_g = 0.349*r + 0.686*g + 0.168*b
 *    new_b = 0.272*r + 0.534*g + 0.131*b
 * 2. Clamp all values to [0, max_color]
 * 3. Process all pixels
 * 
 * HINTS:
 * - Sepia tone gives photos an old, brownish appearance
 * - Calculate all three new values before assigning them back
 * - Don't forget to clamp values!
 */
void apply_sepia(PPM_Image *img) {
    /* TODO: STUDENT IMPLEMENTATION REQUIRED */
}

/*
 * =============================================================================
 * EXERCISE 10: INVERT COLORS
 * =============================================================================
 * 
 * TASK: Invert all colors in the image (create negative)
 * 
 * REQUIREMENTS:
 * 1. For each color component, calculate: new_value = max_color - old_value
 * 2. Apply to all RGB components of all pixels
 * 
 * HINTS:
 * - This creates a "negative" effect
 * - Very simple operation but effective
 * - Example: if max_color is 255 and r=100, new r = 255-100 = 155
 */
void invert_colors(PPM_Image *img) {
    /* TODO: STUDENT IMPLEMENTATION REQUIRED */
}

/*
 * =============================================================================
 * EXERCISE 11: APPLY THRESHOLD (BINARY IMAGE)
 * =============================================================================
 * 
 * TASK: Convert image to binary (black and white only) using threshold
 * 
 * REQUIREMENTS:
 * 1. For each pixel, calculate average intensity: avg = (r + g + b) / 3
 * 2. If avg >= threshold, set pixel to white (255, 255, 255)
 * 3. If avg < threshold, set pixel to black (0, 0, 0)
 * 4. Threshold value is between 0 and 255
 * 
 * HINTS:
 * - Common threshold value is 128 (middle of range)
 * - This is useful for creating stark, high-contrast images
 * - Similar to grayscale but only two output colors
 */
void apply_threshold(PPM_Image *img, int threshold) {
    /* TODO: STUDENT IMPLEMENTATION REQUIRED */
}

/*
 * =============================================================================
 * EXERCISE 12: CROP IMAGE
 * =============================================================================
 * 
 * TASK: Extract a rectangular region from the image
 * 
 * REQUIREMENTS:
 * 1. Create a new image with dimensions (crop_width x crop_height)
 * 2. Copy pixels starting from (start_x, start_y)
 * 3. Validate that crop region is within image bounds
 * 4. Return new cropped image, or NULL on error
 * 
 * HINTS:
 * - Check: start_x + crop_width <= img->width
 * - Check: start_y + crop_height <= img->height
 * - Source pixel at (start_y + i, start_x + j) maps to dest (i, j)
 */
PPM_Image* crop_image(PPM_Image *img, int start_x, int start_y, 
                      int crop_width, int crop_height) {
    /* TODO: STUDENT IMPLEMENTATION REQUIRED */
    return NULL;  /* Replace with actual implementation */
}

/*
 * =============================================================================
 * EXERCISE 13: APPLY BOX BLUR
 * =============================================================================
 * 
 * TASK: Apply a simple blur effect using box blur (average of neighbors)
 * 
 * REQUIREMENTS:
 * 1. For each pixel, average the colors of surrounding pixels in a box
 * 2. Box size is (2*radius+1) x (2*radius+1) centered on the pixel
 * 3. Handle edge pixels carefully (don't go out of bounds)
 * 4. Create a new image for output (don't modify in-place)
 * 5. Return new blurred image, or NULL on error
 * 
 * HINTS:
 * - For pixel at (i, j), average all pixels in range:
 *   [i-radius to i+radius] x [j-radius to j+radius]
 * - Clamp indices to valid range: max(0, i-radius) to min(height-1, i+radius)
 * - Count how many pixels you averaged to calculate correct average
 * - This is a simple but slow blur algorithm
 */
PPM_Image* apply_box_blur(PPM_Image *img, int radius) {
    /* TODO: STUDENT IMPLEMENTATION REQUIRED */
    return NULL;  /* Replace with actual implementation */
}

/*
 * =============================================================================
 * EXERCISE 14: ADJUST CONTRAST
 * =============================================================================
 * 
 * TASK: Adjust the contrast of the image
 * 
 * REQUIREMENTS:
 * 1. Use formula: new_value = factor * (old_value - 128) + 128
 * 2. factor > 1.0 increases contrast, factor < 1.0 decreases it
 * 3. Clamp all values to [0, max_color]
 * 4. Apply to all RGB components
 * 
 * HINTS:
 * - 128 is the middle gray value (for max_color=255)
 * - This formula pivots around middle gray
 * - Typical range for factor: 0.5 (low contrast) to 2.0 (high contrast)
 * - Be careful with floating point to integer conversion
 */
void adjust_contrast(PPM_Image *img, double factor) {
    /* TODO: STUDENT IMPLEMENTATION REQUIRED */
}

/*
 * =============================================================================
 * TEST CASE GENERATOR (PROVIDED)
 * =============================================================================
 */

/*
 * Generate a test gradient image
 * Creates a smooth color gradient for testing
 */
void generate_test_gradient(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    
    fprintf(fp, "P3\n# Test gradient\n");
    fprintf(fp, "256 256\n255\n");
    
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            fprintf(fp, "%d %d %d  ", j, i, (j + i) / 2);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

/*
 * Generate a simple test pattern
 * Creates a small image with distinct colors for testing
 */
void generate_test_pattern(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    
    fprintf(fp, "P3\n");
    fprintf(fp, "# Simple 4x3 test pattern\n");
    fprintf(fp, "4 3\n255\n");
    fprintf(fp, "255 0 0   0 255 0   0 0 255   255 255 0\n");
    fprintf(fp, "255 0 255 0 255 255 128 128 128 255 255 255\n");
    fprintf(fp, "0 0 0     64 64 64  192 192 192 128 0 128\n");
    fclose(fp);
}

/*
 * Generate a checkerboard pattern
 * Useful for testing geometric transformations
 */
void generate_test_checkerboard(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    
    fprintf(fp, "P3\n# Checkerboard pattern\n");
    fprintf(fp, "8 8\n255\n");
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                fprintf(fp, "255 255 255  ");  /* White */
            } else {
                fprintf(fp, "0 0 0  ");        /* Black */
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

/*
 * Generate RGB color bars
 * Good for testing color operations
 */
void generate_test_colorbars(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    
    fprintf(fp, "P3\n# RGB color bars\n");
    fprintf(fp, "6 2\n255\n");
    fprintf(fp, "255 0 0  255 0 0  0 255 0  0 255 0  0 0 255  0 0 255\n");
    fprintf(fp, "255 255 0  255 0 255  0 255 255  128 128 128  0 0 0  255 255 255\n");
    fclose(fp);
}

/*
 * =============================================================================
 * TEST FUNCTIONS (PROVIDED)
 * =============================================================================
 */

void run_tests() {
    printf("\n=== Generating Test Files ===\n");
    
    generate_test_pattern("test_pattern.ppm");
    printf("Created: test_pattern.ppm (4x3, simple colors)\n");
    
    generate_test_checkerboard("test_checkerboard.ppm");
    printf("Created: test_checkerboard.ppm (8x8, checkerboard)\n");
    
    generate_test_colorbars("test_colorbars.ppm");
    printf("Created: test_colorbars.ppm (6x2, color bars)\n");
    
    generate_test_gradient("test_gradient.ppm");
    printf("Created: test_gradient.ppm (256x256, gradient)\n");
    
    printf("\n=== Running Basic Tests ===\n");
    
    /* Test 1: Read and write */
    printf("\nTest 1: Read and Write\n");
    FILE *fp = fopen("test_pattern.ppm", "r");
    if (fp) {
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) == 0) {
            PPM_Image *img = create_image(width, height, max_color);
            if (img && read_ppm_data(fp, img) == 0) {
                write_ppm("output_copy.ppm", img);
                printf("✓ Successfully read and wrote test_pattern.ppm\n");
                free_image(img);
            }
        }
        fclose(fp);
    }
    
    /* Test 2: Grayscale */
    printf("\nTest 2: Grayscale Conversion\n");
    fp = fopen("test_colorbars.ppm", "r");
    if (fp) {
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) == 0) {
            PPM_Image *img = create_image(width, height, max_color);
            if (img && read_ppm_data(fp, img) == 0) {
                convert_to_grayscale(img);
                write_ppm("output_gray.ppm", img);
                printf("✓ Created grayscale version\n");
                free_image(img);
            }
        }
        fclose(fp);
    }
    
    /* Test 3: Brightness */
    printf("\nTest 3: Brightness Adjustment\n");
    fp = fopen("test_pattern.ppm", "r");
    if (fp) {
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) == 0) {
            PPM_Image *img = create_image(width, height, max_color);
            if (img && read_ppm_data(fp, img) == 0) {
                adjust_brightness(img, 50);
                write_ppm("output_bright.ppm", img);
                printf("✓ Created brightened version (+50)\n");
                free_image(img);
            }
        }
        fclose(fp);
    }
    
    printf("\n=== Test Files Generated ===\n");
    printf("Test these with your implemented functions:\n");
    printf("- test_pattern.ppm\n");
    printf("- test_checkerboard.ppm\n");
    printf("- test_colorbars.ppm\n");
    printf("- test_gradient.ppm\n");
}

/*
 * =============================================================================
 * MAIN FUNCTION
 * =============================================================================
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("PPM Image Processor - Course Project\n\n");
        printf("Usage: %s <command> [arguments]\n\n", argv[0]);
        printf("Commands:\n");
        printf("  test                  - Generate test files and run basic tests\n");
        printf("  process <input.ppm>   - Process an image (create gray, bright versions)\n");
        printf("  flip_v <input.ppm> <output.ppm>   - Flip image vertically\n");
        printf("  flip_h <input.ppm> <output.ppm>   - Flip image horizontally\n");
        printf("  rotate <input.ppm> <output.ppm>   - Rotate 90° clockwise\n");
        printf("  sepia <input.ppm> <output.ppm>    - Apply sepia tone\n");
        printf("  invert <input.ppm> <output.ppm>   - Invert colors\n");
        printf("  threshold <input.ppm> <output.ppm> <value>  - Apply threshold\n");
        printf("  crop <input.ppm> <output.ppm> <x> <y> <w> <h> - Crop image\n");
        printf("  blur <input.ppm> <output.ppm> <radius>  - Apply box blur\n");
        printf("  contrast <input.ppm> <output.ppm> <factor> - Adjust contrast\n");
        return 1;
    }
    
    if (strcmp(argv[1], "test") == 0) {
        run_tests();
        return 0;
    }
    
    if (strcmp(argv[1], "process") == 0 && argc >= 3) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        printf("Image dimensions: %d x %d\n", width, height);
        printf("Max color value: %d\n", max_color);
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img) {
            fprintf(stderr, "Error: Cannot allocate memory\n");
            fclose(fp);
            return 1;
        }
        
        if (read_ppm_data(fp, img) != 0) {
            free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        /* Create grayscale version */
        PPM_Image *gray = create_image(width, height, max_color);
        if (gray) {
            memcpy(gray->data, img->data, width * height * sizeof(Pixel));
            convert_to_grayscale(gray);
            write_ppm("output_gray.ppm", gray);
            printf("Created: output_gray.ppm\n");
            free_image(gray);
        }
        
        /* Create brightened version */
        PPM_Image *bright = create_image(width, height, max_color);
        if (bright) {
            memcpy(bright->data, img->data, width * height * sizeof(Pixel));
            adjust_brightness(bright, 50);
            write_ppm("output_bright.ppm", bright);
            printf("Created: output_bright.ppm\n");
            free_image(bright);
        }
        
        free_image(img);
        return 0;
    }
    
    if (strcmp(argv[1], "flip_v") == 0 && argc >= 4) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img || read_ppm_data(fp, img) != 0) {
            if (img) free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        flip_vertical(img);
        write_ppm(argv[3], img);
        printf("Created: %s\n", argv[3]);
        free_image(img);
        return 0;
    }
    
    if (strcmp(argv[1], "flip_h") == 0 && argc >= 4) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img || read_ppm_data(fp, img) != 0) {
            if (img) free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        flip_horizontal(img);
        write_ppm(argv[3], img);
        printf("Created: %s\n", argv[3]);
        free_image(img);
        return 0;
    }
    
    if (strcmp(argv[1], "rotate") == 0 && argc >= 4) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img || read_ppm_data(fp, img) != 0) {
            if (img) free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        PPM_Image *rotated = rotate_90_clockwise(img);
        if (rotated) {
            write_ppm(argv[3], rotated);
            printf("Created: %s\n", argv[3]);
            free_image(rotated);
        } else {
            fprintf(stderr, "Error: Rotation failed\n");
        }
        free_image(img);
        return 0;
    }
    
    if (strcmp(argv[1], "sepia") == 0 && argc >= 4) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img || read_ppm_data(fp, img) != 0) {
            if (img) free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        apply_sepia(img);
        write_ppm(argv[3], img);
        printf("Created: %s\n", argv[3]);
        free_image(img);
        return 0;
    }
    
    if (strcmp(argv[1], "invert") == 0 && argc >= 4) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img || read_ppm_data(fp, img) != 0) {
            if (img) free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        invert_colors(img);
        write_ppm(argv[3], img);
        printf("Created: %s\n", argv[3]);
        free_image(img);
        return 0;
    }
    
    if (strcmp(argv[1], "threshold") == 0 && argc >= 5) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img || read_ppm_data(fp, img) != 0) {
            if (img) free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        int threshold = atoi(argv[4]);
        apply_threshold(img, threshold);
        write_ppm(argv[3], img);
        printf("Created: %s (threshold=%d)\n", argv[3], threshold);
        free_image(img);
        return 0;
    }
    
    if (strcmp(argv[1], "crop") == 0 && argc >= 8) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img || read_ppm_data(fp, img) != 0) {
            if (img) free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        int x = atoi(argv[4]);
        int y = atoi(argv[5]);
        int w = atoi(argv[6]);
        int h = atoi(argv[7]);
        
        PPM_Image *cropped = crop_image(img, x, y, w, h);
        if (cropped) {
            write_ppm(argv[3], cropped);
            printf("Created: %s (crop %dx%d at %d,%d)\n", argv[3], w, h, x, y);
            free_image(cropped);
        } else {
            fprintf(stderr, "Error: Crop failed\n");
        }
        free_image(img);
        return 0;
    }
    
    if (strcmp(argv[1], "blur") == 0 && argc >= 5) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img || read_ppm_data(fp, img) != 0) {
            if (img) free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        int radius = atoi(argv[4]);
        PPM_Image *blurred = apply_box_blur(img, radius);
        if (blurred) {
            write_ppm(argv[3], blurred);
            printf("Created: %s (blur radius=%d)\n", argv[3], radius);
            free_image(blurred);
        } else {
            fprintf(stderr, "Error: Blur failed\n");
        }
        free_image(img);
        return 0;
    }
    
    if (strcmp(argv[1], "contrast") == 0 && argc >= 5) {
        FILE *fp = fopen(argv[2], "r");
        if (!fp) {
            fprintf(stderr, "Error: Cannot open file: %s\n", argv[2]);
            return 1;
        }
        
        int width, height, max_color;
        if (read_ppm_header(fp, &width, &height, &max_color) != 0) {
            fclose(fp);
            return 1;
        }
        
        PPM_Image *img = create_image(width, height, max_color);
        if (!img || read_ppm_data(fp, img) != 0) {
            if (img) free_image(img);
            fclose(fp);
            return 1;
        }
        fclose(fp);
        
        double factor = atof(argv[4]);
        adjust_contrast(img, factor);
        write_ppm(argv[3], img);
        printf("Created: %s (contrast factor=%.2f)\n", argv[3], factor);
        free_image(img);
        return 0;
    }
    
    fprintf(stderr, "Error: Unknown command or invalid arguments\n");
    fprintf(stderr, "Run '%s' without arguments for usage information\n", argv[0]);
    return 1;
}