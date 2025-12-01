// reader_writer.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

int shared_data = 0;          // shared resource
int read_count = 0;           // number of active readers

std::mutex mutex_readcount;   // protects read_count
std::mutex write_lock;        // ensures exclusive writer access
std::mutex print_lock;        // protects std::cout

void reader(int id) {
    // Entry section for reader
    mutex_readcount.lock();
    read_count++;
    if (read_count == 1) {
        // first reader locks writer
        write_lock.lock();
    }
    mutex_readcount.unlock();

    // Critical section (reading)
    {
        std::lock_guard<std::mutex> guard(print_lock);
        std::cout << "Reader " << id 
                  << " is reading shared_data = " << shared_data 
                  << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate reading

    // Exit section for reader
    mutex_readcount.lock();
    read_count--;
    if (read_count == 0) {
        // last reader unlocks writer
        write_lock.unlock();
    }
    mutex_readcount.unlock();
}

void writer(int id) {
    // Entry section for writer
    write_lock.lock();

    // Critical section (writing)
    shared_data++;
    {
        std::lock_guard<std::mutex> guard(print_lock);
        std::cout << "Writer " << id 
                  << " updated shared_data to " << shared_data 
                  << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate writing

    // Exit section for writer
    write_lock.unlock();
}

int main() {
    const int NUM_READERS = 5;
    const int NUM_WRITERS = 3;

    std::vector<std::thread> readers;
    std::vector<std::thread> writers;

    // Create reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        readers.emplace_back(reader, i + 1);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writers.emplace_back(writer, i + 1);
    }

    // Join reader threads
    for (auto& t : readers) {
        t.join();
    }

    // Join writer threads
    for (auto& t : writers) {
        t.join();
    }

    return 0;
}
