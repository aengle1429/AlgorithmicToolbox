#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

long long max_dot_product(vector<int> a, vector<int> b) {
  // write your code here
    if(a.size() > 1)
    {
        for(int i = 1; i < a.size(); ++i)
        {
            int key1 = a.at(i);
            int key2 = b.at(i);
            int j = i - 1;
            int k = i - 1;

            while(k >= 0 && b.at(k) > key2)
            {
                b.at(k+1) = b.at(k);
                k--;
            }
            b.at(k+1) = key2;


            while(j >= 0 && a.at(j) > key1)
            {
                a.at(j+1) = a.at(j);
                j--;
            }
            a.at(j+1) = key1;
        }
    }
    // for(int i = 0; i < a.size(); ++i)
    // {
    //     std::cout << a.at(i) << " ";
    // }
    // for(int i = 0; i < a.size(); ++i)
    // {
    //     std::cout << b.at(i) << " ";
    // }
    long long result = 0;
    for (size_t i = 0; i < a.size(); i++) {
      result += ((long long) a[i]) * b[i];
    }
    return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
