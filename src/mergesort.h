#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include "listing.h"

void merge(std::vector<std::pair<Listing, double>>& vec, int start, int mid, int end);
void recursiveMergeSort(std::vector<Listing, double>& vec, int start, int end);
void mergeSort(std::vector<std::pair<Listing, double>>& vec);

#endif
