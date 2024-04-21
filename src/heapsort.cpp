void heapifyDown(vector<pair<Listing,double>> &heap, int size, int root) {

    // Sets the "left" node and "right" node from the inputted "root"
    int left = (2 * root) + 1;
    int right = (2 * root) + 2;

    // used to compare with its left and right node
    int max = root;

    // compare root and left node
    if (left < size && heap.at(max).second < heap.at(left).second) {
        max = left;
    }

    // compare root and right node
    if (right < size && heap.at(max).second < heap.at(right).second) {
        max = right;
    }

    // swap the largest child with the root if the root is not max
    if (root != max) {
        pair<Listing,double> temp = heap.at(root);
        heap.at(root) = heap.at(max);
        heap.at(max) = temp;

        // recursively heapifys down to ensure correct max heap structure
        heapifyDown(heap, size, max);
    }
}

void heapSort(vector<pair<Listing,double>> &unsorted, int size) {

    // Creates the max heap in place
    // [(size / 2) - 1] is the last non-leaf node
    for (int i = (size / 2) - 1; i >= 0; i--) {
        heapifyDown(unsorted, size, i);
    }

    // extracts max and moves it to the back of the array
    // then we decrease our "heap size" and repeat until the heap is empty
    for (int i = size - 1; i >= 0; i--) {

        // swap the root of the heap with the end/beginning of the array
        pair<Listing,double> temp = unsorted.at(0);
        unsorted.at(0) = unsorted.at(i);
        unsorted.at(i) = temp;

        // heapify down to make sure it is still a max heap
        // size is i so that heapify does not affect the sorted array
        heapifyDown(unsorted, i, 0);
    }
}