// producer_consumer.cpp
#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>   // for sleep

const int BUFFER_SIZE = 5;
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty_slots;   // counts available empty slots
sem_t full_slots;    // counts filled slots
sem_t mutex;         // binary semaphore for mutual exclusion

void producer(int id) {
    for (int i = 0; i < 5; i++) { // produce 5 items
        int item = i + 1;  // some item

        sem_wait(&empty_slots);   // wait for empty slot
        sem_wait(&mutex);         // enter critical section

        buffer[in] = item;
        std::cout << "Producer " << id 
                  << " produced " << item 
                  << " at index " << in << "\n";
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);         // leave critical section
        sem_post(&full_slots);    // one more full slot

        sleep(1); // simulate time to produce
    }
}

void consumer(int id) {
    for (int i = 0; i < 5; i++) { // consume 5 items
        sem_wait(&full_slots);    // wait for full slot
        sem_wait(&mutex);         // enter critical section

        int item = buffer[out];
        std::cout << "Consumer " << id 
                  << " consumed " << item 
                  << " from index " << out << "\n";
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);         // leave critical section
        sem_post(&empty_slots);   // one more empty slot

        sleep(1); // simulate time to consume
    }
}

int main() {
    // Initialize semaphores
    sem_init(&empty_slots, 0, BUFFER_SIZE); // all slots empty
    sem_init(&full_slots, 0, 0);            // no full slots initially
    sem_init(&mutex, 0, 1);                 // binary semaphore = 1

    std::thread prod1(producer, 1);
    std::thread cons1(consumer, 1);

    prod1.join();
    cons1.join();

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    sem_destroy(&mutex);

    return 0;
}
