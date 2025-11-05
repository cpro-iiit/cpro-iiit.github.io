/**
 * ============================================================================
 * CONWAY'S GAME OF LIFE - C PROGRAMMING COURSE PROJECT
 * ============================================================================
 * 
 * BACKGROUND:
 * -----------
 * Conway's Game of Life is a cellular automaton devised by British 
 * mathematician John Horton Conway in 1970. It is a zero-player game, 
 * meaning its evolution is determined by its initial state, requiring 
 * no further input from humans.
 * 
 * THE UNIVERSE:
 * -------------
 * The game takes place on an infinite 2D orthogonal grid of square cells.
 * In this implementation, we use a finite grid with fixed boundaries.
 * Each cell can be in one of two states: ALIVE (1) or DEAD (0).
 * 
 * THE RULES:
 * ----------
 * At each step in time (generation), the following transitions occur:
 * 
 * 1. UNDERPOPULATION: Any live cell with fewer than 2 live neighbors dies,
 *    as if by underpopulation.
 * 
 * 2. SURVIVAL: Any live cell with 2 or 3 live neighbors lives on to the 
 *    next generation.
 * 
 * 3. OVERPOPULATION: Any live cell with more than 3 live neighbors dies,
 *    as if by overpopulation.
 * 
 * 4. REPRODUCTION: Any dead cell with exactly 3 live neighbors becomes 
 *    a live cell, as if by reproduction.
 * 
 * NEIGHBORS:
 * ----------
 * Each cell has up to 8 neighbors: the cells that are horizontally, 
 * vertically, or diagonally adjacent. For cells on the edges or corners,
 * some neighbors may be out of bounds.
 * 
 * The 8 neighbor positions relative to a cell at (row, col):
 *     (row-1, col-1)  (row-1, col)  (row-1, col+1)
 *     (row,   col-1)  [CELL]        (row,   col+1)
 *     (row+1, col-1)  (row+1, col)  (row+1, col+1)
 * 
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For usleep() - sleep function for animation

// Grid dimensions
#define ROWS 20
#define COLS 40

// Cell states
#define DEAD 0
#define ALIVE 1

// Display characters
#define DEAD_CHAR '.'
#define ALIVE_CHAR 'O'

// Function prototypes
void initialize_grid(int grid[ROWS][COLS]);
void copy_grid(int src[ROWS][COLS], int dest[ROWS][COLS]);
void display_grid(int grid[ROWS][COLS], int generation);
int count_neighbors(int grid[ROWS][COLS], int row, int col);
void compute_next_generation(int current[ROWS][COLS], int next[ROWS][COLS]);
int grids_equal(int grid1[ROWS][COLS], int grid2[ROWS][COLS]);
void set_pattern_glider(int grid[ROWS][COLS]);
void set_pattern_blinker(int grid[ROWS][COLS]);
void set_pattern_random(int grid[ROWS][COLS]);

/**
 * ============================================================================
 * MAIN FUNCTION
 * ============================================================================
 * This is a complete implementation that ties everything together.
 * It initializes the grid, runs the simulation, and displays each generation.
 */
int main() {
    int current_grid[ROWS][COLS];
    int next_grid[ROWS][COLS];
    int previous_grid[ROWS][COLS];
    int generation = 0;
    int max_generations = 100;
    
    // Initialize the grid with a pattern
    printf("Conway's Game of Life - C Implementation\n");
    printf("========================================\n\n");
    printf("Choose initial pattern:\n");
    printf("1. Glider (moves across the grid)\n");
    printf("2. Blinker (oscillates)\n");
    printf("3. Random\n");
    printf("Enter choice (1-3): ");
    
    int choice;
    scanf("%d", &choice);
    
    initialize_grid(current_grid);
    
    switch(choice) {
        case 1:
            set_pattern_glider(current_grid);
            break;
        case 2:
            set_pattern_blinker(current_grid);
            break;
        case 3:
            set_pattern_random(current_grid);
            break;
        default:
            set_pattern_glider(current_grid);
    }
    
    // Main simulation loop
    while (generation < max_generations) {
        // Clear screen (ANSI escape code - works on Unix/Linux/Mac)
        printf("\033[2J\033[H");
        
        // Display current state
        display_grid(current_grid, generation);
        
        // Store current grid as previous
        copy_grid(current_grid, previous_grid);
        
        // Compute next generation
        compute_next_generation(current_grid, next_grid);
        
        // Check if grid has stabilized (no change) or returned to previous state
        if (grids_equal(current_grid, next_grid)) {
            printf("\nGrid has stabilized! No further changes will occur.\n");
            break;
        }
        
        if (grids_equal(next_grid, previous_grid)) {
            printf("\nGrid is oscillating! Detected a 2-step cycle.\n");
        }
        
        // Copy next generation to current
        copy_grid(next_grid, current_grid);
        
        generation++;
        
        // Pause for animation effect (500ms = 500000 microseconds)
        usleep(500000);
    }
    
    printf("\nSimulation complete! Final generation: %d\n", generation);
    return 0;
}

/**
 * ============================================================================
 * EXERCISE 1: Implement count_neighbors
 * ============================================================================
 * DIFFICULTY: Medium
 * 
 * TASK:
 * Count the number of ALIVE neighbors for the cell at position (row, col).
 * 
 * REQUIREMENTS:
 * - Check all 8 adjacent cells (horizontal, vertical, and diagonal)
 * - Handle edge cases: cells on boundaries have fewer neighbors
 * - Return a count between 0 and 8
 * 
 * APPROACH:
 * 1. Use nested loops to check all 8 directions around the cell
 * 2. For each direction, check if the neighbor is within grid bounds
 * 3. If the neighbor is ALIVE, increment the counter
 * 
 * HINT: You can use direction arrays to simplify the code:
 *       int dr[] = {-1, -1, -1,  0, 0,  1, 1, 1};  // row deltas
 *       int dc[] = {-1,  0,  1, -1, 1, -1, 0, 1};  // col deltas
 * 
 * TESTING:
 * - Corner cell (0,0) should have at most 3 neighbors
 * - Edge cell (0,5) should have at most 5 neighbors
 * - Center cell (10,20) should have 8 neighbors to check
 * 
 * @param grid - The current state of the game grid
 * @param row  - Row index of the cell to check
 * @param col  - Column index of the cell to check
 * @return     - Number of alive neighbors (0-8)
 */
int count_neighbors(int grid[ROWS][COLS], int row, int col) {
    int count = 0;
    
    // TODO: Implement this function
    // Your code here...
    
    // STUDENT IMPLEMENTATION AREA - DELETE THIS COMMENT AND IMPLEMENT
    
    return count;
}

/**
 * ============================================================================
 * EXERCISE 2: Implement compute_next_generation
 * ============================================================================
 * DIFFICULTY: Hard
 * 
 * TASK:
 * Apply Conway's Game of Life rules to compute the next generation.
 * 
 * REQUIREMENTS:
 * - Iterate through every cell in the grid
 * - Count neighbors for each cell using count_neighbors()
 * - Apply the four rules to determine if each cell lives or dies
 * - Store results in the 'next' grid (don't modify 'current' in place!)
 * 
 * THE FOUR RULES (reminder):
 * 1. Live cell with < 2 live neighbors → dies (underpopulation)
 * 2. Live cell with 2-3 live neighbors → lives (survival)
 * 3. Live cell with > 3 live neighbors → dies (overpopulation)
 * 4. Dead cell with exactly 3 live neighbors → becomes alive (reproduction)
 * 
 * PSEUDOCODE:
 * for each row:
 *     for each col:
 *         neighbors = count_neighbors(current, row, col)
 *         if current[row][col] is ALIVE:
 *             if neighbors < 2 or neighbors > 3:
 *                 next[row][col] = DEAD
 *             else:
 *                 next[row][col] = ALIVE
 *         else:  // cell is DEAD
 *             if neighbors == 3:
 *                 next[row][col] = ALIVE
 *             else:
 *                 next[row][col] = DEAD
 * 
 * CRITICAL: Do NOT modify the 'current' grid. Only write to 'next' grid.
 *          This is because we need to compute all cells based on the same
 *          generation state.
 * 
 * @param current - The current generation grid (input)
 * @param next    - The next generation grid (output)
 */
void compute_next_generation(int current[ROWS][COLS], int next[ROWS][COLS]) {
    // TODO: Implement this function
    // Your code here...
    
    // STUDENT IMPLEMENTATION AREA - DELETE THIS COMMENT AND IMPLEMENT
}

/**
 * ============================================================================
 * EXERCISE 3: Implement grids_equal
 * ============================================================================
 * DIFFICULTY: Easy
 * 
 * TASK:
 * Compare two grids to check if they are identical.
 * This is used to detect when the simulation has reached a stable state.
 * 
 * REQUIREMENTS:
 * - Compare every cell in both grids
 * - Return 1 (true) if all cells are equal
 * - Return 0 (false) if any cell differs
 * 
 * OPTIMIZATION HINT:
 * You can return 0 immediately when you find the first difference.
 * No need to check remaining cells if you already found a difference.
 * 
 * @param grid1 - First grid to compare
 * @param grid2 - Second grid to compare
 * @return      - 1 if grids are equal, 0 otherwise
 */
int grids_equal(int grid1[ROWS][COLS], int grid2[ROWS][COLS]) {
    // TODO: Implement this function
    // Your code here...
    
    // STUDENT IMPLEMENTATION AREA - DELETE THIS COMMENT AND IMPLEMENT
    
    return 0;  // Placeholder return
}

/**
 * ============================================================================
 * HELPER FUNCTIONS (Already Implemented)
 * ============================================================================
 * These functions are provided to help you test your implementation.
 * You don't need to modify them, but you should understand how they work.
 */

/**
 * Initialize all cells in the grid to DEAD state.
 */
void initialize_grid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = DEAD;
        }
    }
}

/**
 * Copy contents from source grid to destination grid.
 * This is necessary because we need to keep track of previous states.
 */
void copy_grid(int src[ROWS][COLS], int dest[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

/**
 * Display the grid in a visually appealing format.
 * Shows generation number and grid with border.
 */
void display_grid(int grid[ROWS][COLS], int generation) {
    printf("Generation: %d\n", generation);
    printf("\n");
    
    // Top border
    printf("+");
    for (int j = 0; j < COLS; j++) printf("-");
    printf("+\n");
    
    // Grid contents
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            printf("%c", grid[i][j] == ALIVE ? ALIVE_CHAR : DEAD_CHAR);
        }
        printf("|\n");
    }
    
    // Bottom border
    printf("+");
    for (int j = 0; j < COLS; j++) printf("-");
    printf("+\n");
}

/**
 * PATTERN: Glider
 * A small pattern that "glides" diagonally across the grid.
 * This is one of the most famous patterns in Game of Life.
 * 
 * Pattern shape:
 *   .O.
 *   ..O
 *   OOO
 */
void set_pattern_glider(int grid[ROWS][COLS]) {
    int start_row = 1;
    int start_col = 1;
    
    grid[start_row][start_col + 1] = ALIVE;
    grid[start_row + 1][start_col + 2] = ALIVE;
    grid[start_row + 2][start_col] = ALIVE;
    grid[start_row + 2][start_col + 1] = ALIVE;
    grid[start_row + 2][start_col + 2] = ALIVE;
}

/**
 * PATTERN: Blinker
 * An oscillator that alternates between horizontal and vertical.
 * Period: 2 (returns to original state every 2 generations)
 * 
 * Pattern shapes:
 * State 1:  OOO    State 2:  .O.
 *                            .O.
 *                            .O.
 */
void set_pattern_blinker(int grid[ROWS][COLS]) {
    int row = ROWS / 2;
    int col = COLS / 2;
    
    grid[row][col - 1] = ALIVE;
    grid[row][col] = ALIVE;
    grid[row][col + 1] = ALIVE;
}

/**
 * PATTERN: Random
 * Fills approximately 20% of the grid with random live cells.
 * Results in unpredictable and interesting patterns.
 */
void set_pattern_random(int grid[ROWS][COLS]) {
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // 20% chance of being alive
            grid[i][j] = (rand() % 100 < 20) ? ALIVE : DEAD;
        }
    }
}

/**
 * ============================================================================
 * BONUS EXERCISES (Optional Challenges)
 * ============================================================================
 * 
 * BONUS 1: Implement toroidal wrapping
 * Modify the grid so that edges wrap around (top connects to bottom,
 * left connects to right). This creates an infinite grid topology.
 * Hint: Use modulo operator (%) to wrap coordinates.
 * 
 * BONUS 2: Add more patterns
 * Implement these famous patterns:
 * - Toad (period-2 oscillator)
 * - Beacon (period-2 oscillator)
 * - Pulsar (period-3 oscillator)
 * - Gosper Glider Gun (produces gliders indefinitely)
 * 
 * BONUS 3: Grid statistics
 * Track and display statistics:
 * - Total alive cells per generation
 * - Birth rate (new cells born)
 * - Death rate (cells that died)
 * - Population density
 * 
 * BONUS 4: Save/Load functionality
 * Implement functions to:
 * - Save grid state to a file
 * - Load grid state from a file
 * - Allow pausing and resuming simulation
 * 
 * BONUS 5: Interactive mode
 * Add user interaction:
 * - Click cells to toggle alive/dead
 * - Step forward one generation at a time
 * - Adjust simulation speed
 * 
 * ============================================================================
 */