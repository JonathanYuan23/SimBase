#include "lsh.h"

namespace simbase::cpu
{
LSHIndex::LSHIndex(int dimensions): 
	// TODO: find better way of deciding on numHyperplanes
	numHyperplanes(dimensions / 10), size(0),
	Index(dimensions), hyperplanes(), 
	hashTables()
{
	// generate random hyperplanes
	for (int i = 0; i < numHyperplanes; i++)
	{
		hyperplanes.push_back(VectorXd::Random(dimensions));
	}
}

void LSHIndex::Add(VectorXd point)
{
	assert(dimensions == point.size());
	string hashValue = hash(point);

	// if no hash bucket exists for the hash value, create one
	if (hashTables.find(hashValue) == hashTables.end())
	{
		hashTables[hashValue] = std::vector<int>();
	}

	// add the point index to the hash bucket
	hashTables[hashValue].push_back(size++);
	points.push_back(point);
}

std::vector<VectorXd> LSHIndex::search(VectorXd query, int k) const
{
	assert(dimensions == query.size());
	assert(k <= n_total);

	// calculate hash
	string hashValue = hash(query);

	std::vector<VectorXd> nearest;

	// we account for all cases: the bin for the query contains < k elements, or not
	
	// check if bin contains < k values, or doesn't exist (slow, but unlikely to happen w/ enough points)
	auto entry = hashTables.find(hashValue);
	if(entry == hashTables.end() || entry->second.size() < k) {
		// check every other hash table based on hamming distance

		// ctor order: Type, Container, Comparator (creates min heap storing pairs)
		std::priority_queue<std::pair<int, string>, std::vector<std::pair<int, string>>, std::greater<std::pair<int, string>>> binPQ;
		for(auto kv : hashTables) {
			int dist = Distances::hamming(hashValue, kv.first);
			binPQ.push({dist, kv.first});
		}

		int candidates = 0;
		std::vector<string> binCandidates;
		// pop from pq until there are enough candidates
		while(candidates < k) {
			string bin = binPQ.top().second;
			binPQ.pop();
			candidates += hashTables.find(bin)->second.size();
			binCandidates.emplace_back(bin);
		}

		/* Search for nearest */
		// pair as {inner product to query, index in points}
		std::priority_queue<std::pair<double, int>> pq;
		
		for(string bin : binCandidates) {
			auto vec = hashTables.find(bin)->second;
			for(int i : vec) {
				double IP = query.dot(points[i]);
				pq.push({IP, i});

				if(pq.size() > k)
				{
					pq.pop();
				}
			}
		}
		while(!pq.empty())
		{
			auto& p = points[pq.top().second];
			pq.pop();
			nearest.push_back(p);
		}

		std::reverse(nearest.begin(), nearest.end());

		return nearest;
	}

	/*  we only need to check our one bin */
	std::priority_queue<std::pair<double, int>> pq;
	auto keyBin = hashTables.find(hashValue)->second;

	for(int i : keyBin) {
		double IP = query.dot(points[i]);
		pq.push({IP, i});

		if(pq.size() > k)
		{
			pq.pop();
		}
	}
	while(!pq.empty())
	{
		auto& p = points[pq.top().second];
		pq.pop();
		nearest.push_back(p);
	}

	std::reverse(nearest.begin(), nearest.end());

	return nearest;
}

string LSHIndex::hash(VectorXd point) const {
	// TODO: use something better to store hash values, bitset (?)
	string hash = "";
	// calculate the hash value for each hash function
	for (int i = 0; i < numHyperplanes; i++)
	{
		hash += (hyperplanes[i].dot(point) > 0) ? "1" : "0";
	}
	return hash;
}

} // namespace simbase
