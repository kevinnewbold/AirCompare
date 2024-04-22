#include <iostream>
#include <vector>
#include <chrono>
#include "mergesort.cpp"
#include "heapsort.cpp"


template<typename Func, typename... Args>
long long measureTime(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}
