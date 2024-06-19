// MERGE SORT
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////
// Wiki source https://en.wikipedia.org/wiki/Merge_sort
//
//  Algorithm
//     1. Divide the unsorted list into n sublists, each containing one element
//     (a list of one
//        element is considered sorted.)
//     2. Repeatedly merge sublists to produce new sorted sublists unitl there
//     is only on e
//        sublist remaining. This will be the sorted list.
//
//
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
// Algorithnms Jeff Erickson
//
//
///////////////////////////////////////////////////////////////////////////////////////////////

//*********************************************************************************

////////////////////////////////////////////////////////////////////////////////////
// Wiki Merge Sort Top Down
////////////////////////////////////////////////////////////////////////////////////

/// @brief Copies a segment of one array to another array.
///
/// This function copies elements from the source array A
/// to the destination array B, from index iBegin to iEnd.
///
/// @param A The source array from which elements are copied.
/// @param iBegin The starting index in the source array.
/// @param iEnd The ending index in the source array (exclusive).
/// @param B The destination array where elements are copied to.
void CopyArray(int A[], int iBegin, int iEnd, int B[]) {
    for (int k = iBegin; k < iEnd; k++) {
        B[k] = A[k];
    }
}

/// @brief Merges two halves of an array into a single sorted array.
///
/// Left source half is A[iBegin:iMiddle-1].
/// Right source half is A[iMiddle:iEnd-1].
/// Result is B[iBegin:iEnd-1].
///
/// @param B The array where the merged result will be stored.
/// @param iBegin The starting index of the subarray to be merged.
/// @param iMiddle The index that separates the two halves of the array to be
/// merged.
/// @param iEnd The ending index of the subarray to be merged.
/// @param A The source array containing the two halves to be merged.
void TopDownMerge(int B[], int iBegin, int iMiddle, int iEnd, int A[]) {
    int i = iBegin, j = iMiddle;

    // While there are elements in the left or right runs...
    for (int k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;
        }
    }
}

/// @brief Recursively splits and merges subarrays for the top-down merge sort
/// algorithm.
///
/// This function splits the array into halves, recursively sorts each half, and
/// then merges the sorted halves.
///
/// @param B The auxiliary array used during the merge sort process.
/// @param iBegin The starting index of the subarray to be split and merged.
/// @param iEnd The ending index of the subarray to be split and merged.
/// @param A The source array containing the subarrays to be split and merged.
void TopDownSplitMerge(int B[], int iBegin, int iEnd, int A[]) {
    if (iEnd - iBegin <= 1) return;  // if run size == 1

    // split the run longer than 1 item into halves
    int iMiddle = (iEnd + iBegin) / 2;  // iMiddle = mid point
    // rrecursively sort both runs from array A[] int B[]
    TopDownSplitMerge(A, iBegin, iMiddle, B);  // sort the left run
    TopDownSplitMerge(A, iMiddle, iEnd, B);    // sort the right run
    // merge the resulting runs from array B[] into A[]
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
}

/// @brief Sorts an array using the top-down merge sort algorithm.
///
/// This function initiates the top-down merge sort algorithm by performing
/// a one-time copy of the source array A[] to the auxiliary array B[].
///
/// @param A The source array to be sorted.
/// @param B An auxiliary array used during the merge sort process.
/// @param n The number of elements in the array A[].
void TopDownMergeSort(int A[], int B[], int n) {
    CopyArray(A, 0, n, B);          // one time copy of A[] to B[]
    TopDownSplitMerge(A, 0, n, B);  // sort data from B[] into A[]
}

void testTopDownMerge() {
    int A[] = {5, 7, 8, 2, 1, 0, 6, 7, 22, 45, 65, 78, 99, 92};
    int n = sizeof(A) / sizeof(A[0]);
    int B[n];
    TopDownMergeSort(A, B, n);
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

//*********************************************************************************

//*********************************************************************************
////////////////////////////////////////////////////////////////////////////////////
// Wiki Merge Sort Bottom Up
////////////////////////////////////////////////////////////////////////////////////

/// @brief
/// @param A
/// @param iLfeft
/// @param iRight
/// @param iEnd
/// @param B
void BottomUpMerge(int A[], int iLeft, int iRight, int iEnd, int B[]) {
    int i = iLeft, j = iRight;
    // While there are elements in the left or right runs ...
    for (int k = iLeft; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iRight && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;
        }
    }
}

/// @brief Copies a segment of one array to another array.
/// @param B
/// @param A
/// @param n
void CopyArrayBottomUp(int B[], int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
}

/// @brief
/// @param A The source array to be sorted
/// @param B
/// @param n
void BottomUpMergeSort(int A[], int B[], int n) {
    // Each 1-element run in A is already sorted
    // Make successively longer sorted runs of length 2, 4, 8, 16...
    // until the whole array is sorted.
    for (int width = 1; width < n; width = 2 * width) {
        // Array A is full of runs of length width.
        for (int i = 0; i < n; i = i + 2 * width) {
            // Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[]
            // or copy A[i:n-1] to B[] ( if i+width >= n)
            BottomUpMerge(A, i, std::min(i + width, n),
                          std::min(i + 2 * width, n), B);
        }
        // Now work array B is full or runs of length 2*width.
        // Copy array B to array A for the next iteration.
        // A more efficient implementation would swap the roles of A and B
        CopyArrayBottomUp(B, A, n);
        // Now array A is full of runs of length 2*width
    }
}

//*********************************************************************************

int main() {
    std::cout << "Compiled\n";
    testTopDownMerge();
    return 0;
}