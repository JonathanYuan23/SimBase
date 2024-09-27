#include "flat.h"
#include <queue>

namespace simbase::cpu
{

IndexFlatIP::IndexFlatIP(int dimensions)
	: Index(dimensions)
{}

std::vector<VectorXd> IndexFlatIP::search(VectorXd query, int k) const
{
	assert(dimensions == query.size());
	assert(k <= n_total);

	// pair as {inner product to query, index in points}
	std::priority_queue<std::pair<double, int>> pq;

	for(size_t i = 0; i < points.size(); ++i)
	{
		double IP = query.dot(points[i]);
		pq.push({IP, i});

		if(pq.size() > k)
		{
			pq.pop();
		}
	}

	std::vector<VectorXd> nearest;
	while(!pq.empty())
	{
		auto& p = points[pq.top().second];
		pq.pop();
		nearest.push_back(p);
	}

	std::reverse(nearest.begin(), nearest.end());

	return nearest;
}

} // namespace simbase::cpu