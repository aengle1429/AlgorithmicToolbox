#include <iostream>
/*
Return F_n (mod m), 1\le n \le 1e18, 2\le m\le 1e5
*/
long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long long get_pisano(long long n, long long m)
{
	//Creates a dynamic array that returns the Pisano period
	int previous = 0;
	int current = 1;
	int not_done = 1;
	long period = 0;
	while(not_done)
	{
		int tmp_previous = previous;
		previous = current;
		current = (previous + tmp_previous) % m;
		if(previous == 0 && current == 1)
		{
			not_done = 0;
		}
		period++;
	}
	return period;
}

long long get_fibonacci_huge(long long n, long long m)
{
	int period = get_pisano(n, m);
	// std::cout << period << std::endl;
	int mod_n = n % period;
	if(mod_n == 0 || mod_n == 1)
	{
		return mod_n;
	}
	else
	{
		long long fibs_mod_m [mod_n + 1]; // Array of size n mod period + 1
		fibs_mod_m[0] = 0;
		fibs_mod_m[1] = 1;
		for(int i = 2; i < mod_n + 1; ++i)
		{
			fibs_mod_m[i] = (fibs_mod_m[i-1] + fibs_mod_m[i-2]) % m;
		}
		return fibs_mod_m[mod_n];
	}
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    // std::cout << get_fibonacci_huge_naive(n, m) << '\n';
    std::cout << get_fibonacci_huge(n, m) << '\n';
}
