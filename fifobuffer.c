#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data1;
    int data2;
} Entry;

typedef struct {
    Entry *buffer;
    int size;
    int front;
    int rear;
} FifoBuffer;

FifoBuffer* createFifoBuffer(int size) {
    FifoBuffer* fifo = (FifoBuffer*)malloc(sizeof(FifoBuffer));
    fifo->buffer = (Entry*)malloc(size * sizeof(Entry));
    fifo->size = size;
    fifo->front = 0;
    fifo->rear = 0;
    return fifo;
}

void enqueue(FifoBuffer* fifo, Entry entry) {
    fifo->buffer[fifo->rear] = entry;
    fifo->rear = (fifo->rear + 1) % fifo->size;
}

Entry dequeue(FifoBuffer* fifo) {
    Entry entry = fifo->buffer[fifo->front];
    fifo->front = (fifo->front + 1) % fifo->size;
    return entry;
}

int main() {
    FifoBuffer* fifo = createFifoBuffer(5);

    // Enqueue some entries
    Entry entry1 = {1, 2};
    Entry entry2 = {3, 4};
    Entry entry3 = {5, 6};
    enqueue(fifo, entry1);
    enqueue(fifo, entry2);
    enqueue(fifo, entry3);

    // Dequeue when condition is met
    while (fifo->front != fifo->rear) {
        Entry currentEntry = dequeue(fifo);
        if (currentEntry.data1 + currentEntry.data2 >= 8) {
            printf("Condition met: %d + %d >= 8\n", currentEntry.data1, currentEntry.data2);
            // Process the entry further...
        } else {
            printf("Condition not met: %d + %d < 8\n", currentEntry.data1, currentEntry.data2);
        }
    }

    // Clean up
    free(fifo->buffer);
    free(fifo);

    return 0;
}
