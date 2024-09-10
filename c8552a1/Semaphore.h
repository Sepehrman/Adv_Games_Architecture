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
        //### Use unique_lock to lock a resource
    }
    
    inline void wait()
    {
        //### Use unique_lock to lock a resource
    }
    
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

#endif
