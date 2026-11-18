# CPE2600_Fractal_Lab
Labs 11 and 12 for systems programming

## Lab 11: Multi-processing

Compile using makefile (make command)

Run with ./mandelmovie -p maxProcesses

### Implementation

The program starts by parsing the -p argument to determine the largest amount of processes it should run at a time. Then, a semaphore is opened, starting at this value. The main program waits for the semaphore before making a child that executes the mandel program. This happens 50 times so that 50 images are created.

### Time vs. Processes Graph

![Time vs. Number of Processes Graph](Time_v_Processes.png)

The graph shows a very large speedup when going from 1 to 2 processes and 2 to 5 processes. By 10 processes the points start to settle and hover around 30 seconds.