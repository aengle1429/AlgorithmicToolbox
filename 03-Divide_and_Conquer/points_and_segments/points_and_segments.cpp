#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cstdlib>
using std::vector;
using std::array;

array<int,2> partition3(vector<array<int, 3>> &list, int l, int r)
{
    array<int, 3> key = list.at(l);
    int j = l;
    for(int i = l + 1; i <= r; i++)
    {
        if(list.at(i).at(0) < key.at(0) || (list.at(i).at(0) == key.at(0) && list.at(i).at(1) <= key.at(1)) )
        {
            j++;
            std::swap(list.at(j), list.at(i));
        }
    }
    int k = l;
    for(int i = l + 1; i <= j; i++)
    {
        if(list.at(i).at(0) < key.at(0)|| (list.at(i).at(0) == key.at(0) && list.at(i).at(1) < key.at(1)) )
        {
            k++;
            std::swap(list.at(k), list.at(i));
        }
    }
    std::swap(list.at(l), list.at(k));
    array<int, 2> m = {k, j};
    return m;
}

void quicksort3(vector<array<int, 3>> &list, int l, int r)
{
    if(l >= r){ return;}
    int random = l + ( std::rand() % (r - l + 1) );
    std::swap(list.at(l), list.at(random));
    array<int, 2> m = partition3(list, l, r);
    quicksort3(list, l, m[0]-1);
    quicksort3(list, m[1]+1, r);
}


// int partition(vector<array<int, 2>> list, int l, int r)
// {
//     // int middle = (l + r)/2;
//     // array<int, 3> median = {list.at(l).at(0), list.at(r).at(0), list.at(middle).at(0)};
// 
//     array<int, 2> key = list.at(l);
//     int j = l;
//     for(int i = l + 1; i<=r; ++i)
//     {
//         if(list.at(i).at(0) <= key.at(0))
//         {
//             std::swap(list.at(++j), list.at(i));
//         }
//     }
//     std::swap(list.at(l), list.at(j));
//     return j;
// }
// 
// void quicksort(vector<array<int, 2>> list, int l, int r)
// {
//     if(l >= r) return;
//     int m = partition(list, l, r);
//     quicksort(list, l, m-1);
//     quicksort(list, m+1, r);
// }
 
vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  int n = points.size() + 2*ends.size();
  vector<std::array<int, 3>> all_data;

  for(int i = 0; i < points.size(); ++i)
  {
     array<int, 3> data = {points.at(i), 1, -i};
     all_data.push_back(data); 
  }
  for(int i = 0; i < ends.size(); ++i)
  {
     array<int, 3> data2 = {starts.at(i), 0, 1};
     array<int, 3> data = {ends.at(i), 2, 1};
     all_data.push_back(data); 
     all_data.push_back(data2);
  }
  //std::cout << all_data.size() << std::endl;

  quicksort3(all_data, 0, all_data.size() - 1);

  for(int i = 0; i < all_data.size(); i++)
  {
      // std::cout << all_data.at(i).at(0) << " " << all_data.at(i).at(1) << std::endl;
  }
  int balance = 0;
  for(int i = 0; i < all_data.size(); i++)
  {
      int flag = all_data.at(i).at(1); // flag for left, point, or right
      int idx = all_data.at(i).at(2); // negative idx for input, else 1 
      if(flag == 0) balance++;
      else if(flag == 2) balance-- ;
      else{cnt.at(-idx) = balance;}
  }
  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  // vector<int> cnt = naive_count_segments(starts, ends, points);
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
