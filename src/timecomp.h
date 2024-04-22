#ifndef TIME_MEASUREMENT_H
#define TIME_MEASUREMENT_H

#include <chrono>
#include <utility>
#include "mergesort.h"
#include "heapsort.h"


template<typename Func, typename... Args>
long long measureTime(Func func, Args&&... args);


#endif  // TIME_MEASUREMENT_H
