// Binary Search with concurrency.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

bool binarySearch(int* ar, int startingIndex, int endingIndex, int element, int* solution) {

    cout << "Thread Id for this thread is " << this_thread::get_id() << endl;
    while (startingIndex <= endingIndex) {
        int mid = startingIndex + (endingIndex - startingIndex) / 2;
        if (ar[mid] == element) {
            *solution = mid;
            return true;
        }
        else if (ar[mid] > element) {
            endingIndex = mid - 1;
        }
        else {
            startingIndex = mid + 1;
        }
    }
    return false;
}
int main()
{
    int noOfElements;
    cout << "Enter no of elements ";
    cin >> noOfElements;

    int threadSize;
    cout <<endl<< "Enter no of elements which need to processed in one thread ";
    cin >> threadSize;

    int* input = new int[noOfElements];
    cout << "Enter element ";
    for (int i = 0; i < noOfElements; i++) {
        cin >> input[i];
    }

    int element;
    cout << endl << "What element to be searched ";
    cin >> element;

    vector<thread> threads;
    vector<int> threadresult(threadSize,-1);

    int noOfElementsInAThread = noOfElements / threadSize;
    for (int i = 0; i < threadSize; i++) {
        threads.push_back(thread(binarySearch, input, i * noOfElementsInAThread, (i == threadSize - 1) ? noOfElements - 1 : ((i + 1) * noOfElementsInAThread) - 1, element,&threadresult[i]));
    }

    for (int i = 0; i < threadSize; i++) {
        threads[i].join();

        if (threadresult[i] != -1) {
            cout << "element found at index " << threadresult[i] << endl;
        }
    }
    return 0;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

/*
Sample testcase 
16
3
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16


*/