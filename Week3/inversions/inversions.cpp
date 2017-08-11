#include <iostream>
#include <vector>

using std::vector;

void mergeAB(vector<int> &c, vector<int> &a, int N, vector<int> &b, int M)
{
    for(int i = 0, j = 0, k = 0; k < N + M; ++k)
    {

        if(i==N) { c[k] = b[j++]; continue;}
        if(j==M) { c[k] = a[i++]; continue;}
        c[k] = (a[i] < b[j]) ? a[i++] : b[j++];
    }
}

void mergesortABr(vector<int> &a, vector<int> &b, int l, int r)
{
    if(r <= l) { return; }
    int m = (l + r) / 2;
    mergesortABr(b, a, l, m);
    mergesortABr(b, a, m+1, r);
    merge(a+l, b+l, m-l+1, b+m+1, r-m);
}

void mergesortAB(vector<int> &a, int l, int r)
{
    vector<int> &aux(r-l+1);
    for(int i = l; i <= r; ++i) aux[i] = a[i];
    mergesortABr(a, aux, l, r);
}


long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
    long long number_of_inversions = 0;
    if (right <= left + 1)
    {
        return number_of_inversions;
    }
    size_t ave = left + (right - left) / 2;
    number_of_inversions += get_number_of_inversions(a, b, left, ave);
    number_of_inversions += get_number_of_inversions(a, b, ave, right);
    return number_of_inversions;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
      std::cin >> a[i];
    }
    vector<int> b(a.size());
    std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
