#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

/*
 * BMP File Format Structures
 * 
 * BMP files consist of:
 * 1. File Header (14 bytes) - contains file type, size, and data offset
 * 2. Info Header (40 bytes) - contains image dimensions and color info
 * 3. Pixel Data - the actual image data (stored bottom-to-top)
 * 
 * IMPORTANT: BMP headers must be byte-packed (no padding between fields)
 * We write each field individually to ensure correct byte alignment
 */

/* RGB Color structure */
typedef struct {
    uint8_t r, g, b;
} RGB;

/*
 * MANDELBROT SET MATHEMATICS
 * ==========================
 * 
 * The Mandelbrot set is defined on the complex plane. For each point c = (cx + cy*i),
 * we iterate the equation:
 * 
 *     z(n+1) = z(n)² + c
 * 
 * Starting with z(0) = 0.
 * 
 * A point c is IN the Mandelbrot set if the sequence remains bounded (|z| ≤ 2).
 * If |z| exceeds 2, the sequence will diverge to infinity.
 * 
 * COMPLEX NUMBER ARITHMETIC:
 * Given z = (zx + zy*i) and c = (cx + cy*i):
 * 
 * z² = (zx + zy*i)²
 *    = zx² + 2*zx*zy*i + (zy*i)²
 *    = zx² + 2*zx*zy*i - zy²        (since i² = -1)
 *    = (zx² - zy²) + (2*zx*zy)*i
 * 
 * Therefore: z² + c = (zx² - zy² + cx) + (2*zx*zy + cy)*i
 * 
 * So our iteration becomes:
 *     zx(new) = zx² - zy² + cx
 *     zy(new) = 2*zx*zy + cy
 * 
 * ESCAPE CONDITION:
 * We check if |z|² = zx² + zy² > 4 (equivalent to |z| > 2)
 * If this happens, the point escapes to infinity.
 * 
 * The number of iterations before escape determines the color.
 */

/**
 * Calculate the number of iterations before a point escapes the Mandelbrot set
 * 
 * @param cx Real part of the complex number c
 * @param cy Imaginary part of the complex number c
 * @param max_iter Maximum number of iterations to test
 * @return Number of iterations before escape (max_iter if point is in the set)
 */
int mandelbrot(double cx, double cy, int max_iter) {
    /* Starting point: z(0) = 0 + 0i */
    double zx = 0.0;
    double zy = 0.0;
    int i;
    
    /* Iterate the equation z(n+1) = z(n)² + c */
    for (i = 0; i < max_iter; i++) {
        /* Calculate squares (we'll need these multiple times) */
        double zx2 = zx * zx;  /* Real part squared */
        double zy2 = zy * zy;  /* Imaginary part squared */
        
        /* Check escape condition: |z|² > 4 */
        /* This is equivalent to checking if zx² + zy² > 4 */
        /* If true, the sequence diverges to infinity */
        if (zx2 + zy2 > 4.0) {
            break;  /* Escaped! Return iteration count */
        }
        
        /* Calculate z² + c using complex arithmetic:
         * z² = (zx² - zy²) + (2*zx*zy)*i
         * z² + c = (zx² - zy² + cx) + (2*zx*zy + cy)*i
         */
        
        /* New real part: zx² - zy² + cx */
        double temp = zx2 - zy2 + cx;
        
        /* New imaginary part: 2*zx*zy + cy */
        zy = 2.0 * zx * zy + cy;
        
        /* Update zx (we used temp to avoid overwriting zx before calculating zy) */
        zx = temp;
    }
    
    /* Return the iteration count
     * If i == max_iter, the point is (probably) in the Mandelbrot set
     * Otherwise, i tells us how quickly the point escaped
     */
    return i;
}

/**
 * Generate a color based on the iteration count
 * Uses a smooth color gradient for aesthetic appeal
 * 
 * @param iter Number of iterations before escape
 * @param max_iter Maximum iterations possible
 * @return RGB color value
 */
RGB get_color(int iter, int max_iter) {
    RGB color;
    
    /* Points in the set (didn't escape) are colored black */
    if (iter == max_iter) {
        color.r = color.g = color.b = 0;
    } else {
        /* Normalize iteration count to range [0, 1] */
        double t = (double)iter / max_iter;
        
        /* Create smooth color gradient using polynomial functions
         * These formulas create beautiful blue-purple gradients
         * You can experiment with different formulas for different color schemes
         */
        color.r = (uint8_t)(9 * (1 - t) * t * t * t * 255);
        color.g = (uint8_t)(15 * (1 - t) * (1 - t) * t * t * 255);
        color.b = (uint8_t)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    }
    
    return color;
}

/**
 * Write BMP file header and info header
 * We write byte-by-byte to ensure proper alignment without padding
 */
void write_bmp_headers(FILE* f, int width, int height, int row_size) {
    uint16_t type = 0x4D42;  /* 'BM' magic number */
    uint32_t file_size = 54 + row_size * height;
    uint16_t reserved = 0;
    uint32_t offset = 54;
    
    /* Write BMP File Header (14 bytes) */
    fwrite(&type, sizeof(uint16_t), 1, f);           /* 2 bytes: BM */
    fwrite(&file_size, sizeof(uint32_t), 1, f);      /* 4 bytes: file size */
    fwrite(&reserved, sizeof(uint16_t), 1, f);       /* 2 bytes: reserved1 */
    fwrite(&reserved, sizeof(uint16_t), 1, f);       /* 2 bytes: reserved2 */
    fwrite(&offset, sizeof(uint32_t), 1, f);         /* 4 bytes: offset to pixel data */
    
    /* Write BMP Info Header (40 bytes) */
    uint32_t header_size = 40;
    int32_t image_width = width;
    int32_t image_height = height;
    uint16_t planes = 1;
    uint16_t bits_per_pixel = 24;
    uint32_t compression = 0;
    uint32_t image_size = row_size * height;
    int32_t x_resolution = 2835;  /* 72 DPI */
    int32_t y_resolution = 2835;
    uint32_t colors_used = 0;
    uint32_t important_colors = 0;
    
    fwrite(&header_size, sizeof(uint32_t), 1, f);    /* 4 bytes: header size */
    fwrite(&image_width, sizeof(int32_t), 1, f);     /* 4 bytes: width */
    fwrite(&image_height, sizeof(int32_t), 1, f);    /* 4 bytes: height */
    fwrite(&planes, sizeof(uint16_t), 1, f);         /* 2 bytes: planes */
    fwrite(&bits_per_pixel, sizeof(uint16_t), 1, f); /* 2 bytes: bits per pixel */
    fwrite(&compression, sizeof(uint32_t), 1, f);    /* 4 bytes: compression */
    fwrite(&image_size, sizeof(uint32_t), 1, f);     /* 4 bytes: image size */
    fwrite(&x_resolution, sizeof(int32_t), 1, f);    /* 4 bytes: x resolution */
    fwrite(&y_resolution, sizeof(int32_t), 1, f);    /* 4 bytes: y resolution */
    fwrite(&colors_used, sizeof(uint32_t), 1, f);    /* 4 bytes: colors used */
    fwrite(&important_colors, sizeof(uint32_t), 1, f); /* 4 bytes: important colors */
}

/**
 * Save image data as a BMP file
 * 
 * @param filename Output filename
 * @param pixels Array of RGB pixel data
 * @param width Image width in pixels
 * @param height Image height in pixels
 * @return 1 on success, 0 on failure
 */
int save_bmp(const char* filename, RGB* pixels, int width, int height) {
    FILE* f = fopen(filename, "wb");
    if (!f) {
        printf("Error: Cannot create file %s\n", filename);
        return 0;
    }
    
    /* BMP rows must be padded to multiples of 4 bytes */
    int row_size = ((width * 3 + 3) / 4) * 4;  /* 3 bytes per pixel (RGB) */
    int padding = row_size - width * 3;
    
    /* Write BMP headers */
    write_bmp_headers(f, width, height, row_size);
    
    /* Padding bytes (up to 3 bytes of zeros) */
    uint8_t pad[3] = {0, 0, 0};
    
    /* Write pixel data
     * BMP format stores pixels bottom-to-top, left-to-right
     * Each pixel is stored as BGR (not RGB!)
     */
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            RGB* pixel = &pixels[y * width + x];
            /* Write in BGR order (BMP format requirement) */
            fwrite(&pixel->b, sizeof(uint8_t), 1, f);
            fwrite(&pixel->g, sizeof(uint8_t), 1, f);
            fwrite(&pixel->r, sizeof(uint8_t), 1, f);
        }
        /* Add row padding to align to 4-byte boundary */
        if (padding > 0) {
            fwrite(pad, sizeof(uint8_t), padding, f);
        }
    }
    
    fclose(f);
    printf("Saved: %s (%d x %d pixels, %d bytes)\n", filename, width, height, 54 + row_size * height);
    return 1;
}

/**
 * Generate a Mandelbrot fractal image
 * 
 * COORDINATE MAPPING:
 * We need to map screen coordinates (pixels) to complex plane coordinates.
 * 
 * The classic Mandelbrot set is centered around (-0.5, 0) in the complex plane
 * and spans roughly from -2.5 to 1 on the real axis and -1 to 1 on imaginary axis.
 * 
 * For each pixel (x, y):
 *   1. Center it: (x - width/2, y - height/2)
 *   2. Scale it: multiply by scale factor
 *   3. Translate to region of interest: add center coordinates (cx, cy)
 * 
 * @param filename Output filename
 * @param width Image width
 * @param height Image height
 * @param cx Center x-coordinate in complex plane
 * @param cy Center y-coordinate in complex plane
 * @param zoom Zoom level (higher = more zoomed in)
 * @param max_iter Maximum iterations for convergence test
 */
void generate_mandelbrot(const char* filename, int width, int height, 
                        double cx, double cy, double zoom, int max_iter) {
    /* Allocate memory for pixel data */
    RGB* pixels = (RGB*)malloc(width * height * sizeof(RGB));
    if (!pixels) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    
    /* Calculate scale factor
     * Base range is 4 units (from -2 to +2 on complex plane)
     * Divided by (zoom * width) to get scale per pixel
     */
    double scale = 4.0 / (zoom * width);
    
    printf("Generating fractal (%dx%d, zoom=%.2f, max_iter=%d)...\n", 
           width, height, zoom, max_iter);
    
    /* Iterate through each pixel */
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            /* Map pixel coordinates to complex plane
             * 
             * (x - width/2) centers the x-coordinate
             * Multiply by scale to get proper complex plane range
             * Add cx to shift to region of interest
             */
            double real = (x - width / 2.0) * scale + cx;
            double imag = (y - height / 2.0) * scale + cy;
            
            /* Calculate how many iterations before this point escapes */
            int iter = mandelbrot(real, imag, max_iter);
            
            /* Convert iteration count to color and store */
            pixels[y * width + x] = get_color(iter, max_iter);
        }
        
        /* Progress indicator (print every 10%) */
        if (y % (height / 10) == 0) {
            printf("Progress: %d%%\n", (y * 100) / height);
        }
    }
    
    printf("Progress: 100%%\n");
    
    /* Save the generated image to BMP file */
    save_bmp(filename, pixels, width, height);
    
    /* Free allocated memory */
    free(pixels);
}

/*
 * ========================================================================
 * STUDENT EXERCISES - Features to Implement
 * ========================================================================
 * 
 * EXERCISE 1: JULIA SET FRACTALS [Difficulty: Medium]
 * ---------------------------------------------------
 * The Julia set is similar to Mandelbrot but uses a fixed c value.
 * Instead of z(n+1) = z(n)² + c where c varies per pixel,
 * use z(n+1) = z(n)² + c_fixed where c_fixed is constant.
 * 
 * Task: Create a function julia_set(double zx, double zy, double cx, double cy, int max_iter)
 * - zx, zy: initial z value (varies per pixel - use pixel coordinates)
 * - cx, cy: fixed complex constant (same for all pixels)
 * - Try cx=-0.7, cy=0.27015 for beautiful results
 * 
 * Hint: Copy the mandelbrot() function and swap what varies vs what's constant
 * 
 * 
 * EXERCISE 2: DIFFERENT COLOR SCHEMES [Difficulty: Easy]
 * ------------------------------------------------------
 * Create multiple color palette functions for variety:
 * 
 * Task: Implement these color schemes:
 * a) get_color_grayscale() - Simple black to white gradient
 * b) get_color_fire() - Black -> Red -> Orange -> Yellow -> White
 * c) get_color_ocean() - Deep blue -> Cyan -> White
 * d) get_color_rainbow() - Full rainbow spectrum (use sin/cos functions)
 * 
 * Hint: Use HSV to RGB conversion for rainbow, or simple linear interpolation
 * 
 * 
 * EXERCISE 3: SMOOTH COLORING [Difficulty: Hard]
 * -----------------------------------------------
 * Current coloring has "bands" - smooth it out using continuous potential.
 * 
 * Formula: smooth_iter = iter + 1 - log(log(|z|)) / log(2)
 * 
 * Task: Modify mandelbrot() to return a double instead of int
 * - After escape, calculate: zx² + zy² to get |z|²
 * - Return: iter + 1 - log(log(sqrt(zx² + zy²))) / log(2)
 * - Modify get_color() to accept double instead of int
 * 
 * This eliminates color banding for professional-looking fractals!
 * 
 * 
 * EXERCISE 4: BURNING SHIP FRACTAL [Difficulty: Easy-Medium]
 * ----------------------------------------------------------
 * A variant of Mandelbrot using absolute values.
 * 
 * Equation: z(n+1) = (|Re(z(n))| + i|Im(z(n))|)² + c
 * 
 * Task: Create burning_ship(double cx, double cy, int max_iter)
 * - Before squaring, take absolute value: zx = fabs(zx), zy = fabs(zy)
 * - Then compute: temp = zx² - zy² + cx, zy = 2*zx*zy + cy
 * - Try center: (0.4, -0.6), zoom: 1.5
 * 
 * 
 * EXERCISE 5: ZOOM ANIMATION [Difficulty: Medium]
 * ------------------------------------------------
 * Generate a sequence of images that zoom into a location.
 * 
 * Task: Create a function that generates 50-100 frames
 * - Start at zoom=1.0, end at zoom=1000.0
 * - Use exponential zoom: zoom = start * pow(end/start, frame/total_frames)
 * - Save as "frame_0001.bmp", "frame_0002.bmp", etc.
 * - Can be combined into video using ffmpeg
 * 
 * 
 * EXERCISE 6: INTERACTIVE COORDINATE SELECTOR [Difficulty: Hard]
 * --------------------------------------------------------------
 * Allow user to input coordinates from command line.
 * 
 * Task: Modify main() to accept parameters:
 * - Use scanf() or command line arguments (argc, argv)
 * - Parse: ./fractal -x -0.5 -y 0.0 -z 10 -i 500 -o output.bmp
 * - Add input validation (check ranges, handle errors)
 * 
 * 
 * EXERCISE 7: MULTITHREADING [Difficulty: Hard]
 * ---------------------------------------------
 * Speed up generation using multiple CPU cores.
 * 
 * Task: Use pthreads (Linux) or Windows threads
 * - Divide image into horizontal strips (e.g., 8 strips for 8 threads)
 * - Each thread processes its strip independently
 * - Join threads before saving
 * - Measure speedup: time_single_thread / time_multi_thread
 * 
 * Hint: Pass a struct containing {pixels, width, height, start_row, end_row, ...}
 * 
 * 
 * EXERCISE 8: ESCAPE TIME HISTOGRAM [Difficulty: Medium]
 * ------------------------------------------------------
 * Improve color distribution by equalizing the histogram.
 * 
 * Task: Two-pass algorithm:
 * 1. First pass: Count how many pixels have each iteration count
 * 2. Calculate cumulative distribution
 * 3. Second pass: Map iteration counts to colors using histogram
 * 
 * This ensures all colors are used more evenly.
 * 
 * 
 * EXERCISE 9: DIFFERENT IMAGE FORMATS [Difficulty: Medium-Hard]
 * -------------------------------------------------------------
 * Save in formats other than BMP.
 * 
 * Task: Implement:
 * a) PPM format (easiest - text or binary format)
 * b) PNG format (use libpng library)
 * c) JPEG format (use libjpeg library)
 * 
 * PPM is great practice as it's simpler than BMP!
 * 
 * 
 * EXERCISE 10: TRICORN (MANDELBAR) FRACTAL [Difficulty: Easy]
 * -----------------------------------------------------------
 * Uses complex conjugate: z(n+1) = conj(z(n))² + c
 * 
 * Task: Create tricorn() function
 * - Conjugate means: flip sign of imaginary part
 * - temp = zx² - zy² + cx
 * - zy = -2*zx*zy + cy  (notice the negative sign!)
 * - zx = temp
 * - Try center: (0, 0), zoom: 1.0
 * 
 * 
 * BONUS CHALLENGE: BUDDHA FRACTALS [Difficulty: Expert]
 * -----------------------------------------------------
 * Instead of coloring based on escape time, track the trajectory!
 * 
 * Algorithm:
 * 1. For random points, iterate and record ALL z positions
 * 2. If point escapes, increment counter for each visited pixel
 * 3. Color based on visit frequency (creates ghostly buddha shape)
 * 
 * This is significantly different and produces stunning results!
 * 
 * ========================================================================
 */

int main() {
    /* Image dimensions and iteration settings */
    int width = 800;
    int height = 600;
    int max_iterations = 256;
    
    printf("=== Mandelbrot Fractal Generator ===\n\n");
    
    /* Generate 1: Classic full view of Mandelbrot set
     * Center: (-0.5, 0) - slightly left of origin
     * Zoom: 1.0 - shows the entire main bulb and cardioid
     */
    generate_mandelbrot("mandelbrot_full.bmp", width, height, 
                       -0.5, 0.0, 1.0, max_iterations);
    
    /* Generate 2: Medium zoom into interesting region
     * Center: (-0.7, 0) - exploring the area between bulbs
     * Zoom: 3.0 - reveals intricate detail
     */
    generate_mandelbrot("mandelbrot_zoom1.bmp", width, height, 
                       -0.7, 0.0, 3.0, max_iterations);
    
    /* Generate 3: Deep zoom into spiral region
     * Center: (-0.743643887037151, 0.131825904205330)
     * This is a famous location showing self-similar spirals
     * Zoom: 100.0 - very deep zoom reveals infinite complexity
     * Note: Doubled iterations for better detail at high zoom
     */
    generate_mandelbrot("mandelbrot_zoom2.bmp", width, height, 
                       -0.743643887037151, 0.131825904205330, 
                       100.0, max_iterations * 2);
    
    printf("\nDone! Generated 3 fractal images.\n");
    printf("\nInteresting coordinates to explore:\n");
    printf("  Mini Mandelbrot: (-0.1592, -1.0317) zoom=100\n");
    printf("  Elephant Valley: (0.282, -0.009) zoom=200\n");
    printf("  Seahorse Valley: (-0.75, 0.1) zoom=50\n");
    printf("\n");
    printf("========================================\n");
    printf("STUDENT EXERCISES AVAILABLE!\n");
    printf("========================================\n");
    printf("See comments above main() for 10+ exercises to extend this code:\n");
    printf("  1. Julia Set Fractals (Medium)\n");
    printf("  2. Different Color Schemes (Easy)\n");
    printf("  3. Smooth Coloring (Hard)\n");
    printf("  4. Burning Ship Fractal (Easy-Medium)\n");
    printf("  5. Zoom Animation (Medium)\n");
    printf("  6. Interactive Coordinate Selector (Hard)\n");
    printf("  7. Multithreading (Hard)\n");
    printf("  8. Escape Time Histogram (Medium)\n");
    printf("  9. Different Image Formats (Medium-Hard)\n");
    printf(" 10. Tricorn Fractal (Easy)\n");
    printf(" BONUS: Buddha Fractals (Expert)\n");
    printf("\nEach exercise includes hints and difficulty ratings!\n");
    
    return 0;
}