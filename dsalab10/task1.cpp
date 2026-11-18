#include <iostream>
using namespace std;

class MaxHeap {
private:
    int* arr;      // dynamic array
    int size;      // number of elements currently in the heap
    int capacity;  // total space in the array
    void grow() {
        capacity = capacity * 2;
        int* bigger = new int[capacity];
        for (int i = 0; i < size; i++)
            bigger[i] = arr[i];
        delete[] arr;
        arr = bigger;
    }

public:
    MaxHeap(int cap = 4) {
        capacity = cap;
        size = 0;
        arr = new int[capacity];
    }

    ~MaxHeap() {
        delete[] arr;
    }

    // Insert at the end, then move it up while it is bigger than its parent
    int insert(int value) {
        if (size == capacity)
            grow();

        arr[size] = value;
        int i = size;
        size++;

        int swaps = 0;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (arr[i] > arr[parent]) {
                int temp = arr[i];
                arr[i] = arr[parent];
                arr[parent] = temp;
                i = parent;
                swaps++;
            } else {
                break;
            }
        }
        return swaps;
    }

    void printHeap() {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    // Heap sort on a COPY, so the original max heap stays unchanged
    void heapSort() {
        int n = size;
        int* a = new int[n];
        for (int i = 0; i < n; i++)
            a[i] = arr[i];

        // Repeat: swap the max (root) with the last element, shrink the heap, fix the root
        for (int end = n - 1; end > 0; end--) {
            int temp = a[0];
            a[0] = a[end];
            a[end] = temp;

            // sift down the new root within a[0..end-1]
            int i = 0;
            while (true) {
                int left = 2 * i + 1;
                int right = 2 * i + 2;
                int largest = i;

                if (left < end && a[left] > a[largest])
                    largest = left;
                if (right < end && a[right] > a[largest])
                    largest = right;

                if (largest == i)
                    break;

                int t = a[i];
                a[i] = a[largest];
                a[largest] = t;
                i = largest;
            }
        }

        cout << "Sorted output: ";
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl;

        delete[] a;
    }
};

int main() {
    MaxHeap heap;
    int values[] = {25, 40, 15, 60, 35, 10, 70, 50};
    int n = 8;

    for (int i = 0; i < n; i++) {
        int swaps = heap.insert(values[i]);
        cout << "Insert: " << values[i]
             << " | Swaps: " << swaps
             << " | Heap: ";
        heap.printHeap();
    }

    cout << "\nFinal max heap: ";
    heap.printHeap();

    heap.heapSort();

    return 0;
}


/*
Q1. What is the worst-case number of swaps for one insertion into a heap of n elements?
Answer: The new element can move up from the last level to the root, so the swaps
are at most the height of the heap = floor(log2(n+1)). That is O(log n).

Q2. What is the time complexity of building the heap by n insertions, and of heap sort?
Answer: Building by n insertions: each insertion is O(log n), so total O(n log n).
Heap sort: n removals, each with a sift-down of O(log n), so O(n log n).
(Heap sort total including building: O(n log n).)
*/

