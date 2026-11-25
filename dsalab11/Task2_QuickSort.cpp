#include <iostream>
#include <utility>
using namespace std;

int comparisons = 0;     // counts arr[j] <= pivot checks
bool showSteps = false;  // turns the trace on or off
int totalSize = 0;       // size of the array being traced

void printArray(int arr[], int n) {
    cout << "{ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << " }";
}

// Lomuto partition: last element is the pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1; 

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // put pivot between the two regions
    swap(arr[i + 1], arr[high]);
    int pi = i + 1;

    if (showSteps) {
        cout << "Pivot = " << pivot << ", pi = " << pi << " -> ";
        printArray(arr, totalSize);
        cout << endl;
    }
    return pi;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);   // left of pivot
        quickSort(arr, pi + 1, high);  // right of pivot
    }
}

// sorts with a step-by-step trace
void traceTest(const char* name, int arr[], int n) {
    cout << name << "\nInitial: ";
    printArray(arr, n);
    cout << "\n";

    totalSize = n;
    showSteps = true;
    quickSort(arr, 0, n - 1);
    showSteps = false;

    cout << "Sorted:  ";
    printArray(arr, n);
    cout << "\n\n";
}

// sorts and prints the comparison count
void countTest(const char* name, int arr[], int n) {
    comparisons = 0;
    cout << name << "\nBefore: ";
    printArray(arr, n);
    cout << "\n";

    quickSort(arr, 0, n - 1);

    cout << "After:  ";
    printArray(arr, n);
    cout << "\nComparisons = " << comparisons << "\n\n";
}

int main() {
    // part 1: trace
    cout << "=== Trace Tests ===\n";

    int a1[] = {2, 1, 5, 4, 6, 3};
    traceTest("Array 1", a1, 6);

    int a2[] = {35, 12, 43, 8, 51, 27, 19};
    traceTest("Array 2", a2, 7);

    // part 2: comparison counts
    cout << "=== Comparison Counts ===\n";

    int random[] = {5, 1, 4, 2, 8};
    countTest("1. Random Order", random, 5);
    int sorted[] = {1, 2, 4, 5, 8};
    countTest("2. Already Sorted", sorted, 5);
    int reverse[] = {8, 5, 4, 2, 1};
    countTest("3. Reverse Sorted", reverse, 5);
    int same[] = {7, 7, 7, 7, 7};
    countTest("4. Repeated Values", same, 5);
    int single[] = {42};
    countTest("5. Single Element (n = 1)", single, 1);
    int* empty = nullptr;
    countTest("6. Empty Array (n = 0)", empty, 0);
    return 0;
}