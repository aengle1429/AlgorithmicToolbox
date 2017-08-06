#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int euclidean(int a, int b)
{
	if(b == 0)
	{
		return a;
	}
	else
	{
		return euclidean(b, a % b);
	}
}

long long lcm(int a, int b)
{
	int gcd = euclidean(a, b);
	long long lcm1 = (a / gcd); // need to be very careful when computing a*b/d. Overflows will occur
	long long lcm2 = lcm1 * b;
	// overflow if compute a * b first.
	return lcm2;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  // std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}
