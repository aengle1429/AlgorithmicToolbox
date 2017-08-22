#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;

int lcs3(const vector<int> &a, const vector<int> &b, const vector<int> &c)
{
  // Operate on string suffixes. Base case is with an empty suffix
  // Suffix indexed from i = x (empty suffix) to i = 0
  int x(a.size()), y(b.size()), z(c.size()); // Will use size + 1 for base case.
  vector<vector<vector<int>>> matrix(x + 1,
                                     vector<vector<int>>(y + 1,
                                                         vector<int>(z + 1, 0)));
  for(int i = x - 1; i >= 0; i--)
  {
      for(int j = y - 1; j >=0; j--)
      {
          for(int k = z - 1; k >=0; k--)
          {
              int replace = matrix[i + 1][j + 1][k + 1];
              if(a[i] == b[j] && b[j] == c[k])
              {
                  replace += 1; 
              }
              matrix[i][j][k] = std::max({replace, matrix[i + 1][j][k], matrix[i+1][j][k+1], matrix[i+1][j+1][k],
                                       matrix[i][j+1][k], matrix[i][j][k+1], matrix[i][j+1][k+1]});
          }
      }
  }
  return matrix[0][0][0];
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
