#include <vector>
#include <chrono>
#include <iostream>
#include <cstdlib>

//Radix sort code from https://www.programiz.com/dsa/radix-sort
int getMax(int array[], int n) {
  int max = array[0];
  for (int i = 1; i < n; i++)
    if (array[i] > max)
      max = array[i];
  return max;
}

// Using counting sort to sort the elements in the basis of significant places
void countingSort(int array[], int size, int place) {
  const int max = 10;
  int output[size];
  int count[max];

  for (int i = 0; i < max; ++i)
    count[i] = 0;

  // Calculate count of elements
  for (int i = 0; i < size; i++)
    count[(array[i] / place) % 10]++;

  // Calculate cumulative count
  for (int i = 1; i < max; i++)
    count[i] += count[i - 1];

  // Place the elements in sorted order
  for (int i = size - 1; i >= 0; i--) {
    output[count[(array[i] / place) % 10] - 1] = array[i];
    count[(array[i] / place) % 10]--;
  }

  for (int i = 0; i < size; i++)
    array[i] = output[i];
}

// Main function to implement radix sort
void radixsort(int array[], int size) {
  // Get maximum element
  int max = getMax(array, size);

  // Apply counting sort to sort elements based on place value.
  for (int place = 1; max / place > 0; place *= 10)
    countingSort(array, size, place);
}

int main() {

    const int size = 10000;
    srand((unsigned) time(NULL));

    auto start{std::chrono::steady_clock::now()};
    auto end{std::chrono::steady_clock::now()};

    int a[size];
    int a2[size];
    for (int i = 0; i < size; i++) {
        int n = rand() % 10;
        a[i] = n;
        a2[i] = n;
    } 
    start = std::chrono::steady_clock::now();
    std::sort(a, a+size);
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_std{end - start};

    start = std::chrono::steady_clock::now();
    radixsort(a2, size);
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_radix{end - start};

    for (int i = 0; i < size; i++) {
        if (a[i] != a2[i]) {
            std::cout << "The arrays are different.";
            break;
        }
    }
    std::cout << "std::sort runs in " << elapsed_seconds_std.count() << "s\n";
    std::cout << "radix sort runs in " << elapsed_seconds_radix.count() << "s\n";
    return 0;
}