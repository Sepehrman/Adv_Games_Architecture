//
//  Semaphore.h
//  MultiThread
//
//  Created by Borna Noureddin
//  Copyright (c) BCIT. All rights reserved.
//

#ifndef Semaphore_h
#define Semaphore_h

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore (int count_ = 0) : count(count_) {}
    
    inline void notify()
    {
        std::lock_guard<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }
    
    inline void wait()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() {return count > 0;} );
        --count;
    }
    
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

#endif
