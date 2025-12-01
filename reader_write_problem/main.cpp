#include <iostream>
#include <thread>
#include <mutex>

int shared_data = 0;
int read_count = 0;

std::mutex mutex_readcount;   // protects read_count
std::mutex write_lock;        // ensures writers get exclusive access
std::mutex print_lock; // protects std::cout

void reader(int id) {
    // Entry Section
    mutex_readcount.lock();
    read_count++;
    if (read_count == 1) {
        write_lock.lock();    // first reader blocks writers
    }
    mutex_readcount.unlock();

    // Critical Section (Reading)
    {
        std::lock_guard<std::mutex> guard(print_lock);
        std::cout << "Reader " << id << " reads shared_data = " << shared_data << "\n";
    }

    // Exit Section
    mutex_readcount.lock();
    read_count--;
    if (read_count == 0) {
        write_lock.unlock();  // last reader releases writer lock
    }
    mutex_readcount.unlock();
}

void writer(int id) {
    // Entry Section
    write_lock.lock();

    // Critical Section (Writing)

    shared_data++;
    {
        std::lock_guard<std::mutex> guard(print_lock);
        std::cout << "Writer " << id << " updates shared_data to " << shared_data << "\n";
    }

    // Exit Section
    write_lock.unlock();
}

int main() {
    std::thread r1(reader, 1);
    std::thread r2(reader, 2);
    std::thread w1(writer, 1);
    std::thread r3(reader, 3);
    std::thread w2(writer, 2);

    r1.join();
    r2.join();
    w1.join();
    r3.join();
    w2.join();

    return 0;
}
