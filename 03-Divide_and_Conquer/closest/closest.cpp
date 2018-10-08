// This code computes the closest pair of n points in R^2
// using a divide and conquer algorithm. The brute force algorithm is
// O(n^2), but the divide and conquer method is O(n log n)
// the code also includes an implementation of a randomized quicksort
// See https://en.wikipedia.org/wiki/Closest_pair_of_points_problem#Planar_case
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

using std::array;
using std::min;
using std::pair;
using std::string;
using std::vector;

// Computes l2 distance between two points in R^2
double l2_dist(array<int, 3> &p0, array<int, 3> &p1);
// Partition function used in the recursive definition of the Quicksort
array<int, 2> partition3(vector<array<int, 3>> &list, int l, int r, char coord);
// Quicksort an array of 2d points by a particular coordinate
void quicksort3(vector<array<int, 3>> &list, int l, int r, char coord);
// Recursion function called by minimal distance solution function
array<array<int, 3>, 2> closest_pair_rec2(vector<array<int, 3>> &Px,
                                          vector<array<int, 3>> &Py);
// Solution function called by main
double minimal_distance(vector<int> &x, vector<int> &y);

double l2_dist(array<int, 3> &p0, array<int, 3> &p1) {
  return std::sqrt(pow(p0[0] - p1[0], 2) + pow(p0[1] - p1[1], 2));
}

array<int, 2> partition3(vector<array<int, 3>> &list, int l, int r,
                         char coord) {
  int idx = coord == 'x' ? 0 : 1;
  int otheridx = 1 - idx;
  array<int, 3> key = list.at(l);
  int j = l;
  if (idx == 0) {
    for (int i = l + 1; i <= r; i++) {
      if (list.at(i).at(idx) < key.at(idx) ||
          (list.at(i).at(idx) == key.at(idx) &&
           list.at(i).at(otheridx) <= key.at(otheridx))) {
        j++;
        std::swap(list.at(j), list.at(i));
      }
    }
    int k = l;
    for (int i = l + 1; i <= j; i++) {
      if (list.at(i).at(idx) < key.at(idx) ||
          (list.at(i).at(idx) == key.at(idx) &&
           list.at(i).at(otheridx) < key.at(otheridx))) {
        k++;
        std::swap(list.at(k), list.at(i));
      }
    }
    std::swap(list.at(l), list.at(k));
    array<int, 2> m = {k, j};
    return m;
  } else {
    for (int i = l + 1; i <= r; i++) {
      if (list.at(i).at(idx) <= key.at(idx)) {
        j++;
        std::swap(list.at(j), list.at(i));
      }
    }
    int k = l;
    for (int i = l + 1; i <= j; i++) {
      if (list.at(i).at(idx) < key.at(idx)) {
        k++;
        std::swap(list.at(k), list.at(i));
      }
    }
    std::swap(list.at(l), list.at(k));
    array<int, 2> m = {k, j};
    return m;
  }
}

array<array<int, 3>, 2> closest_pair_rec2(vector<array<int, 3>> &Px,
                                          vector<array<int, 3>> &Py) {
  // Base case of the recursion
  if (Px.size() == 2) {
    return {Px[0], Px[1]};
  }
  if (Px.size() == 3) {
    array<int, 3> u = Px[0], v = Px[1], w = Px[2];
    double d0 = l2_dist(u, v), d1 = l2_dist(u, w), d2 = l2_dist(v, w);
    if (d0 <= d1 && d0 <= d2)
      return {u, v};
    if (d1 <= d0 && d1 <= d2)
      return {u, w};
    if (d2 <= d0 && d2 <= d1)
      return {v, w};
  }

  // Split list into two along the middle of the x coordinates

  int m = Px.size() / 2, m2 = m;
  while (Px[m2 - 1][0] == Px[m2 - 2][0] && m2 >= 2) {
    m2--;
  }

  // Set up vector copies for the recursion

  vector<array<int, 3>> Qx(Px.begin(), Px.begin() + m),
      Rx(Px.begin() + m, Px.begin() + Px.size()), Qy, Ry;

  assert(Rx.size() + Qx.size() == Px.size());

  int L = Qx[m - 1][0];
  assert(L == Qx.back()[0]);
  assert(m == Qx.size());
  assert(Qx[m - 1][0] == Px[m - 1][0]);
  int keyscount = 0;
  for (int i = 0; i < Py.size(); i++) {
    if (Py[i][0] < L) {
      Qy.push_back(Py[i]);
    } else if (Py[i][0] == L && Py[i][1] <= Qx.back()[1] &&
               keyscount < m - m2 + 1) {
      Qy.push_back(Py[i]);
      keyscount++;
    } else {
      Ry.push_back(Py[i]);
    }
  }
  assert(Qx.size() == Qy.size());
  assert(Rx.size() == Ry.size());
  
  // Recurse on the left and right 

  array<array<int, 3>, 2> Q = closest_pair_rec2(Qx, Qy);
  array<array<int, 3>, 2> R = closest_pair_rec2(Rx, Ry);
  
  // Find minimum distance and argmin points for the left and right regions

  array<int, 3> u, v;  // argmin distance for both regions
  double dist_Q = l2_dist(Q[0], Q[1]), dist_R = l2_dist(R[0], R[1]);
  double delta; // minimum distance of both regions
  if (dist_Q < dist_R) {
    delta = dist_Q;
    u = Q[0];
    v = Q[1];
  } else {
    delta = dist_R;
    u = R[0], v = R[1];
  }

  // Create an array Sy in the left/right region sorted by y-values
  // These will be used to find potential minimizers

  vector<array<int, 3>> Sy;
  for (int i = 0; i <= Py.size() - 1; ++i) {
    if (Py[i][0] - L >= -delta || Py[i][0] - L <= delta) {
      Sy.push_back(Py[i]); // add the point if its a candidate minimizer
    }
  }

  // Only have to go through the sorted array Sy
  // by testing every point with the next 15.
  // This implies the complexity of the divide and conquer is O(n log n)

  if (Sy.size() <= 1)
    return {u, v};
  for (int i = 0; i <= Sy.size() - 2; i++) {
    array<int, 3> p1 = Sy[i];

    for (int j = i + 1; j <= min(i + 20, (int)Sy.size() - 1); j++) {
      array<int, 3> p2 = Sy[j];

      double dist = l2_dist(p1, p2);
      if (dist < delta) {
        u = p1;
        v = p2;
      }
    }
  }

  return {u, v};
}

void quicksort3(vector<array<int, 3>> &list, int l, int r, char coord) {
  if (l >= r) {
    return;
  }
  int random = l + (std::rand() % (r - l + 1));
  std::swap(list.at(l), list.at(random));
  array<int, 2> m = partition3(list, l, r, coord);
  quicksort3(list, l, m[0] - 1, coord);
  quicksort3(list, m[1] + 1, r, coord);
}

double minimal_distance(vector<int> &x, vector<int> &y) {
  // Construct P_x and P_y O(n logn) time
  // Call Closest-Pair-Rec(P_x, P_y) recurrence is T(n) = 2T(n/2) + O(n) => T(n)
  // = O(nlogn)
  vector<array<int, 3>> Px;
  vector<array<int, 3>> Py;
  for (int i = 0; i < x.size(); ++i) {
    array<int, 3> xy = {x[i], y[i], i};
    Px.push_back(xy);
    Py.push_back(xy);
  }
  quicksort3(Px, 0, x.size() - 1, 'x');
  quicksort3(Py, 0, x.size() - 1, 'y');

  array<array<int, 3>, 2> argmin = closest_pair_rec2(Px, Py);
  return l2_dist(argmin[0], argmin[1]);
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
