#pragma once
#include <vector>
#include "listing.h"
using namespace std;

void heapifyDown(vector<pair<Listing, double>>& heap, int size, int root);

void heapSort(vector<pair<Listing, double>>& unsorted, int size);