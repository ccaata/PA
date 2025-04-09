#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Function to get the digit at a specific position
int getDigit(int number, int position) {
    return (number / static_cast<int>(pow(10, position))) % 10;
}

// Radix Sort implementation
void radixSort(vector<int>& arr, int maxDigits) {
    const int base = 10; // Base 10 for decimal numbers
    vector<queue<int>> buckets(base);

    for (int digit = 0; digit < maxDigits; ++digit) {
        // Distribute elements into buckets based on the current digit
        for (int num : arr) {
            int bucketIndex = getDigit(num, digit);
            buckets[bucketIndex].push(num);
        }

        // Collect elements back into the array
        int index = 0;
        for (int i = 0; i < base; ++i) {
            while (!buckets[i].empty()) {
                arr[index++] = buckets[i].front();
                buckets[i].pop();
            }
        }
    }
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    int maxDigits = 3; // Maximum number of digits in the largest number

    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    radixSort(arr, maxDigits);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
