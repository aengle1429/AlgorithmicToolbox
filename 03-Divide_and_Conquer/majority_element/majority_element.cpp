#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return a[left];
  if (left + 1 == right) 
  {
	if(a[left] == a[right])
	{
		return a[left];
	}
	else{
		return -1;
	}
  }
  else{
	  int mid = (right + left) / 2;
	  int L = get_majority_element(a, left, mid); 
	  int R = get_majority_element(a, mid + 1, right);
	  if( L == -1 && R == -1)
	  {
		return -1;
	  }
      else if(L >=0 && R == -1)
	  {
		int count = 0;
		for(int i = left; i <= right; ++i)
		{
			if( a[i] == L)
			{
				count++;
			}
		}
		int ans = (count > (right - left + 1)/2) ? L : -1;
		return ans;
	  }
      else if(R >=0 && L == -1)
	  {
		int count = 0;
		for(int i = left; i <= right; ++i)
		{
			if( a[i] == R)
			{
				count++;
			}
		}
		int ans = (count > (right - left + 1)/2) ? R : -1;
		return ans;
	  }
	  else if(R >= 0 && R == L)
	  {
		return R;
  	  }
	  else
	  {
		int countL = 0;
		int countR = 0;
		for(int i = left; i <= right; ++i)
		{
			if( a[i] == R)
			{
				countR++;
			}
			if( a[i] == L)
			{
				countL++;
			}
		}
		int ansL = (countL > (right - left + 1)/2) ? L : -1;
		int ansR = (countR > (right - left + 1)/2) ? R : -1;
		//std::cout << ansL << " " << ansR << std::endl;
		//std::cout << L << " " << R << std::endl;
		//std::cout << countL << " " << countR << std::endl;
		//std::cout << a.size() << " " << right - left + 1 << std::endl;
		return ansL >= ansR ? ansL : ansR;
	  }
  }
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()-1) != -1) << '\n';
}
