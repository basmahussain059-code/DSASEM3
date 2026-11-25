#include <iostream>
using namespace std;

int totalSize = 0;
bool showSteps = false;

void printArray(int arr[], int n) {
    cout << "{ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << " }";
}

void merge(int arr[], int low, int mid, int high);
void mergeSort(int arr[], int low, int high);

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    // temporary arrays
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = low;

    // merge both halves
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // copy remaining elements
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    delete[] L;
    delete[] R;

    if (showSteps) {
        cout << "Merged [" << low << ".." << high << "] -> ";
        printArray(arr, totalSize);
        cout << endl;
    }
}

void mergeSort(int arr[], int low, int high) {
    // base case
    if (low >= high) {
        return;
    }

    int mid = low + (high - low) / 2;

    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void runTest(const char* name, int arr[], int n) {
    cout << name << "\nBefore: ";
    printArray(arr, n);
    cout << endl;

    mergeSort(arr, 0, n - 1);

    cout << "After:  ";
    printArray(arr, n);
    cout << "\n\n";
}

int main() {
    // main test with trace
    int mainArr[] = {35, 12, 43, 8, 51, 27, 19};
    int n = 7;

    cout << "=== Main Test: {35, 12, 43, 8, 51, 27, 19} ===\n";
    cout << "Initial Array: ";
    printArray(mainArr, n);
    cout << "\n\n";

    totalSize = n;
    showSteps = true;
    mergeSort(mainArr, 0, n - 1);
    showSteps = false;

    cout << "\nFinal Sorted Array: ";
    printArray(mainArr, n);
    cout << "\n\n";

    // boundary cases
    cout << "=== Boundary Cases ===\n";

    int sortedArr[] = {1, 2, 4, 5, 8};
    runTest("1. Already Sorted", sortedArr, 5);

    int reverseArr[] = {8, 5, 4, 2, 1};
    runTest("2. Reverse Sorted", reverseArr, 5);

    int repeatedArr[] = {5, 2, 5, 1, 2};
    runTest("3. Repeated Values", repeatedArr, 5);

    int singleArr[] = {42};
    runTest("4. Single Element (n = 1)", singleArr, 1);

    int* emptyArr = nullptr;
    runTest("5. Empty Array (n = 0)", emptyArr, 0);

    return 0;
}