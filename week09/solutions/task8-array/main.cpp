#include <iostream>
#include "Array.h"

int main() {
    // --- int array ---
    Array<int, 5> arr;
    arr[0] = 3; arr[1] = 1; arr[2] = 4; arr[3] = 1; arr[4] = 5;

    std::cout << "arr:     "; arr.print();
    std::cout << "size:    " << arr.size() << "\n";
    std::cout << "min:     " << min(arr)      << "\n"; // 1
    std::cout << "max:     " << max(arr)      << "\n"; // 5
    std::cout << "sum:     " << sum(arr)      << "\n"; // 14
    std::cout << "find(4): " << find(arr, 4)  << "\n"; // 2
    std::cout << "find(9): " << find(arr, 9)  << "\n"; // -1

    sort(arr);
    std::cout << "sorted:  "; arr.print(); // [1, 1, 3, 4, 5]

    reverse(arr);
    std::cout << "reversed:"; arr.print(); // [5, 4, 3, 1, 1]

    // --- double array ---
    std::cout << "\n";
    Array<double, 4> vec;
    vec[0] = 1.5; vec[1] = 3.2; vec[2] = 0.8; vec[3] = 2.1;

    std::cout << "vec:     "; vec.print();
    std::cout << "min:     " << min(vec)  << "\n"; // 0.8
    std::cout << "max:     " << max(vec)  << "\n"; // 3.2
    std::cout << "sum:     " << sum(vec)  << "\n"; // 7.6

    sort(vec);
    std::cout << "sorted:  "; vec.print(); // [0.8, 1.5, 2.1, 3.2]
}
