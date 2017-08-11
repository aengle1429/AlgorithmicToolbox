#include <iostream>
#include <vector>

using std::vector;

// void mergeAB(int c[], int a[], int N, int b[], int M)
// {
//     for(int i = 0, j = 0, k = 0; k < N + M; ++k)
//     {
// 
//         if(i==N) { c[k] = b[j++]; continue;}
//         if(j==M) { c[k] = a[i++]; continue;}
//         c[k] = (a[i] < b[j]) ? a[i++] : b[j++];
//     }
// }
// 
long long mergeAB(long long c[], long long a[], int N, long long b[], int M)
{
    long long numInv = 0;
    for(int i = 0, j = 0, k = 0; k < N + M; ++k)
    {

        if(i==N) { c[k] = b[j++]; continue;}
        if(j==M) { c[k] = a[i++]; continue;}
        if(a[i] <= b[j]) c[k] = a[i++];
        else{numInv+=(N-i); c[k] = b[j++];}
    }
    return numInv;
}

long long mergesortABr(long long a[],long long b[], int l, int r)
{
    long long numInv = 0;
    //recursion set up to sort subcomponents of b[l,...,r] and merge them into a[l,...,r].
    if(r <= l){ return numInv; }
    int m = (l + r) / 2;
    long long i1 = mergesortABr(b, a, l, m);
    long long i2 = mergesortABr(b, a, m+1, r);
    // merge the files from b into a.
    // all data movement is done during merge
    numInv += mergeAB(&a[l], &b[l], m-l+1, &b[m+1], r-m);
    return i1 + i2 + numInv;
}

void mergesortAB(long long a[], int l, int r)
{
    long long aux [r-l+1];
    for(int i = 0; i <= r-l; ++i) aux[i] = a[i];
    long long inversions = mergesortABr(a, aux, 0, r-l);
    // for(int i = 0; i <= r-l; ++i) std::cout<<a[i]<<std::endl;
    std::cout << inversions << std::endl;
}


// long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
//     long long number_of_inversions = 0;
//     if (right <= left + 1)
//     {
//         return number_of_inversions;
//     }
//     size_t ave = left + (right - left) / 2;
//     number_of_inversions += get_number_of_inversions(a, b, left, ave);
//     number_of_inversions += get_number_of_inversions(a, b, ave, right);
//     return number_of_inversions;
// }
// 
int main() {
    int n;
    std::cin >> n;
    long long a [n];
    for (size_t i = 0; i < n; i++) {
      std::cin >> a[i];
    }
    mergesortAB(a, 0, n-1);
    //std::cout << get_number_of_inversions(a, b, 0, n) << '\n';
}
