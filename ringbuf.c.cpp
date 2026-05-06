#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 8   // Must be power of 2 for bonus optimization

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} RingBuffer;

// Initialize buffer
void init(RingBuffer *rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

// Check full
bool isFull(RingBuffer *rb) {
    return rb->count == BUFFER_SIZE;
}

// Check empty
bool isEmpty(RingBuffer *rb) {
    return rb->count == 0;
}

// Get count
int getCount(RingBuffer *rb) {
    return rb->count;
}

// Write to buffer
bool write(RingBuffer *rb, uint8_t data) {
    if (isFull(rb)) {
        return false; // buffer full
    }

    rb->buffer[rb->head] = data;

    // BONUS: faster than %
    rb->head = (rb->head + 1) & (BUFFER_SIZE - 1);

    rb->count++;
    return true;
}

// Read from buffer
bool read(RingBuffer *rb, uint8_t *data) {
    if (isEmpty(rb)) {
        return false; // buffer empty
    }

    *data = rb->buffer[rb->tail];

    // BONUS: faster than %
    rb->tail = (rb->tail + 1) & (BUFFER_SIZE - 1);

    rb->count--;
    return true;
}

// Main demonstration
int main() {
    RingBuffer rb;
    init(&rb);

    uint8_t data;

    // Step 1: Write 8 bytes (0x41 to 0x48)
    for (int i = 0; i < 8; i++) {
        if (write(&rb, 0x41 + i))
            printf("[WRITE] 0x%X -> OK (count=%d)%s\n",
                   0x41 + i,
                   getCount(&rb),
                   isFull(&rb) ? " FULL" : "");
    }

    // Step 2: Try writing extra (should fail)
    if (!write(&rb, 0x99))
        printf("[WRITE] 0x99 -> FAIL (buffer full)\n");

    // Step 3: Read 3 bytes
    for (int i = 0; i < 3; i++) {
        if (read(&rb, &data))
            printf("[READ] -> 0x%X (count=%d)\n", data, getCount(&rb));
    }

    // Step 4: Write 3 new bytes (0x49, 0x4A, 0x4B)
    for (int i = 0; i < 3; i++) {
        if (write(&rb, 0x49 + i))
            printf("[WRITE] 0x%X -> OK (count=%d)\n",
                   0x49 + i,
                   getCount(&rb));
    }

    // Step 5: Read all remaining bytes
    while (!isEmpty(&rb)) {
        read(&rb, &data);
        printf("[READ] -> 0x%X (count=%d)\n", data, getCount(&rb));
    }

    // Step 6: Read from empty (should fail)
    if (!read(&rb, &data))
        printf("[READ] (empty) -> FAIL (buffer empty)\n");

    return 0;
}
