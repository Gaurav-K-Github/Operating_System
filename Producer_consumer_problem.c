#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int mutex = 1;
int full = 0;
int empty = SIZE;
int buffer[SIZE];
int in = 0, out = 0;
int count = 0; // For tracking item number

// Semaphore operations
int wait(int s) {
    return --s;
}

int signal(int s) {
    return ++s;
}

// Producer function
void producer() {
    int item;
    printf("Enter item to produce: ");
    scanf("%d", &item);

    mutex = wait(mutex);
    empty = wait(empty);

    count++;
    buffer[in] = item;
    printf("Producer produces the item %d\n", count);
    printf("Item stored is: %d\n", item);

    in = (in + 1) % SIZE;

    full = signal(full);
    mutex = signal(mutex);
}

// Consumer function
void consumer() {
    mutex = wait(mutex);
    full = wait(full);

    count++;

    int item = buffer[out];
    printf("Consumer consumes item: %d item: %d\n", count,item);

    out = (out + 1) % SIZE;

    empty = signal(empty);
    mutex = signal(mutex);
}

int main() {
    int choice;

    while (1) {
        printf("\n1. PRODUCER\n2. CONSUMER\n3. EXIT\n");
        printf("ENTER YOUR CHOICE\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if ((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("BUFFER IS FULL\n");
                break;

            case 2:
                if ((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("BUFFER IS EMPTY\n");
                break;

            case 3:
                exit(0);

            default:
                printf("INVALID CHOICE\n");
        }
    }

    return 0;
}
