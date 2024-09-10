#include <iostream>
#include "CMultiThread.h"

int main(int argc, char *argv[])
{
    CMultiThread *threadObj;

    threadObj = new CMultiThread;
    if (threadObj == NULL) {
        std::cerr << "Could not create thread object!" << std::endl;
    } else {
        std::cout << std::endl << std::endl << "Two Thread Test:" << std::endl;
        threadObj->TwoThreadTest();
        std::cout << std::endl << std::endl << std::endl << "Multiple Thread Test:" << std::endl;
        threadObj->MultiThreadTest();
        std::cout << std::endl << std::endl << std::endl << "Reader-Writer Test:" << std::endl;
        threadObj->ReaderWriterTest();
    }

    if (threadObj) {
        delete threadObj;
        threadObj = NULL;
    }

    return 0;
}
