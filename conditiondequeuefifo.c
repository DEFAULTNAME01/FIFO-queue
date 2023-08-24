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
    int isEmpty;
} FifoBuffer;

FifoBuffer* createFifoBuffer(int size) {
    FifoBuffer* fifo = (FifoBuffer*)malloc(sizeof(FifoBuffer));
    fifo->buffer = (Entry*)malloc(size * sizeof(Entry));
    fifo->size = size;
    fifo->front = 0;
    fifo->rear = 0;
    fifo->isEmpty = 1;  // Initially, the FIFO is empty
    return fifo;
}

int enqueue(FifoBuffer* fifo, Entry entry) {
    if ((fifo->rear + 1) % fifo->size == fifo->front && !fifo->isEmpty) {
        printf("Queue is full! Cannot enqueue.\n");
        return 0;  // Enqueue failed
    }

    fifo->buffer[fifo->rear] = entry;
    fifo->rear = (fifo->rear + 1) % fifo->size;
    fifo->isEmpty = 0;
    return 1;  // Enqueue successful
}


int dequeue(FifoBuffer* fifo, Entry* outEntry) {
    if (fifo->front == fifo->rear && fifo->isEmpty) {
        printf("Queue is empty! Cannot dequeue.\n");
        return 0;  // Queue is empty
    }
    
    int start = fifo->front; // To ensure we don't loop forever

    do {
        *outEntry = fifo->buffer[fifo->front];
        fifo->front = (fifo->front + 1) % fifo->size;  
        if (fifo->front == fifo->rear) {
            fifo->isEmpty = 1;
        }

        // Check if the data is valid based on your criteria and print
        if (outEntry->data1 + outEntry->data2 >= 8) {
            printf("Condition met: %d + %d >= 8\n", outEntry->data1, outEntry->data2);
            return 1;  // Found an entry that satisfies the condition
        } else {
            if (fifo->front == start) {
                printf("No entry met the condition!\n");
                return -1; // Scanned the whole queue and didn't find a satisfying entry
            }
        }
    } while (fifo->front != start);

    return -1; // Shouldn't reach here, but added as a precaution
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

   // Dequeue for n times or until the queue is empty
    const int n = 4;  
    Entry currentEntry;
    int result;
    for (int i = 0; i < n; i++) {
        result = dequeue(fifo, &currentEntry);
        if (result <= 0) { // Queue is empty or no entry met the condition
            break;
        }
        // Further process the entry if required...
    }

    // Clean up
    free(fifo->buffer);
    free(fifo);

    return 0;
}
