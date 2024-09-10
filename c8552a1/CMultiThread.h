//
//  CMultiThread.h
//  MultiThread
//
//  Created by Borna Noureddin
//  Copyright (c) BCIT. All rights reserved.
//

#ifndef __MultiThread__CMultiThread__
#define __MultiThread__CMultiThread__

#include <stdio.h>
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <condition_variable>

#define NUM_TOTAL_BUFFERS 5
#define DATA_LENGTH 20


class CMultiThread
{
public:
    CMultiThread();
    ~CMultiThread();
    double UniformRandom();
    int RandomInt(int minVal, int maxVal);
    
    static void TwoThreadTestWorkerThread(CMultiThread *th, int n, char c, int sleepTime);
    void TwoThreadTest();
    int GetCurrentThreadId();
    void IncrementCurrentThreadId();
    static void MultiThreadTestWorkerThread(CMultiThread *th, int num, int max);
    void MultiThreadTest();
    static void Writer(CMultiThread *th);
    static void Reader(CMultiThread *th);
    void ProcessData(char data);
    char PrepareData();
    void ReaderWriterTest();
    
private:
    std::thread *th1;
    std::thread *th2;
    const int numThreads = 15;
    int current;
    char buffers[NUM_TOTAL_BUFFERS];
};

#endif /* defined(__MultiThread__CMultiThread__) */
