#include <iostream>

int get_change(int m) {
	//write your code here
	int n = 0;
	int coins [3] = {10, 5, 1};

	int i = 0;
	while(i < 3)
	{
		int quotient = m / 10;
		n += m / coins[i];
		m = m % coins[i];
		++i;
	}
	return n;
}

int main() {
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
