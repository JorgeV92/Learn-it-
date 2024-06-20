///////////////////////////////////////////////////////////////////////////////////////////////
// Algorithnms Jeff Erickson
//
//  1. Divide the input array into two subarrays of roughly equal size.
//  2. Recursively mergesort each of the subarrays.
//  3. Merge the newly-sorted subarrays into a single sorted array.
//
// **********************************************************
//  MergeSort(A[1..n]):
//      if n > 1
//          m <- floor(n / 2)
//          MergeSort(A[1..m])      << Recurse!>>
//          MergeSort(A[m+1..n])    << Recurse!>>
//          Merge(A[1..n], m)
// **********************************************************
//
//
// **********************************************************
//  Merge(A[1..n], m):
//      i <- 1; j <- m + 1
//      for k <- 1 to n
//          if j > n
//              B[k] <- A[i]; i <- i + 1
//          else if i > m
//              B[k] <- A[j]; j <- j + 1
//          else if A[i] < A[j]
//              B[k] <- A[i]; i <- i + 1
//          else
//              B[k] <- A[j]; j <- j + 1
//      
//      for k <- 1 to n
//          A[k] <- B[k]
// **********************************************************
// Good Luck!
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

/// @brief Merges two sorted subarrays of A into a single sorted subarray.
/// The subarrays are defined by the indices [start..mid] and [mid+1..end].
/// @param A The array containing the subarrays to be merged.
/// @param start The starting index of the first subarray.
/// @param mid The ending index of the first subarray, and mid+1 is the starting index of the second subarray.
/// @param end The ending index of the second subarray.
void Merge(std::vector<int>& A, int start, int mid, int end) {
    int i = start, j = mid + 1;
    int n = end - start + 1;
    std::vector<int> B(n);

    for (int k = 0; k < n; k++) {
        if (j > end) {
            B[k] = A[i];
            i = i + 1;
        } else if (i > mid) {
            B[k] = A[k];
            j = j + 1;
        } else if (A[i] < A[j]) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;
        }
    }

    for (int k = 0; k < n; k++) {
        A[start + k] = B[k];
    } 
}

/// @brief Recursively sorts an array using the merge sort algorithm.
/// The array is divided into subarrays, each subarray is sorted, and then merged back together.
/// @param A The array to be sorted.
/// @param start The starting index of the subarray to be sorted.
/// @param end The ending index of the subarray to be sorted.
void MergeSort(std::vector<int>& A, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        MergeSort(A, start, mid);
        MergeSort(A, mid + 1, end);
        Merge(A, start, mid, end);
    }
}

int main () {
    std::vector<int> A = {38, 27, 43, 3, 9, 82, 10};

    MergeSort(A, 0, A.size() - 1);
    
    for (int i : A) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}