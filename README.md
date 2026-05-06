# Ring Buffer Assignment

Name: Akanksha Pandhrinath Harde

This project is a circular buffer (ring buffer) implemented in C.

Features:
- Write data
- Read data
- Check full and empty
- Buffer size = 8

Compile:
gcc -Wall -std=c99 ringbuf.c -o ringbuf

Run:
./ringbuf

Output:
Program shows writing, reading, full and empty conditions.

Bonus:
Used & (BUFFER_SIZE - 1) instead of % for faster operation.