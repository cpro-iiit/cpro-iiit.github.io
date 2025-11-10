#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* ============================================================================
 * SIMULATION PARAMETERS
 * ============================================================================ */
#define WIDTH 800              // Image width in pixels
#define HEIGHT 800             // Image height in pixels
#define N_BODIES 10             // Number of gravitating bodies (planets/stars)
#define N_ROCKETS 5            // Number of rockets to simulate
#define DT 0.01                // Time step for integration (smaller = more accurate)
#define STEPS 5000             // Total simulation steps
#define FRAMES 100             // Number of output frames to generate
#define G 1.0                  // Gravitational constant (can be scaled for visualization)
#define SOFTENING 0.1          // Softening parameter to prevent singularities

/* ============================================================================
 * DATA STRUCTURES
 * ============================================================================ */

/**
 * Body structure representing a gravitating mass (star, planet, etc.)
 * These bodies affect each other gravitationally
 */
typedef struct {
    double x, y;      // Position in 2D space
    double vx, vy;    // Velocity components
    double ax, ay;    // Acceleration components
    double mass;      // Mass of the body (affects gravitational force)
} Body;

/**
 * Rocket structure representing a test particle
 * Rockets are affected by gravity but don't exert gravitational forces
 * This allows us to trace trajectories without affecting the system
 */
typedef struct {
    double x, y;      // Position in 2D space
    double vx, vy;    // Velocity components
    double ax, ay;    // Acceleration components
    int active;       // 1 if rocket is active, 0 if inactive
    double *trail_x;  // Array to store X positions for trajectory trail
    double *trail_y;  // Array to store Y positions for trajectory trail
    int trail_length; // Current length of trail
    int trail_capacity; // Maximum capacity of trail arrays
} Rocket;

/**
 * Pixel structure for BMP image format
 * Uses BGR color ordering (BMP standard)
 */
typedef struct {
    unsigned char b, g, r;  // Blue, Green, Red color channels (0-255)
} Pixel;

/* ============================================================================
 * BMP FILE I/O
 * ============================================================================ */

/**
 * Writes a 24-bit BMP image file
 * 
 * @param filename Output filename
 * @param img      Pixel array (row-major order, top-left origin)
 * @param w        Image width
 * @param h        Image height
 */
void write_bmp(const char *filename, Pixel *img, int w, int h) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    
    // BMP rows must be padded to multiples of 4 bytes
    int row_size = (w * 3 + 3) & ~3;  // Round up to nearest multiple of 4
    int img_size = row_size * h;
    int file_size = 54 + img_size;    // 54-byte header + image data
    
    // Construct 54-byte BMP header
    unsigned char header[54] = {
        'B','M',                                           // BMP signature
        file_size & 0xFF, (file_size >> 8) & 0xFF,        // File size
        (file_size >> 16) & 0xFF, (file_size >> 24) & 0xFF,
        0,0,0,0,                                           // Reserved
        54,0,0,0,                                          // Pixel data offset
        40,0,0,0,                                          // DIB header size
        w & 0xFF, (w >> 8) & 0xFF, (w >> 16) & 0xFF, (w >> 24) & 0xFF,  // Width
        h & 0xFF, (h >> 8) & 0xFF, (h >> 16) & 0xFF, (h >> 24) & 0xFF,  // Height
        1,0,                                               // Color planes
        24,0,                                              // Bits per pixel
        0,0,0,0,                                           // No compression
        img_size & 0xFF, (img_size >> 8) & 0xFF,          // Image size
        (img_size >> 16) & 0xFF, (img_size >> 24) & 0xFF,
        0,0,0,0,                                           // X pixels per meter
        0,0,0,0,                                           // Y pixels per meter
        0,0,0,0,                                           // Colors in palette
        0,0,0,0                                            // Important colors
    };
    
    fwrite(header, 1, 54, f);
    
    // BMP format stores pixels bottom-to-top, so we write rows in reverse
    unsigned char padding[3] = {0, 0, 0};
    int pad_size = row_size - w * 3;
    
    for (int y = h - 1; y >= 0; y--) {
        for (int x = 0; x < w; x++) {
            Pixel *p = &img[y * w + x];
            fwrite(p, 3, 1, f);  // Write BGR triple
        }
        if (pad_size > 0) {
            fwrite(padding, 1, pad_size, f);  // Add row padding
        }
    }
    
    fclose(f);
}

/* ============================================================================
 * INITIALIZATION FUNCTIONS
 * ============================================================================ */

/**
 * Initialize celestial bodies in a stable orbital configuration
 * Body 0 is a massive central star, others orbit around it
 * 
 * @param bodies Array of Body structures to initialize
 * @param n      Number of bodies
 */
void init_bodies(Body *bodies, int n) {
    // Central massive body (like a star)
    bodies[0].x = 0.0;
    bodies[0].y = 0.0;
    bodies[0].vx = 0.0;
    bodies[0].vy = 0.0;
    bodies[0].mass = 100.0;  // Much more massive than other bodies
    
    // Create orbiting bodies (like planets)
    for (int i = 1; i < n; i++) {
        // Distribute bodies in a circle around the central mass
        double angle = 2.0 * M_PI * i / (n - 1);
        double radius = 2.0 + i * 0.5;  // Each body at different orbital radius
        
        // Position on circle
        bodies[i].x = radius * cos(angle);
        bodies[i].y = radius * sin(angle);
        
        // Calculate circular orbital velocity: v = sqrt(GM/r)
        // Velocity is perpendicular to radius for circular orbit
        double v = sqrt(G * bodies[0].mass / radius);
        bodies[i].vx = -v * sin(angle);  // Tangent to circle
        bodies[i].vy = v * cos(angle);
        
        bodies[i].mass = 5.0;  // All orbiting bodies have same mass
    }
}

/**
 * Initialize rockets with given starting positions and velocities
 * Rockets are test particles that don't exert gravitational forces
 * 
 * @param rockets Array of Rocket structures to initialize
 * @param n       Number of rockets
 */
void init_rockets(Rocket *rockets, int n) {
    // Launch rocket from far away to get a long trajectory through the system
    for (int i = 0; i < n; i++) {
        // Start position: far from the central mass and orbiting bodies
        rockets[i].x = -8.0;         // Start position X (far left)
        rockets[i].y = -6.0;         // Start position Y (below)
        
        // Calculate direction vector towards the center (0, 0)
        double dx = 0.0 - rockets[i].x;  // Vector from rocket to center
        double dy = 0.0 - rockets[i].y;
        double dist = sqrt(dx * dx + dy * dy);
        
        // Normalize direction vector and scale by desired speed
        double speed = 0.000005;  // Magnitude of initial velocity
        rockets[i].vx = (dx / dist) * speed;  // Velocity pointing toward center
        rockets[i].vy = (dy / dist) * speed;
        
        rockets[i].ax = 0.0;
        rockets[i].ay = 0.0;
        rockets[i].active = 1;       // Rocket is active
        
        // Allocate memory for trajectory trail
        rockets[i].trail_capacity = STEPS;  // Enough space for all steps
        rockets[i].trail_x = (double *)malloc(rockets[i].trail_capacity * sizeof(double));
        rockets[i].trail_y = (double *)malloc(rockets[i].trail_capacity * sizeof(double));
        rockets[i].trail_length = 0;
        
        // Store initial position in trail
        rockets[i].trail_x[0] = rockets[i].x;
        rockets[i].trail_y[0] = rockets[i].y;
        rockets[i].trail_length = 1;
        
        printf("Rocket %d initialized at (%.2f, %.2f) with velocity (%.2f, %.2f)\n",
               i, rockets[i].x, rockets[i].y, rockets[i].vx, rockets[i].vy);
        printf("  Direction: toward center (0, 0), speed: %.2f\n", speed);
    }
}

/* ============================================================================
 * PHYSICS SIMULATION
 * ============================================================================ */

/**
 * Compute gravitational forces between all bodies using Newton's law of gravitation
 * F = G * m1 * m2 / r^2
 * 
 * This function updates the acceleration (ax, ay) for each body based on
 * gravitational attraction from all other bodies.
 * 
 * @param bodies Array of bodies
 * @param n      Number of bodies
 */
void compute_forces(Body *bodies, int n) {
    // Reset accelerations to zero
    for (int i = 0; i < n; i++) {
        bodies[i].ax = 0.0;
        bodies[i].ay = 0.0;
    }
    
    // Compute pairwise forces (Newton's third law: equal and opposite)
    // We only need to compute each pair once
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Vector from body i to body j
            double dx = bodies[j].x - bodies[i].x;
            double dy = bodies[j].y - bodies[i].y;
            
            // Distance squared with softening to prevent singularities
            // Softening prevents division by zero when bodies are very close
            double dist_sq = dx * dx + dy * dy + SOFTENING * SOFTENING;
            double dist = sqrt(dist_sq);
            
            // Gravitational force magnitude: F = G / r^2
            double force = G / dist_sq;
            
            // Force components (unit vector * force magnitude)
            double fx = force * dx / dist;
            double fy = force * dy / dist;
            
            // Apply Newton's third law
            // Force on i from j: F_ij = m_j * force
            bodies[i].ax += fx / bodies[j].mass;
            bodies[i].ay += fy / bodies[j].mass;
            
            // Force on j from i: F_ji = -F_ij
            bodies[j].ax -= fx / bodies[i].mass;
            bodies[j].ay -= fy / bodies[i].mass;
        }
    }
}

/**
 * Compute gravitational acceleration on rockets from all bodies
 * Rockets don't exert forces, only experience them
 * 
 * @param rockets Array of rockets
 * @param n_rockets Number of rockets
 * @param bodies Array of bodies
 * @param n_bodies Number of bodies
 */
void compute_rocket_forces(Rocket *rockets, int n_rockets, Body *bodies, int n_bodies) {
    for (int i = 0; i < n_rockets; i++) {
        if (!rockets[i].active) continue;
        
        // Reset acceleration
        rockets[i].ax = 0.0;
        rockets[i].ay = 0.0;
        
        // Sum gravitational acceleration from all bodies
        for (int j = 0; j < n_bodies; j++) {
            // Vector from rocket to body
            double dx = bodies[j].x - rockets[i].x;
            double dy = bodies[j].y - rockets[i].y;
            
            // Distance with softening
            double dist_sq = dx * dx + dy * dy + SOFTENING * SOFTENING;
            double dist = sqrt(dist_sq);
            
            // Acceleration = G * M / r^2 (in direction of body)
            double acc = G * bodies[j].mass / dist_sq;
            
            // Acceleration components
            rockets[i].ax += acc * dx / dist;
            rockets[i].ay += acc * dy / dist;
        }
    }
}

/**
 * Update body positions and velocities using leapfrog integration
 * This is a symplectic integrator that conserves energy better than Euler method
 * 
 * Steps:
 * 1. Compute forces/accelerations
 * 2. Update velocities: v(t+dt) = v(t) + a(t) * dt
 * 3. Update positions: x(t+dt) = x(t) + v(t+dt) * dt
 * 
 * @param bodies Array of bodies
 * @param n      Number of bodies
 * @param dt     Time step
 */
void update_bodies(Body *bodies, int n, double dt) {
    // Compute accelerations from gravitational forces
    compute_forces(bodies, n);
    
    // Integrate equations of motion
    for (int i = 0; i < n; i++) {
        // Update velocity: v = v + a * dt
        bodies[i].vx += bodies[i].ax * dt;
        bodies[i].vy += bodies[i].ay * dt;
        
        // Update position: x = x + v * dt
        bodies[i].x += bodies[i].vx * dt;
        bodies[i].y += bodies[i].vy * dt;
    }
}

/**
 * Update rocket positions and velocities
 * Same integration scheme as bodies
 * 
 * @param rockets Array of rockets
 * @param n_rockets Number of rockets
 * @param bodies Array of bodies (for force computation)
 * @param n_bodies Number of bodies
 * @param dt Time step
 */
void update_rockets(Rocket *rockets, int n_rockets, Body *bodies, int n_bodies, double dt) {
    // Compute accelerations from gravitational forces
    compute_rocket_forces(rockets, n_rockets, bodies, n_bodies);
    
    // Integrate equations of motion
    for (int i = 0; i < n_rockets; i++) {
        if (!rockets[i].active) continue;
        
        // Update velocity
        rockets[i].vx += rockets[i].ax * dt;
        rockets[i].vy += rockets[i].ay * dt;
        
        // Update position
        rockets[i].x += rockets[i].vx * dt;
        rockets[i].y += rockets[i].vy * dt;
        
        // Store position in trail if there's space
        if (rockets[i].trail_length < rockets[i].trail_capacity) {
            rockets[i].trail_x[rockets[i].trail_length] = rockets[i].x;
            rockets[i].trail_y[rockets[i].trail_length] = rockets[i].y;
            rockets[i].trail_length++;
        }
        
        // Optional: Deactivate rocket if it goes too far
        double dist = sqrt(rockets[i].x * rockets[i].x + rockets[i].y * rockets[i].y);
        if (dist > 50.0) {
            rockets[i].active = 0;
            printf("Rocket %d left simulation area at step with trail length %d\n", 
                   i, rockets[i].trail_length);
        }
    }
}

/* ============================================================================
 * RENDERING
 * ============================================================================ */

/**
 * Render the current state of the simulation to an image
 * 
 * @param bodies Array of bodies to render
 * @param n_bodies Number of bodies
 * @param rockets Array of rockets to render
 * @param n_rockets Number of rockets
 * @param img Pixel buffer to render into
 * @param scale Coordinate-to-pixel scaling factor
 */
void render(Body *bodies, int n_bodies, Rocket *rockets, int n_rockets, 
            Pixel *img, double scale) {
    // Clear image to black
    memset(img, 0, WIDTH * HEIGHT * sizeof(Pixel));
    
    // Draw coordinate grid for reference
    for (int i = 0; i < WIDTH; i += 50) {
        for (int j = 0; j < HEIGHT; j++) {
            img[j * WIDTH + i].r = 20;
            img[j * WIDTH + i].g = 20;
            img[j * WIDTH + i].b = 20;
        }
    }
    for (int j = 0; j < HEIGHT; j += 50) {
        for (int i = 0; i < WIDTH; i++) {
            img[j * WIDTH + i].r = 20;
            img[j * WIDTH + i].g = 20;
            img[j * WIDTH + i].b = 20;
        }
    }
    
    // Draw bodies (planets/stars)
    for (int i = 0; i < n_bodies; i++) {
        // Convert world coordinates to pixel coordinates
        int px = (int)(bodies[i].x * scale + WIDTH / 2);
        int py = (int)(bodies[i].y * scale + HEIGHT / 2);
        
        // Check if body is within image bounds
        if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
            // Central body is larger
            int radius = (i == 0) ? 8 : 4;
            
            // Draw filled circle for body
            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    if (dx * dx + dy * dy <= radius * radius) {
                        int x = px + dx;
                        int y = py + dy;
                        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                            if (i == 0) {
                                // Central star: yellow
                                img[y * WIDTH + x].r = 255;
                                img[y * WIDTH + x].g = 255;
                                img[y * WIDTH + x].b = 100;
                            } else {
                                // Orbiting bodies: blue shades
                                img[y * WIDTH + x].r = 100 + i * 30;
                                img[y * WIDTH + x].g = 150;
                                img[y * WIDTH + x].b = 255;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Draw rockets and their complete trajectories
    for (int i = 0; i < n_rockets; i++) {
        // Draw the entire trajectory trail up to current position
        for (int t = 0; t < rockets[i].trail_length - 1; t++) {
            // Get start and end points of this segment
            int px1 = (int)(rockets[i].trail_x[t] * scale + WIDTH / 2);
            int py1 = (int)(rockets[i].trail_y[t] * scale + HEIGHT / 2);
            int px2 = (int)(rockets[i].trail_x[t + 1] * scale + WIDTH / 2);
            int py2 = (int)(rockets[i].trail_y[t + 1] * scale + HEIGHT / 2);
            
            // Draw line segment using Bresenham's algorithm
            int dx = abs(px2 - px1);
            int dy = abs(py2 - py1);
            int sx = (px1 < px2) ? 1 : -1;
            int sy = (py1 < py2) ? 1 : -1;
            int err = dx - dy;
            
            int x = px1, y = py1;
            while (1) {
                if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                    // Color gradient: older parts dimmer, newer parts brighter
                    int brightness = 100 + (155 * t) / rockets[i].trail_length;
                    img[y * WIDTH + x].r = brightness;
                    img[y * WIDTH + x].g = brightness / 2;
                    img[y * WIDTH + x].b = brightness / 2;
                }
                
                if (x == px2 && y == py2) break;
                
                int e2 = 2 * err;
                if (e2 > -dy) {
                    err -= dy;
                    x += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    y += sy;
                }
            }
        }
        
        // Draw current rocket position
        if (rockets[i].trail_length > 0) {
            int px = (int)(rockets[i].x * scale + WIDTH / 2);
            int py = (int)(rockets[i].y * scale + HEIGHT / 2);
            
            if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                int radius = 4;
                
                // Draw rocket as bright red circle
                for (int dy = -radius; dy <= radius; dy++) {
                    for (int dx = -radius; dx <= radius; dx++) {
                        if (dx * dx + dy * dy <= radius * radius) {
                            int x = px + dx;
                            int y = py + dy;
                            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                                img[y * WIDTH + x].r = 255;  // Bright red rocket
                                img[y * WIDTH + x].g = 50;
                                img[y * WIDTH + x].b = 50;
                            }
                        }
                    }
                }
                
                // Draw velocity vector as line (shows direction of motion)
                if (rockets[i].active) {
                    double vx_scaled = rockets[i].vx * 5.0;
                    double vy_scaled = rockets[i].vy * 5.0;
                    for (int t = 0; t < 10; t++) {
                        int vx = px + (int)(vx_scaled * t / 10.0);
                        int vy = py + (int)(vy_scaled * t / 10.0);
                        if (vx >= 0 && vx < WIDTH && vy >= 0 && vy < HEIGHT) {
                            img[vy * WIDTH + vx].r = 255;
                            img[vy * WIDTH + vx].g = 255;
                            img[vy * WIDTH + vx].b = 0;
                        }
                    }
                }
            }
        }
    }
}

/* ============================================================================
 * MAIN SIMULATION LOOP
 * ============================================================================ */

int main() {
    // Allocate arrays
    Body bodies[N_BODIES];
    Rocket rockets[N_ROCKETS];
    Pixel *img = (Pixel *)malloc(WIDTH * HEIGHT * sizeof(Pixel));
    
    if (!img) {
        printf("Error: Memory allocation failed\n");
        return 1;
    }
    
    // Initialize simulation
    init_bodies(bodies, N_BODIES);
    init_rockets(rockets, N_ROCKETS);
    
    // Scaling factor: world coordinates to pixels
    double scale = 50.0;
    
    // How many simulation steps between each frame
    int frame_interval = STEPS / FRAMES;
    
    printf("\n");
    printf("====================================\n");
    printf("N-Body Simulation with Rocket Trajectories\n");
    printf("====================================\n");
    printf("Bodies: %d\n", N_BODIES);
    printf("Rockets: %d\n", N_ROCKETS);
    printf("Steps: %d\n", STEPS);
    printf("Frames: %d\n", FRAMES);
    printf("Time step: %.4f\n", DT);
    printf("====================================\n\n");
    
    // Main simulation loop
    for (int step = 0; step < STEPS; step++) {
        // Update physics for one time step
        update_bodies(bodies, N_BODIES, DT);
        update_rockets(rockets, N_ROCKETS, bodies, N_BODIES, DT);
        
        // Generate output frame at regular intervals
        if (step % frame_interval == 0) {
            char filename[50];
            sprintf(filename, "frame_%04d.bmp", step / frame_interval);
            
            // Render current state and save to file
            render(bodies, N_BODIES, rockets, N_ROCKETS, img, scale);
            write_bmp(filename, img, WIDTH, HEIGHT);
            
            printf("Step %5d/%d - Generated %s\n", step, STEPS, filename);
        }
    }
    
    // Clean up
    free(img);
    
    // Free rocket trail memory
    for (int i = 0; i < N_ROCKETS; i++) {
        free(rockets[i].trail_x);
        free(rockets[i].trail_y);
    }
    
    printf("\n====================================\n");
    printf("Simulation complete!\n");
    printf("Generated %d frames\n", FRAMES);
    printf("====================================\n\n");
    
    return 0;
}