#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
	vector<int> points;
	//sort by right-hand endpoint. Choose the smallest to begin with.
	//iterate through the remainder of the list until a left-hand endpoint
	//is strictly larger (hence right-hand is too). 
	//The sorting property guarantees that segment's right-hand
	//endpoint is smallest among segments not yet covered. The iteration continues
	// 
	if(segments.size() > 1)
	{
		for(int i = 1; i < segments.size(); ++i)
		{
			int j = i - 1;
			Segment key = segments.at(i);
			while(j >= 0 && segments.at(j).end > key.end)
			{
				segments.at(j+1) = segments.at(j);
				j--;
			}
			segments.at(j+1) = key;
		}

		points.push_back(segments.at(0).end);
		for(int i = 1; i < segments.size(); ++i)
		{
			if(segments.at(i).start > points.back())
			{
				points.push_back(segments.at(i).end);
			}
		}
	}
	else
	{
		points.push_back(segments.at(0).end);
	}
	// for (size_t i = 0; i < segments.size(); ++i) {
	// 	points.push_back(segments[i].start);
	// 	points.push_back(segments[i].end);
	// }
	return points;
}

int main() {
	int n;
	std::cin >> n;
	vector<Segment> segments(n);
	for (size_t i = 0; i < segments.size(); ++i) {
	std::cin >> segments[i].start >> segments[i].end;
	}
	vector<int> points = optimal_points(segments);
	std::cout << points.size() << "\n";
	for (size_t i = 0; i < points.size(); ++i) {
	std::cout << points[i] << " ";
	}
}
