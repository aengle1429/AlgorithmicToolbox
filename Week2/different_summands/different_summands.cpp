#include <iostream>
#include <vector>

using std::vector;

// Given a positive integer n, find the maximum number of distinct positive summands that total n.
// There are multiple optima; e.g., 8 = 1 + 2 + 5 = 1 + 3 + 4.
// The greedy approach

int summands_helper(int l, int k)
{
	if(k <= 2*l)
	{
		return k;
	}
	else
	{
		return l;
	}
}

vector<int> optimal_summands(int n) {
  vector<int> summands;
  //write your code here
  int l = 1;
  int k = n;
  while(k > 0)
  {
    int ans = summands_helper(l, k);	
	summands.push_back(ans);
	// std::cout << ans << std::endl;
	k = k - ans;
	l = l + 1;
    // std::cout << l << " " << k << "\n";
  }
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
