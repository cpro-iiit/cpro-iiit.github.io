---
title: "L24: Rocket Trajectories in the Solar System"
bookHidden: false
marp: true
header: 'CS0.101 Computer Programming (Monsoon 25)'
revealjs_config:
  slideNumber: true
---

# Rocket Trajectories in the Solar System

In this lecture, we will go over a program that computes the trajectory of rockets in a solar system.

---

Please go over the code in : [main.c](./main.c)

Read about BMP image files: https://en.wikipedia.org/wiki/BMP_file_format 

Try the following:
- Modularize the code into a multifile program
- Add a Makefile
- Implement the File I/O features described bellow.

---

# 🚀 C Programming Exercises: Rocket Simulation & File I/O

These exercises build on the given rocket trajectory simulation program.
Each problem focuses on adding new functionality that requires students to use C file I/O (text and binary) effectively.

## 🧩 Part 1: Input Extensions
### Exercise 1.1 — Load Body Parameters from a File

Goal: Replace the hard-coded initialization of celestial bodies with data read from a text file.

File format (bodies.txt):

```
# x  y   vx  vy   mass
0.0 0.0  0.0 0.0  100.0
2.0 0.0  0.0 0.8  5.0
-2.0 0.0  0.0 -0.8  5.0
...
```


Tasks:

- Write a function int `load_bodies(const char *filename, Body *bodies, int max_bodies);`

- Open the file and read lines into the bodies array.

- Ignore lines starting with `#`.

- Return the number of bodies successfully loaded.

- Modify main() to call this function instead of init_bodies().

- Handle file-not-found errors gracefully.

### Exercise 1.2 — Initialize Rockets from a File

Goal: Allow flexible rocket starting conditions.

File format (rockets.txt):
```
# x  y   vx   vy
-8.0 -6.0 0.000005 0.000004
-6.0  5.0 0.000005 -0.000004
```


Tasks:

- Implement `int load_rockets(const char *filename, Rocket *rockets, int max_rockets);`

- Modify `init_rockets()` to use this function if a file exists; otherwise fall back to default initialization.

- Print loaded rockets to the console for verification.

## 💾 Part 2: Output Extensions
### Exercise 2.1 — Save Final Rocket Positions

Goal: Write final rocket positions and velocities to a text file after the simulation.

Tasks:

- Create a function:

`void save_rocket_data(const char *filename, Rocket *rockets, int n);`


It should write:
```
Rocket_ID   Final_X   Final_Y   Final_VX   Final_VY   Trail_Length
```

Call this function at the end of the simulation (e.g., `save_rocket_data("final_rockets.txt", rockets, N_ROCKETS);`).

### Exercise 2.2 — Save Rocket Trajectories in Binary Format

Goal: Store all positions in binary for later analysis or visualization.

Tasks:

- Implement:

`void save_rocket_trails_bin(const char *filename, Rocket *rockets, int n);`

- Store `trail_length` followed by `(x, y)` pairs for each rocket.

- Use `fwrite()` for efficient binary output.

- Add a separate program `analyze_trails.c` that: 
  - Reads this binary file.
  - Computes total trajectory length and prints summary statistics.

### Exercise 2.3 — Frame Metadata Log

Goal: Maintain a log file that records when each BMP frame was generated.

Tasks:

- Before the main loop, open `frames.log` in write mode.

- During rendering:

Append a line:

`Frame 12: Step 600, Rocket0_Pos (-1.24, 3.98)`

- Include timestamp using time.h if you want bonus points.

- Close the file at the end.

## 📈 Part 3: Analysis Extensions
### Exercise 3.1 — Trajectory Summary Statistics

Goal: Write summary information for each rocket into a CSV file.

Output format (rocket_stats.csv):
```
RocketID,TrailLength,FinalDistance,MaxDistance,AverageSpeed
0,3200,45.7,48.9,0.032
1,2500,22.1,40.2,0.028
```

Hints:

- FinalDistance = sqrt(x² + y²) at last point.

- AverageSpeed = total_distance / simulation_time.

### Exercise 3.2 — Reload and Plot Trails

Goal: Read the stored binary or text trajectory file and re-render them into a new BMP image (without re-running simulation).

Tasks:

- Implement a standalone program `plot_trails.c`.

- It should:

  - Read rocket trail data from file.

  - Use the same `render()` and `write_bmp()` functions to visualize the loaded trails.

## 🧠 Challenge Exercises (Advanced)
### Exercise 4.1 — Combine File I/O and User Interaction

Let users choose between:

Running a new simulation (N)

Loading and re-plotting saved data (L)

Use scanf() to read the user choice and perform appropriate file I/O.

### Exercise 4.2 — Save Simulation Parameters

Write a function save_metadata() to record:
```
Width, Height, Steps, DT, G, N_Bodies, N_Rockets
```

and other constants into a metadata.txt file.
Students can then write a corresponding load_metadata() function that rebuilds the same configuration later.

### Exercise 4.3 — Implement a Configurable Save Interval

Currently, frames are saved every frame_interval.
Modify the code so that the interval can be read from a config file:

```
dt=0.01
frames=200
save_interval=50
```

---
## Solution Repository

https://github.com/cpro-iiit/rocket_sim 


---