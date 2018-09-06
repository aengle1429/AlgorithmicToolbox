#include <iostream>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

long long get_pisano()
{
    int previous = 0;
    int current = 1;
    int period = 0;
    int not_done = 1;
    while(not_done)
    {
        int temp_prev = previous;
        previous = current;
        current = (previous + temp_prev) % 10;
        if(previous == 0 && current == 1)
        {
            not_done = 0;
        }
        period++; 
    }
    return period;
}

int fibonacci_sum(long long n)
{
    // Sum of first n Fibonacci numbers is F(n+2) - 1
    // We want this mod 10. First find Pisano period, then compute.
    // F( n+2 (mod pisano(10)) ) - 1
    if(n == 0 || n == 1)
    {
        return n;
    }
    else
    {
        long long pisano_10 = get_pisano();
//        std::cout << pisano_10 << std::endl;
        long long residue = (n + 2) % pisano_10;
        int previous = 0;
        int current = 1;
        for(int i = 2; i < residue + 1; ++i)
        {
            int temp = previous;
            previous = current;
            current = (temp + previous) % 10;
        }
        return (current + 9) % 10;
        /*
        int fibs [n + 3];
        fibs[0] = 0;
        fibs[1] = 1;
        for(int i = 2; i < n + 3; ++i)
        {
            fibs[i] = fibs[i-1] + fibs[i-2];
        }
        return fibs[n + 2] - 1;
        */
    }
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum(n);
}
