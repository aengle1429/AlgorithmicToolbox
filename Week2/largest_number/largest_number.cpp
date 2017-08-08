#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

string largest_number(vector<string> a) {
  //write your code here
  std::stringstream ret;
  while(a.size() > 0)
  {
	  int maxdigit = 0;
	  int maxlocation = -1;
	  for(int i = 0; i < a.size(); ++i)
	  {
		// if(std::stoi(a.at(i)) >= maxdigit)
		// string smaxdigit = std::to_string(maxdigit);
		// std::cout << a.at(i) + std::to_string(maxdigit) << "\n";
		if(std::stoi(a.at(i) + std::to_string(maxdigit)) >= std::stoi(std::to_string(maxdigit) + a.at(i)))
		{
			maxdigit = std::stoi(a.at(i));
			maxlocation = i;
		}
	  }
	  ret << a.at(maxlocation);
	  a.erase(a.begin() + maxlocation);
  }
  // for (size_t i = 0; i < a.size(); i++) {
  //   ret << a[i];
  // }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
