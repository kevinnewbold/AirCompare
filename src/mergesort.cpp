#include "mergesort.h"
#include <vector>
#include <utility>
using namespace std;

void merge(vector<pair<Listing, double>>& vec, int start, int mid, int end) {
    int sizeLeft = mid - start + 1;
    int sizeRight = end - mid;
    vector<pair<Listing, double>> leftSubvec(sizeLeft);
    vector<pair<Listing, double>> rightSubvec(sizeRight);

    for (int i = 0; i < sizeLeft; i++)
        leftSubvec[i] = vec[start + i];
    for (int j = 0; j < sizeRight; j++)
        rightSubvec[j] = vec[mid + 1 + j];

    int leftIndex = 0;
    int rightIndex = 0;
    int mergedIndex = start;

    while (leftIndex < sizeLeft && rightIndex < sizeRight) {
        if (leftSubvec[leftIndex].second <= rightSubvec[rightIndex].second) {
            vec[mergedIndex++] = leftSubvec[leftIndex++];
        } else {
            vec[mergedIndex++] = rightSubvec[rightIndex++];
        }
    }

    while (leftIndex < sizeLeft) {
        vec[mergedIndex++] = leftSubvec[leftIndex++];
    }

    while (rightIndex < sizeRight) {
        vec[mergedIndex++] = rightSubvec[rightIndex++];
    }
}

void recursiveMergeSort(vector<pair<Listing, double>>& vec, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        recursiveMergeSort(vec, start, mid);
        recursiveMergeSort(vec, mid + 1, end);
        merge(vec, start, mid, end);
    }
}

void mergeSort(vector<pair<Listing, double>>& vec) {
    recursiveMergeSort(vec, 0, vec.size() - 1);
}
