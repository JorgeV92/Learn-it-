def read_information():
    # number of elemets and numnber of queries
    n, k = map(int, input().strip().split())
    a = list(map(int, input().strip().split()))
    assert len(a) == n, "The number of array elements does not match the provided n"
    # Read the third line to get the queries
    q = list(map(int, input().strip().split()))
    assert len(q) == k, "The number of queries does not match the provided k"
    return a, q

def binary_search(A, Q):
    results = []
    for q in Q:
        l, r = 0, len(A) - 1
        found = False
        while l <= r:
            m = (l + r) // 2
            if A[m] == q:
                results.append("YES")
                found = True
                break
            elif A[m] < q:
                l = m + 1
            else:
                r = m - 1
        if not found:
            results.append("NO")
    return results

if __name__ == "__main__":
    # Get data from user input
    a, q = read_information()
    print()
    # Process each query and print results
    results = binary_search(a, q)
    for result in results:
        print(result)
