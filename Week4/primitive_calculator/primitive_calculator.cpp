#include <limits>
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using namespace std;

// the greedy algorithm here fails with n = 10
// greedy proposes the sequence 10 5 4 2 1
// optimal is 10 9 3 1

/*
 *steps to dynamic programming are
 *1. Define subproblems
 *2. Guess part of solution
 *3. Recurrence (time / subproblem)
 *4. Recurse + Memoize (acyclic) or Bottom-up (topo ordering needed)
 * time = #subproblem  * time/subproblem
 *5. Original problem
*/


// Here we try Recurse + Memoize. However, for n large enough the recursion tree is too deep, so stack overflow.

int optimal_sequence(int n, vector<int> &memo, vector<int> &backtrack) {
  if(n > 1 && memo.at(n - 1) >= 1)
  {
      return memo.at(n - 1);
  }
  if(n == 1)
  {
      return n - 1;
  }
  else
  {
      int p1, p2, p3;
      p3 = optimal_sequence(n - 1, memo, backtrack);
      p2 = n % 2 == 0 ? optimal_sequence(n / 2, memo, backtrack) : numeric_limits<int>::max(); 
      p1 = n % 3 == 0 ? optimal_sequence(n / 3, memo, backtrack) : numeric_limits<int>::max();
      // std::cout << "The numbers for n= " << n << " are " << p1 << " " << p2 << " " << p3 << endl;
      int ans = min({p1, p2, p3}) + 1;
      memo[n-1] = ans;
      if( p1 <= p2 )
      {
       if( p1 <= p3)
       {
         backtrack.at(n - 1) = n / 3;
       }
       else
       {
         backtrack.at(n - 1) = n - 1;
       }
      }
      else
      {
       if( p2 <= p3 )
       {
         backtrack.at(n - 1) = n / 2;
       }
       else
       {
         backtrack.at(n - 1) = n - 1;
       }
      }
      return ans;
   }
}

void optimal_sequence2(int n, vector<int> &memo, vector<int> &backtrack)
{
    // Place ith answer in memo[i - 1]
    memo.at(0) = 0;
    for(int i = 2; i <= n; ++i)
    {
        int p1 = i % 3 == 0 ? memo.at(i / 3 - 1) : numeric_limits<int>::max();
        int p2 = i % 2 == 0 ? memo.at(i / 2 - 1) : numeric_limits<int>::max();
        int p3 = memo.at(i - 2);
        int ans = min({p1, p2, p3}) + 1;
        memo.at(i-1) = ans;
        if( p1 <= p2 )
        {
        if( p1 <= p3)
        {
        backtrack.at(i - 1) = i / 3;
        }
        else
        {
        backtrack.at(i - 1) = i - 1;
        }
        }
        else
        {
        if( p2 <= p3 )
        {
         backtrack.at(i - 1) = i / 2;
        }
        else
        {
         backtrack.at(i - 1) = i - 1;
        }
        }
    }          
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence(n, 0), backtrack(n, 0);
  optimal_sequence2(n, sequence, backtrack);
  cout << sequence.back() << endl;
  vector<int> answ;
  answ.push_back(n);
  while(n > 1)
  {
      answ.push_back(backtrack[n - 1]); 
      n = backtrack[n - 1];
  }
  reverse(answ.begin(), answ.end());
  for(int i = 0; i < answ.size(); ++i) std::cout << answ[i] << " ";
}
