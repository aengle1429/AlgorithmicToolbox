#include <algorithm>
#include <array>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <limits>

using std::vector;
using std::array;
using std::string;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;


long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}

array<long long, 2> min_and_max(int i, int j, vector<int> &digits, vector<char> &ops, vector<vector<long long>> &M, vector<vector<long long>> &m)
{
    long long minimum, maximum;
    maximum = std::numeric_limits<int>::lowest();
    minimum = std::numeric_limits<int>::max();
    for(int k = i; k < j; k++)
    {
        long long a, b, c, d;
        a = eval(M[i][k], M[k+1][j], ops[k]);
        b = eval(M[i][k], m[k+1][j], ops[k]);
        c = eval(m[i][k], M[k+1][j], ops[k]);
        d = eval(m[i][k], m[k+1][j], ops[k]);
        minimum = min({minimum, a, b, c, d});
        maximum = max({maximum, a, b, c, d});
    }
    return {minimum, maximum};
}

long long get_maximum_value(const string &exp) {
    //write your code here
    // E_{i,j} = d_i op_i ... op_{j - 1} d_j
    // If there are n digits, then exp has length 2n - 1.
    // In other words,
    int n = (exp.size() + 1) / 2;
    vector<int> digits(n, 0);
    vector<char> ops(n - 1, 0);
    vector<vector<long long>> M(n, vector<long long>(n, 0));
    vector<vector<long long>> m(n, vector<long long>(n, 0));
    for(int i = 0; i <= exp.size(); i = i + 2)
    {
        int c = (int)exp.at(i) - '0';
        digits[i / 2] = c;
        M[i / 2][i / 2] = c;
        m[i / 2][i / 2] = c;
        // cout << M[i/2][i/2] << endl;
    } 
    for(int i = 1; i <= exp.size() - 1; i=i+2) ops[(i - 1)/2] = exp.at(i);
    for(int s = 1; s <= n-1; s++) // s for super diagonals
    {
        for(int i = 0; i <= n-1-s; i++)
        {
            int j = i + s; // now i + j = s
            array<long long, 2> ans = min_and_max(i, j, digits, ops, M, m);
            m[i][j] = ans[0];
            M[i][j] = ans[1];
        }
    }
    return M[0][n - 1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
