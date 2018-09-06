#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    if (to <= 1)
        return to;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < from - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    long long sum = current;

    for (long long i = 0; i < to - from; ++i) {
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

int fibonacci_partial_sum(long long m, long long n)
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
        long long residue = (n + 2) % pisano_10;
        long long residue_lower = (m + 1) % pisano_10;
        int previous = 0;
        int current = 1;
        int current_lower;
        for(int i = 2; i < residue + 1; ++i)
        {
            int temp = previous;
            previous = current;
            current = (temp + previous) % 10;
            if(i == residue_lower)
            {
                current_lower = current;
            }
        }
        return ((current - current_lower) + 10 ) % 10;
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
    long long from, to;
    std::cin >> from >> to;
//    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << fibonacci_partial_sum(from, to) << '\n';
}
