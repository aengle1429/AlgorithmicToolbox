#include <iostream>
#include <string>
#include <algorithm>

using std::string;

int edit_distance(const string &str1, const string &str2) {
  // Operate on string suffixes. Base case is with an empty suffix
  // Suffix indexed from i = x (empty suffix) to i = 0
  int x(str1.size()), y(str2.size());
  int matrix [x + 1][y + 1];
  for(int i = 0; i < y; i++) matrix[x][i] = y - i; // Empty suffix vs suffix of variable length
  for(int i = 0; i < x; i++) matrix[i][y] = x - i;
  matrix[x][y] = 0; // Two empty suffixes
  for(int i = x - 1; i >= 0; i--)
  {
      for(int j = y - 1; j >=0; j--)
      {
          char xi(str1[i]), yj(str2[j]);
          int replace = xi == yj ? matrix[i + 1][j + 1] : matrix[i + 1][j + 1] + 1;
          matrix[i][j] = std::min({replace, matrix[i + 1][j] + 1, matrix[i][j + 1] + 1});
      }
  }
  return matrix[0][0];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
