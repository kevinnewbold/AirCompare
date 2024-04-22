#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>


void merge(std::vector<double>& vec, int start, int mid, int end);
void recursiveMergeSort(std::vector<double>& vec, int start, int end);
void mergeSort(std::vector<double>& vec);

#endif
