#include <iostream>
#include <array>
#include <vector>
using std::array;
using std::vector;

/* Idea : Let val(w, i) denote the optimal value of a knapsack
 * with size w using the first i items, letting val(0, i) = val(w, 0) = 0.
 * Then the optimal knapsack at (w, i) either contains item i or not.
 * In the former, val(w - w_i, i - 1) is an optimal knapsack
 * which we can add w_i to to obtain (w, i). In the latter,
 * val(w, i) = val(w, i - 1) since item i is not present. 
 * Therefore val(w, i) = max( val(w - w_i, i - 1), val(w, i - 1) )
 * And obviously w - w_i >=0 is a necessary condition for the max.
 */
int optimal_weight(int W, const vector<int> &items)
{
    int n = items.size();
    // int matrix [W+1][n+1];
    vector<array<int, 301>> matrix;
    //write your code here
    for(int w = 0; w < W + 1; ++w)
    {
        array<int, 301> arr;
        arr[0] = 0;
        matrix.push_back(arr);
    }

    for(int i = 0; i < n + 1; ++i)
    {
        matrix[0][i] = 0;
    }


    for(int w = 1; w < W + 1; ++w)
    {
        for(int i = 1; i < n + 1; ++i)
        {
            int val = matrix[w][i-1];
            if( w - items[i - 1] >= 0 )
            {
                // std::cout << "Here is items[i] " << items[i] << std::endl;
                int val2 = matrix[w - items[i - 1]][i - 1] + items[i - 1];
                matrix[w][i] = val > val2 ? val : val2;
            }
            else{
                matrix[w][i] = val;
            }
        }
    }

    // int current_weight = 0;
    // for (size_t i = 0; i < items.size(); ++i) {
    //     if (current_weight + items[i] <= W) {
    //         current_weight += items[i];
    //     }
    // }
    return matrix[W][n];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
