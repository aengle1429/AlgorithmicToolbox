#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
    double value = 0.0;
    double filled = 0.0; // this is the amount filled so far.
	int num_items = weights.size();
	double values_by_wt [num_items];

	// Create double array for value per unit weight
	for(int i = 0; i < num_items; ++i)
	{
		values_by_wt[i] = (double) values.at(i) / weights.at(i);
	}

	if(num_items > 1)
	{
		// Begin insertion sort
		for(int i = 1; i < num_items; ++i)
		{
			double key = values_by_wt[i];
			int wtkey = weights.at(i);
			
			int j = i - 1;
			while(j>=0 && values_by_wt[j] > key)
			{
				weights.at(j+1) = weights.at(j);	
				values_by_wt[j+1] = values_by_wt[j];	
				j--;
			}
			weights.at(j+1) = wtkey;
			values_by_wt[j+1] = key;
		}
		
		// for(int i = 0; i < num_items; ++i)
		// {
		// 	std::cout << i << ", " << values_by_wt[i] << ", " << weights.at(i) << std::endl;
		// }
	}
	int i = num_items - 1;
    while(filled < capacity && i>=0)
	{
		// while there is room in the bag, put the max mount
		// given by the smaller of capacity - filled and weight of ith item.
		// this is the greedy choice using the sortedness.
		double min = capacity - filled - weights.at(i) > 0 ? weights.at(i) : capacity-filled;
		filled += min;
		value += min * values_by_wt[i];
		--i;
	} 
    return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
