//
//  CMultiThread.cpp
//  MultiThread
//
//  Created by Borna Noureddin
//  Copyright (c) BCIT. All rights reserved.
//

#include "CMultiThread.h"
#include "Semaphore.h"

//### Define mutexes and semaphores
std::mutex mtx;
std::condition_variable cv;
bool onReady = false;

CMultiThread::CMultiThread()
{
    th1 = th2 = NULL;
}

CMultiThread::~CMultiThread()
{
    if (th1) delete th1;
    if (th2) delete th2;
}

double CMultiThread::UniformRandom()
{
    double r = rand();
    r /= (double)RAND_MAX;
    return r;
}

int CMultiThread::RandomInt(int minVal, int maxVal)
{
    double r = UniformRandom();
    return (int)(r * (maxVal - minVal) + minVal);
}



////////////////////////////////////////////////////////////////////////
//
// Two thread synchronization (single resource)
//

void CMultiThread::TwoThreadTestWorkerThread(CMultiThread *th, int n, char c, int sleepTime)
{
    std::chrono::milliseconds timespan(sleepTime);
    std::this_thread::sleep_for(timespan);

    std::lock_guard<std::mutex> guard(mtx);

    //### This function will need some sort of synchronization...
    for (int i=0; i<n; ++i) {

        std::cout << c;
    }

    std::cout << '\n';
}

void CMultiThread::TwoThreadTest()
{
    th1 = new std::thread(TwoThreadTestWorkerThread, this, 500, '*', 0);
    th2 = new std::thread(TwoThreadTestWorkerThread, this, 500, '$', 0);
    th1->join();
    th2->join();


    std::cout << "Completed two thread example!" << std::endl;
}



////////////////////////////////////////////////////////////////////////
//
// Multiple thread synchronization (single resource)
//


void CMultiThread::MultiThreadTestWorkerThread(CMultiThread *th, int num, int max)
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [th, num]{ return th->GetCurrentThreadId() == num && (onReady == true); });

    th->IncrementCurrentThreadId();

    std::cout << "Thread: ";
    std::cout << num + 1 << " / " << max;
    std::cout << " current count is: ";

    std::cout << th->GetCurrentThreadId() << std::endl;

    //### Remember to clean up synchronization...
    lock.unlock();
    cv.notify_all();
}

void CMultiThread::MultiThreadTest()
{
    std::thread *threads = new std::thread[numThreads];

    for (int id = 0; id < numThreads; id++)
        threads[id] = std::thread(MultiThreadTestWorkerThread, this, id, numThreads);

    std::cout << "\nRunning " << numThreads;
    std::cout << " in parallel: \n" << std::endl;

    static std::mutex mtx;
    std::lock_guard<std::mutex> guard(mtx);
    onReady = true;
    cv.notify_all();

    for(int id = 0; id < numThreads; id++)
        threads[id].join();

    std::cout << "\nCompleted multiple threads example!\n";
    std::cout << std::endl;

    delete [] threads;
    current = 0;
}

void CMultiThread::IncrementCurrentThreadId()
{
    current++;
}

int CMultiThread::GetCurrentThreadId()
{
    return current;
}



////////////////////////////////////////////////////////////////////////
//
// Reader-Writer synchronization
//

//  Reader-Writer example
//
// In this classic Reader-Writer problem, there are two threads exchanging
// information through a fixed size buffer. The Writer thread fills the buffer
// with data whenever there's room for more. The Reader thread reads data from
// the buffer and prints it. Both threads have a situation where they should
// block. The writer blocks when the buffer is full and the reader blocks when
// the buffer is empty. The problem is to get them to cooperate nicely and
// block efficiently when necessary.
// Multiple runs will not necessary get the same output, but the reader
// should always list the chars in the same order as the writer and there
// should never be more than 5 writes before a read and vice versa (since
// we only have 5 buffers to use).

void CMultiThread::ReaderWriterTest()
{
   //### This function will need some sort of synchronization...
    std::thread *writerThread = new std::thread(Writer, this);
    std::thread *readerThread = new std::thread(Reader, this);
    writerThread->join();
    readerThread->join();
    std::cout << "\nCompleted Reader-Writer example!\n";
    std::cout << std::endl;
}

void CMultiThread::Writer(CMultiThread *th)
{
    int i, writePt = 0;
    char data;
    //### This function will need some sort of synchronization in the loop...
    for (i = 0; i < DATA_LENGTH; i++) {
        data = th->PrepareData();
        th->buffers[writePt] = data;
        printf("Writer: buffer[%d] = %c\n", writePt, data);
        writePt = (writePt + 1) % NUM_TOTAL_BUFFERS;
    }
}

void CMultiThread::Reader(CMultiThread *th)
{
    int i, readPt = 0;
    char data;
    //### This function will need some sort of synchronization in the loop...
    for (i = 0; i < DATA_LENGTH; i++) {
        data = th->buffers[readPt];
        printf("\t\tReader: buffer[%d] = %c\n", readPt, data);
        readPt = (readPt + 1) % NUM_TOTAL_BUFFERS;
        th->ProcessData(data);
    }
}

void CMultiThread::ProcessData(char data)
{
    std::chrono::milliseconds timespan(RandomInt(0, 500));
    std::this_thread::sleep_for(timespan);
}

char CMultiThread::PrepareData(void)
{
    std::chrono::milliseconds timespan(RandomInt(0, 500));
    std::this_thread::sleep_for(timespan);
    return (char)RandomInt('A', 'Z');
}
