#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

int sharedData = 0;

void writerFunction() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        
        sharedData = i;
        std::cout << "Поток записи написал: " << sharedData << std::endl;
        
        mtx.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void readerFunction() {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        
        std::cout << "Поток чтения прочитал: " << sharedData << std::endl;
        
        mtx.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::thread writerThread(writerFunction);
    std::thread readerThread(readerFunction);
    
    writerThread.join();
    readerThread.join();
}
