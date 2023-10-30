/*
Parallel Summation:
   Write a program that calculates the sum of a large array of numbers using multiple threads.
   Each thread should work on a subset of the array, and the results should be combined at the end.

*/

#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <atomic>

#define mod 1000000007

using namespace std;
long long sum = 0;
mutex gLock;

void arraySum(int* ar, int startingIndex, int endingIndex) {
    long long localSum = 0;

    for (int i = startingIndex; i <= endingIndex; i++) {
        localSum += ar[i];
        localSum = localSum % mod;
    }

    gLock.lock();
    try {
        sum += localSum;
    }
    catch(const exception& e){
        cout << "Handling unwanted exception "<<e.what()<<endl;
        gLock.unlock();
        return;
    }
    gLock.unlock();

    // Instead of manually locking , we can also use lock_guard 
    // lock_guard provides extra precaution and releases the lock whenever it goes 
    // out of scope, hence less chance of going into a deadlock

    cout << "current thread id is " << this_thread::get_id() << endl;
}

int main() {
    int bucketSize;
    cout << "Please input the bucketSize for one thread";
    cin >> bucketSize;

    vector<thread> threads;

    int noOfElements;
    cout << endl << "Enter number of elements";
    cin >> noOfElements;

    cout << endl << "Enter elements";
    int* input = new int[noOfElements];
    for (int i = 0; i < noOfElements; i++) {
        cin >> input[i];
    }

    int noOfThreads = ceil(noOfElements / (double)bucketSize);

    for (int i = 0; i < noOfThreads; i++) {
        threads.push_back(thread(arraySum, input, i * bucketSize, (((i + 1) * bucketSize - 1)>noOfElements-1 ) ?noOfElements-1: (i + 1) * bucketSize - 1));
    }

    for (int i = 0; i < noOfThreads; i++) {
        threads[i].join();
    }

    this_thread::sleep_for(chrono::seconds(2));

    // Now, print the synchronized sum
    gLock.lock();
    cout << sum;
    gLock.unlock();

    delete[] input; // Clean up the allocated memory

    return 0;
}
