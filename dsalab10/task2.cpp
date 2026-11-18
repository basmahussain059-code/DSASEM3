#include <iostream>
#include <vector>
using namespace std;

class Heap {
private:
    vector<int> data;
    bool isMax;
    // true if a should sit above b in this heap
    bool above(int a, int b) {
        if (isMax) return a > b;
        else       return a < b;
    }
public:
    Heap(bool maxHeap) {
        isMax = maxHeap;
    }
    int size()   { return data.size(); }
    bool empty() { return data.empty(); }
    int top()    { return data[0]; }
    //add at the end, then sift up while it belongs above its parent
    void push(int value) {
        data.push_back(value);
        int i = data.size() - 1;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (above(data[i], data[parent])) {
                int temp = data[i];
                data[i] = data[parent];
                data[parent] = temp;
                i = parent;
            } else {
                break;
            }
        }
    }

    //put the last element at the root, then sift down
    int pop() {
        int root = data[0];
        data[0] = data.back();
        data.pop_back();

        int i = 0;
        int n = data.size();
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int best = i;

            if (left < n && above(data[left], data[best]))
                best = left;
            if (right < n && above(data[right], data[best]))
                best = right;

            if (best == i)
                break;

            int temp = data[i];
            data[i] = data[best];
            data[best] = temp;
            i = best;
        }
        return root;
    }
};

class WaitMonitor {
private:
    Heap lower;  // max heap: smaller half (holds the extra element)
    Heap upper;  // min heap: larger half

public:
    WaitMonitor() : lower(true), upper(false) {}

    // Insert into the correct heap, then rebalance so sizes differ by at most 1
    void addWait(int x) {
        if (lower.empty() || x <= lower.top())
            lower.push(x);
        else
            upper.push(x);

        if (lower.size() > upper.size() + 1)
            upper.push(lower.pop());
        else if (upper.size() > lower.size())
            lower.push(upper.pop());
    }

    // O(1): only looks at the roots
    double getMedian() {
        if (lower.size() > upper.size())
            return lower.top();
        return (lower.top() + upper.top()) / 2.0;
    }

    void printRoots() {
        cout << "Max root: " << lower.top() << " | Min root: ";
        if (upper.empty()) cout << "none";
        else               cout << upper.top();
    }
};

int main() {
    WaitMonitor monitor;
    int waits[] = {45, 20, 60, 15, 30, 90, 10, 55};
    int n = 8;
    int threshold = 35;

    for (int i = 0; i < n; i++) {
        monitor.addWait(waits[i]);
        double median = monitor.getMedian();

        cout << "Arrival " << i + 1 << " | Wait: " << waits[i] << " | ";
        monitor.printRoots();
        cout << " | Median: " << median << " | ";

        if (median > threshold)
            cout << "ALERT: call extra staff";
        else
            cout << "Normal";
        cout << endl;
    }

    return 0;
}

/*
Q7. Why is the median a better alert measure than the average? (arrival 6)
Answer: The average is pulled by extreme values; the median is not. At arrival 6
the waits are 45, 20, 60, 15, 30, 90. Without the 90 the average would be 34
(Normal). With the single 90 it jumps to 43.3. If that patient waited 900
minutes instead, the median would still be 37.5, but the average would be 188.3.
The median shows what a typical patient experiences, so one extreme case
cannot distort it.

Q8. What goes wrong if the two heap sizes differ by two or more?
Answer: The two roots are no longer the middle elements of the sorted data.
For example, if the max heap had 3 more elements than the min heap, its root
would be above the true median. getMedian() would then return a wrong value
(and a wrong ALERT/Normal status).

Q9. How many total operations does repeated sorting need compared with the heap method?
Answer: Sorting after every arrival costs O(k log k) for the k-th arrival, so the
total is about O(n^2 log n) for n patients. The two-heap method costs O(log n)
per arrival, so O(n log n) in total, and each median lookup is O(1).
*/